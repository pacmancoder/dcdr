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
#include <limits>

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

    Mcrt::SpectralDistribution load_texture(IDatabase& database, int32_t  id)
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
            return Mcrt::SpectralDistribution(
                    Types::Real(colorTextureCursor->get_double(0)),
                    Types::Real(colorTextureCursor->get_double(1)),
                    Types::Real(colorTextureCursor->get_double(2)));
        }

        log_warning(LOG_PREFIX, "Unsupported texture type: ", textureType);
        return Mcrt::SpectralDistribution();
    }

    std::shared_ptr<Mcrt::Material> load_material(IDatabase& database, int32_t  id)
    {
        auto materialQuery = database.prepare(
                "SELECT diffuseTexId, specularTexId,"
                    "kDiffuse, kSpecular, kReflectance, kGlossiness, "
                    "kTransmittance, kIOR, kEmittance FROM Material WHERE id = ? LIMIT 1");
        auto materialCursor = materialQuery->bind(id).execute();

        if (!materialCursor->next())
        {
            log_warning(LOG_PREFIX, "No material found with id ", id);
            return nullptr;
        }

        auto material = std::make_shared<Mcrt::Material>();

        if (!materialCursor->is_null(0))
        {
            material->color_diffuse = load_texture(database, materialCursor->get_int(0));
        }
        if (!materialCursor->is_null(1))
        {
            material->color_specular = load_texture(database, materialCursor->get_int(1));
        }

        material->specular_reflectance = static_cast<float>(materialCursor->get_double(3));
        material->reflectance = static_cast<float>(materialCursor->get_double(4));
        // roughness from glossiness
        material->diffuse_roughness = 1.0f - static_cast<float>(materialCursor->get_double(5));
        material->transmissivity = static_cast<float>(materialCursor->get_double(6));
        material->refraction_index = static_cast<float>(materialCursor->get_double(7));
        material->emittance = static_cast<float>(materialCursor->get_double(8));

        log_debug(LOG_PREFIX, "Emittance: ", material->emittance);
        log_debug(LOG_PREFIX, "Loaded material #", id);
        return material;
    }
