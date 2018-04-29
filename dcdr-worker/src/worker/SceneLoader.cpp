#include <dcdr/Types.h>
#include <dcdr/worker/SceneLoader.h>
#include <dcdr/worker/WorkerExceptions.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/database/SQLiteDatabase.h>

#include <mcrt/Object3D.h>
#include <mcrt/Camera.h>

#include <functional>
#include <fstream>
#include <cstdlib>

#include <microtar.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace Dcdr;
using namespace Dcdr::Logging;
using namespace Dcdr::Worker;
using namespace Dcdr::Database;

namespace
{
    const char* LOG_PREFIX = "[Worker][SceneLoader] ";

    Types::Vec3 blob_to_vec3(std::vector<uint8_t> blob)
    {
        return Types::Vec3(
                Types::Real(*(reinterpret_cast<float*>(blob.data()))),
                Types::Real(*(reinterpret_cast<float*>(blob.data()) + 1)),
                Types::Real(*(reinterpret_cast<float*>(blob.data()) + 2)));
    }

    void load_camera(IDatabase& database, Mcrt::Scene& scene)
    {
        auto cameraQuery = database.prepare(
                "SELECT pos, up, direction, fov, dofDistance, dofRadius FROM Camera LIMIT 1");
        auto cameraCursor = cameraQuery->execute();

        auto metaInfoQuery = database.prepare(
                "SELECT renderWidth, renderHeight FROM Metainfo LIMIT 1");
        auto metaInfoCursor = metaInfoQuery->execute();

        if (!metaInfoCursor->next())
        {
            throw SceneLoaderException("Can't execute Scene meta info query");
        }

        auto baseWidth = metaInfoCursor->get_int(0);
        auto baseHeight = metaInfoCursor->get_int(1);

        Mcrt::Scene::SceneEntityId cameraId = 0;
        while(cameraCursor->next())
        {
            auto eye = blob_to_vec3(cameraCursor->get_blob(0));
            auto direction = blob_to_vec3(cameraCursor->get_blob(2));
            auto center = eye + direction * 1.f;
            auto up = blob_to_vec3(cameraCursor->get_blob(1));
            auto fov = Types::Real(cameraCursor->get_double(3));

            scene.AddCamera(cameraId++, std::make_shared<Mcrt::Camera>(
                    eye, center, up, fov, baseWidth, baseHeight));
        }
    }

    std::shared_ptr<Renderer::ITexture> load_texture(IDatabase& database, int32_t  id)
    {
        auto textureTypeQuery = database.prepare("SELECT type FROM Texture WHERE id = ? LIMIT 1");
        auto textureTypeCursor = textureTypeQuery->bind(id).execute();
        if (!textureTypeCursor->next())
        {
            throw SceneLoaderException(std::string("Can't find texture with id ").append(std::to_string(id)));
        }

        auto textureType = textureTypeCursor->get_string(0);

        if (textureType == "COLOR")
        {
            auto colorTextureQuery = database.prepare("SELECT r, g, b FROM ColorTexture WHERE id = ?");
            auto colorTextureCursor = colorTextureQuery->bind(id).execute();
            if (!colorTextureCursor->next())
            {
                throw SceneLoaderException(std::string("Can't find color texture with id ")
                        .append(std::to_string(id)));
            }

            log_debug(LOG_PREFIX, "Loaded texture #", id, " (ColorTexture)");
            return std::make_shared<Renderer::ColorTexture>(Types::Vec3(
                    Types::Real(colorTextureCursor->get_double(0)),
                    Types::Real(colorTextureCursor->get_double(1)),
                    Types::Real(colorTextureCursor->get_double(2))));
        }

        log_warning(LOG_PREFIX, "Unsupported texture type: ", textureType);
        return nullptr;
    }

    std::shared_ptr<Renderer::Material> load_material(IDatabase& database, int32_t  id)
    {
        auto materialQuery = database.prepare(
                "SELECT bumpTexId, diffuseTexId, glossinessTexId, refractionGlossinessTexId, "
                    "kAmbient, kDiffuse, kReflectance, kGlossiness, kRefractionGlossiness, "
                    "kTransmittance, kIOR, kEmittance FROM Material WHERE id = ? LIMIT 1");
        auto materialCursor = materialQuery->bind(id).execute();
        if (!materialCursor->next())
        {
            log_warning(LOG_PREFIX, "No material found with id ", id);
            return nullptr;
        }

        Renderer::Material::Textures textures;

        if (!materialCursor->is_null(0))
        {
            auto tex = load_texture(database, materialCursor->get_int(0));
            textures[Renderer::TextureType::Bump] = tex;
        }
        if (!materialCursor->is_null(1))
        {
            auto tex = load_texture(database, materialCursor->get_int(1));
            textures[Renderer::TextureType::Diffuse] = tex;
        }
        if (!materialCursor->is_null(2))
        {
            auto tex = load_texture(database, materialCursor->get_int(2));
            textures[Renderer::TextureType::Glossiness] = tex;
        }
        if (!materialCursor->is_null(3))
        {
            auto tex = load_texture(database, materialCursor->get_int(3));
            textures[Renderer::TextureType::RefractionGlossiness] = tex;
        }

        Renderer::MaterialParams params = {
                Types::Real(materialCursor->get_double(4)),
                Types::Real(materialCursor->get_double(5)),
                Types::Real(materialCursor->get_double(6)),
                Types::Real(materialCursor->get_double(7)),
                Types::Real(materialCursor->get_double(8)),
                Types::Real(materialCursor->get_double(9)),
                Types::Real(materialCursor->get_double(10)),
                Types::Real(materialCursor->get_double(11))
        };

        log_debug(LOG_PREFIX, "Loaded material #", id);
        return std::make_shared<Renderer::Material>(params, std::move(textures));
    }

    std::shared_ptr<Renderer::IObjectGeometry> load_geometry(IDatabase& database, int32_t id)
    {
        auto geometryTypeQuery = database.prepare("SELECT type FROM Geometry WHERE id = ? LIMIT 1");
        auto geometryTypeCursor = geometryTypeQuery->bind(id).execute();
        if (!geometryTypeCursor->next())
        {
            throw SceneLoaderException(std::string("No geometry found with id ").append(std::to_string(id)));
        }
        auto geometryType = geometryTypeCursor->get_string(0);
        if (geometryType == "SPHERE")
        {
            auto sphereGeometryQuery = database.prepare("SELECT radius FROM SphereGeomery WHERE id = ? LIMIT 1");
            auto sphereGeometryCursor = sphereGeometryQuery->bind(id).execute();
            if (!sphereGeometryCursor->next())
            {
                throw SceneLoaderException(
                        std::string("Can't find sphere geometry with id ").append(std::to_string(id)));
            }

            auto radius = sphereGeometryCursor->get_double(0);

            log_debug(LOG_PREFIX, "Loaded geometry #", id, " (SphereGeometry)");
            return std::make_shared<Renderer::SphereGeometry>(radius);
        }

        else if (geometryType == "MESH")
        {
            auto meshGeometryQuery = database.prepare(
                    "SELECT points, normals, uvs FROM MeshGeometry WHERE id = ? LIMIT 1");
            auto meshGeometryCursor = meshGeometryQuery->bind(id).execute();
            if (!meshGeometryCursor->next())
            {
                throw SceneLoaderException(
                        std::string("Can't find mesh geometry with id ").append(std::to_string(id)));
            }

            static const size_t POINTS_IN_TRIANGLE = 3;
            static const size_t FLOATS_IN_VEC3 = 3;
            static const size_t FLOATS_IN_VEC2 = 2;
            static const size_t FLOATS_IN_TRIANGLE_VEC3 = POINTS_IN_TRIANGLE * FLOATS_IN_VEC3;
            static const size_t FLOATS_IN_TRIANGLE_VEC2 = POINTS_IN_TRIANGLE * FLOATS_IN_VEC2;

            auto pointsBlob = meshGeometryCursor->get_blob(0);
            auto normalsBlob = meshGeometryCursor->get_blob(1);
            auto uvsBlob = meshGeometryCursor->get_blob(2);

            auto trianglesCount = pointsBlob.size() / FLOATS_IN_TRIANGLE_VEC3 / sizeof(float);
            std::vector<Renderer::MeshGeometry::Triangle> triangles;
            triangles.reserve(trianglesCount);

            for (size_t triangleIdx = 0; triangleIdx < trianglesCount; ++triangleIdx)
            {

                Renderer::MeshGeometry::Triangle triangle = {};

                for (size_t pointIdx = 0; pointIdx < 3; ++pointIdx)
                {
                    triangle.pos[pointIdx] = Types::Vec3(
                            *(reinterpret_cast<const float*>(pointsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC3 + pointIdx * FLOATS_IN_VEC3) + 0),
                            *(reinterpret_cast<const float*>(pointsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC3 + pointIdx * FLOATS_IN_VEC3) + 1),
                            *(reinterpret_cast<const float*>(pointsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC3 + pointIdx * FLOATS_IN_VEC3) + 2));

                    triangle.normal[pointIdx] = Types::Vec3(
                            *(reinterpret_cast<const float*>(normalsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC3 + pointIdx * FLOATS_IN_VEC3) + 0),
                            *(reinterpret_cast<const float*>(normalsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC3 + pointIdx * FLOATS_IN_VEC3) + 1),
                            *(reinterpret_cast<const float*>(normalsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC3 + pointIdx * FLOATS_IN_VEC3) + 2));

                    triangle.uv[pointIdx] = Types::Vec2(
                            *(reinterpret_cast<const float*>(uvsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC2 + pointIdx * FLOATS_IN_VEC2) + 0),
                            *(reinterpret_cast<const float*>(uvsBlob.data()) + (triangleIdx * FLOATS_IN_TRIANGLE_VEC2 + pointIdx * FLOATS_IN_VEC2) + 1));
                }

                triangles.push_back(triangle);
            }

            return std::make_shared<Renderer::MeshGeometry>(std::move(triangles));
        }

        log_warning(LOG_PREFIX, "Unsupported geometry type: ", geometryType);
        return nullptr;
    }