/*
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
*/
    std::shared_ptr<Mcrt::Object3D> load_object(
            IDatabase& database,
            Types::Mat4& transform,
            const std::shared_ptr<Mcrt::Material>& material,
            int geometryId)
    {
        auto geometryTypeQuery = database.prepare("SELECT type FROM Geometry WHERE id = ? LIMIT 1");
        auto geometryTypeCursor = geometryTypeQuery->bind(geometryId).execute();
        if (!geometryTypeCursor->next())
        {
            throw SceneLoaderException(std::string("No geometry found with id ").append(std::to_string(geometryId)));
        }

        auto geometryType = geometryTypeCursor->get_string(0);
        if (geometryType == "SPHERE")
        {
            auto sphereGeometryQuery = database.prepare("SELECT radius FROM SphereGeomery WHERE id = ? LIMIT 1");
            auto sphereGeometryCursor = sphereGeometryQuery->bind(geometryId).execute();
            if (!sphereGeometryCursor->next())
            {
                throw SceneLoaderException(
                        std::string("Can't find sphere geometry with id ").append(std::to_string(geometryId)));
            }

            auto originalRadius = sphereGeometryCursor->get_double(0);

            auto radius = glm::length(transform * Types::Vec4(Types::Vec3(originalRadius, 0.f, 0.f), 0.0f));
            auto position = transform * Types::Vec4(Types::Vec3(0.f), 1.0f);

            log_debug(LOG_PREFIX, "Loaded geometry #", geometryId, " (SphereGeometry)");
            return std::make_shared<Mcrt::Sphere>(material, position, radius);
        }
        else if (geometryType == "MESH")
        {
            auto meshGeometryQuery = database.prepare(
                    "SELECT points, normals, uvs FROM MeshGeometry WHERE id = ? LIMIT 1");
            auto meshGeometryCursor = meshGeometryQuery->bind(geometryId).execute();

            if (!meshGeometryCursor->next())
            {
                throw SceneLoaderException(
                        std::string("Can't find mesh geometry with id ").append(std::to_string(geometryId)));
            }

            static const size_t FLOATS_IN_VEC3 = 3;
            static const size_t FLOATS_IN_VEC2 = 2;

            auto pointsBlob = meshGeometryCursor->get_blob(0);
            auto normalsBlob = meshGeometryCursor->get_blob(1);
            auto uvsBlob = meshGeometryCursor->get_blob(2);

            auto pointsCount = pointsBlob.size() / (FLOATS_IN_VEC3 * sizeof(float));

            std::vector<Types::Vec3> points;
            points.reserve(pointsCount);

            std::vector<Types::Vec3> normals;
            normals.reserve(pointsCount);

            std::vector<Types::Vec2> uvs;
            uvs.reserve(pointsCount);

            for(size_t i = 0; i < pointsCount; ++i)
            {
                points.emplace_back(
                        *(reinterpret_cast<const float*>(pointsBlob.data()) + i * FLOATS_IN_VEC3 + 0),
                        *(reinterpret_cast<const float*>(pointsBlob.data()) + i * FLOATS_IN_VEC3 + 1),
                        *(reinterpret_cast<const float*>(pointsBlob.data()) + i * FLOATS_IN_VEC3 + 2));
                normals.emplace_back(
                        *(reinterpret_cast<const float*>(normalsBlob.data()) + i * FLOATS_IN_VEC3 + 0),
                        *(reinterpret_cast<const float*>(normalsBlob.data()) + i * FLOATS_IN_VEC3 + 1),
                        *(reinterpret_cast<const float*>(normalsBlob.data()) + i * FLOATS_IN_VEC3 + 2));
                uvs.emplace_back(
                        *(reinterpret_cast<const float*>(uvsBlob.data()) + i * FLOATS_IN_VEC2 + 0),
                        *(reinterpret_cast<const float*>(uvsBlob.data()) + i * FLOATS_IN_VEC2 + 1));
            }

            return std::make_shared<Mcrt::Mesh>(
                    material,
                    transform,
                    std::move(points),
                    std::move(normals),
                    std::move(uvs));
        }
        else if (geometryType == "PLANE")
        {
            auto planeGeometryQuery = database.prepare("SELECT width, height FROM PlaneGeometry WHERE id = ? LIMIT 1");
            auto planeGeometryCursor = planeGeometryQuery->bind(geometryId).execute();
            if (!planeGeometryCursor->next())
            {
                throw SceneLoaderException(
                        std::string("Can't find plane geometry with id ").append(std::to_string(geometryId)));
            }

            auto width = planeGeometryCursor->get_double(0);
            auto height = planeGeometryCursor->get_double(0);

            // anti-clockwise order
            auto p1 = transform * Types::Vec4( width / 2, -height / 2, 0, 1);
            auto p2 = transform * Types::Vec4( width / 2,  height / 2, 0, 1);
            auto p3 = transform * Types::Vec4(-width / 2,  height / 2, 0, 1);

            log_debug(LOG_PREFIX, "Loaded geometry #", geometryId, " (SphereGeometry)");

            return std::make_shared<Mcrt::Plane>(material, p1, p2, p3);
        }

        log_warning(LOG_PREFIX, "Unsupported geometry type: ", geometryType);

        return nullptr;
    }

    std::shared_ptr<Mcrt::LightSource> load_lamp(
            IDatabase& database,
            Types::Mat4& transform,
            const std::shared_ptr<Mcrt::Material>& material,
            int geometryId)
    {
        auto geometryTypeQuery = database.prepare("SELECT type FROM Geometry WHERE id = ? LIMIT 1");
        auto geometryTypeCursor = geometryTypeQuery->bind(geometryId).execute();
        if (!geometryTypeCursor->next())
        {
            throw SceneLoaderException(std::string("No geometry found with id ").append(std::to_string(geometryId)));
        }

        auto geometryType = geometryTypeCursor->get_string(0);

        if (geometryType == "PLANE")
        {
            auto planeGeometryQuery = database.prepare("SELECT width, height FROM PlaneGeometry WHERE id = ? LIMIT 1");
            auto planeGeometryCursor = planeGeometryQuery->bind(geometryId).execute();
            if (!planeGeometryCursor->next())
            {
                throw SceneLoaderException(
                        std::string("Can't find lamp plane geometry with id ").append(std::to_string(geometryId)));
            }

            auto width = planeGeometryCursor->get_double(0);
            auto height = planeGeometryCursor->get_double(0);

            // anti-clockwise order
            auto p1 = transform * Types::Vec4( width / 2, -height / 2, 0, 1);
            auto p2 = transform * Types::Vec4( width / 2,  height / 2, 0, 1);
            auto p3 = transform * Types::Vec4(-width / 2,  height / 2, 0, 1);

            log_debug(LOG_PREFIX, "Loaded lamp geometry #", geometryId, " (SphereGeometry)");

            return std::make_shared<Mcrt::LightSource>(p1, p2, p3, material->emittance, material->color_diffuse);
        }

        log_warning(LOG_PREFIX, "Unsupported lamp geometry type: ", geometryType);

        return nullptr;
    }

    void load_objects(IDatabase& database, Mcrt::Scene& scene)
    {
        auto objectsQuery = database.prepare(
                "SELECT name, geometryId, materialId, pos, rotation, scale, visible FROM SceneObject");
        auto objectsCursor = objectsQuery->execute();

        auto defaultMaterial = std::make_shared<Mcrt::Material>(Mcrt::Material::air());

        uint32_t objId = 0;
        while (objectsCursor->next())
        {
            auto name = objectsCursor->get_string(0);

            if (objectsCursor->get_int(6) == 0)
            {
                log_info(LOG_PREFIX, "Object ", name, " is invisible. Skipping loading");
                continue;
            }

            auto material = load_material(database, objectsCursor->get_int(2));

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

            auto geometryId = objectsCursor->get_int(1);

            if (material->emittance >= 0.0001)
            {
                auto lamp = load_lamp(database, transformationMatrix, material, geometryId);
                if (!lamp)
                {
                    log_warning(LOG_PREFIX, "Lamp \"", name, "\" loading was skipped");
                    return;
                }
                scene.AddLightSource(objId++, lamp);
                log_debug(LOG_PREFIX, "Loaded lamp \"", name, "\"");
            }
            else
            {
                auto obj = load_object(database, transformationMatrix, material, geometryId);
                if (!obj)
                {
                    log_warning(LOG_PREFIX, "Object \"", name, "\" loading was skipped");
                    return;
                }
                scene.AddObject(objId++, obj);
                log_debug(LOG_PREFIX, "Loaded object \"", name, "\"");
            }
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

void SceneLoader::load_to(Mcrt::Scene& scene)
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