    void load_objects(IDatabase& database, Renderer::Scene& scene)
    {
        auto objectsQuery = database.prepare(
                "SELECT name, geometryId, materialId, pos, rotation, scale, visible FROM SceneObject");
        auto objectsCursor = objectsQuery->execute();

        Renderer::MaterialParams defaultMaterialParams = {};
        defaultMaterialParams.diffuse = 1.0;

        std::shared_ptr<Renderer::Material> defaultMaterial = std::make_shared<Renderer::Material>(
                defaultMaterialParams, Renderer::Material::Textures());

        while (objectsCursor->next())
        {
            auto name = objectsCursor->get_string(0);

            if (objectsCursor->get_int(6) == 0)
            {
                log_info(LOG_PREFIX, "Object ", name, " is invisible. Skipping loading");
                continue;
            }

            auto geometry = load_geometry(database, objectsCursor->get_int(1));
            auto material = load_material(database, objectsCursor->get_int(2));

            if (geometry == nullptr)
            {
                log_warning(LOG_PREFIX, "Can't load ", name, " object geometry. Skipping");
                continue;
            }

            // Object always have some material
            if (material == nullptr)
            {
                material = defaultMaterial;
                log_warning(LOG_PREFIX, "Can't load texture for ", name, " assigning default texture");
            }


            auto pos = blob_to_vec3(objectsCursor->get_blob(3));
            auto euler_angles = blob_to_vec3(objectsCursor->get_blob(4));
            auto scale = blob_to_vec3(objectsCursor->get_blob(5));

            Types::Mat4 transformationMatrix =
                    glm::translate(pos) *
                    glm::eulerAngleXYX(euler_angles.x, euler_angles.y, euler_angles.z) *
                    glm::scale(scale);

            log_debug(LOG_PREFIX, "Loaded object \"", name, "\"");
            scene.add_object(std::make_shared<Renderer::SceneObject>(transformationMatrix, geometry, material));
        }
    }
}

struct SceneLoader::Impl
{
    explicit Impl(std::string path);

    std::string scenePath_;
};

SceneLoader::Impl::Impl(std::string path) :
    scenePath_(std::move(path)) {}

SceneLoader::SceneLoader(const std::string& path) :
    impl_(std::make_unique<Impl>(path)) {}

void SceneLoader::load_to(Renderer::Scene& scene)
{
    mtar_t tar = {};
    std::unique_ptr<mtar_t, std::function<void(mtar_t*)>> tarDeleter(&tar, [](mtar_t* tar){ mtar_close(tar); });

    if (mtar_open(&tar, impl_->scenePath_.c_str(), "rb") != MTAR_ESUCCESS)
    {
        throw SceneLoaderException("Can't open scene file");
    }

    mtar_header_t tarHeader = {};
    if (mtar_find(&tar, "scene.db", &tarHeader) != MTAR_ESUCCESS)
    {
        throw SceneLoaderException("Can't find scene.db in scene tar archive");
    }

    std::string unpackedDBPath = impl_->scenePath_ + ".scene.db.tmp";
    {
        std::ofstream unpackedFile;
        unpackedFile.exceptions(std::ios::failbit | std::ios::badbit);
        unpackedFile.open(unpackedDBPath, std::ios::out | std::ios::binary);
        std::vector<char> buffer(tarHeader.size);
        mtar_read_data(&tar, buffer.data(), tarHeader.size);
        unpackedFile.write(buffer.data(), buffer.size());
        log_debug(LOG_PREFIX, "Unpacked scene.db file");
    }

    SQLiteDatabase db(unpackedDBPath);

    load_camera(db, scene);
    load_objects(db, scene);
}

SceneLoader::~SceneLoader() = default;

