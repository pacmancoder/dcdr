import bpy
import struct
import sqlite3
import os
import shutil
import tarfile
import random
import string
import hashlib

dbScriptPath = '/home/pacmancoder/core/projects/dcdr/dcdr-scene/scenedb.sql'

tmpDirectory = '/home/pacmancoder/core/projects/dcdr/dcdr-scene/scenes_tmp/'
outputDirectory = '/home/pacmancoder/core/projects/dcdr/dcdr-scene/scenes/'


dbName = 'scene.db'
dbPath = tmpDirectory + dbName

if os.path.isdir(tmpDirectory):
    shutil.rmtree(tmpDirectory, ignore_errors=True)

os.mkdir(tmpDirectory);

if os.path.isfile(dbPath):
    os.remove(dbPath)

print('[INFO] Export started...\n\n')

dbScriptFile = open(dbScriptPath, 'r')
dbScript = dbScriptFile.read()

dbConnection = sqlite3.connect(dbPath)
dbCursor = dbConnection.cursor()
dbCursor.executescript(dbScript)

print('[>>>>] Reading cameras...')

for camera in bpy.data.cameras:
    obj = bpy.data.objects[camera.name]
    cameraPos =  struct.pack('fff', obj.location[0], obj.location[1], obj.location[2])
    cameraRotation =  struct.pack('fff', obj.rotation_euler[0], obj.rotation_euler[1], obj.rotation_euler[2])

    cameraAngle       = camera.angle
    cameraDofDistance = camera.dof_distance
    cameraDofRadius   = camera.get('dofRadius', 0.0)
    
    dbCursor.execute('INSERT INTO Camera(pos, rotation, fov, dofDistance, dofRadius) VALUES(?, ?, ?, ?, ?)',
        [cameraPos, cameraRotation, cameraAngle, cameraDofDistance, cameraDofRadius])

print('[<<<<]', len(bpy.data.cameras), 'cameras written to the scene\n\n')

textures = {}

print('[>>>>] Exporting bitmap textures...')

for img in bpy.data.images:
    if not img.users or (img.users == 1 and img.use_fake_user):
        bpy.data.images.remove(img)

imageCounter = 0
bpy.context.scene.render.image_settings.file_format = 'PNG'

for texture in bpy.data.textures:    
    if texture.type == 'IMAGE' and texture.image is not None:
        assetName = 'tex_' + str(imageCounter) + '.png'
        texture.image.save_render(filepath = tmpDirectory + assetName) 
        dbCursor.execute('INSERT INTO Texture(type) VALUES(?)', ['BITMAP'])
        textures[texture.name] = dbCursor.lastrowid
        dbCursor.execute('INSERT INTO BitmapTexture(id, format, path, channels, filter) VALUES(?, ?, ?, ?, ?)',
            [dbCursor.lastrowid, 'PNG', assetName, 'RGB', 'LINEAR'])
    else:
        print('[WARNING] Texture', texture.name, 'with id', imageCounter, 'has no assigned file')
        dbCursor.execute('INSERT INTO Texture(type) VALUES(?)', ['NONE'])
        textures[texture.name] = dbCursor.lastrowid        

    imageCounter += 1
        
print('[<<<<]', len(bpy.data.textures), 'textures written to the scene\n\n')

print('[>>>>] Exporting materials...')

materials = {}

for material in bpy.data.materials:
    if material.type == 'SURFACE':

        diffuseMap = None
        bumpMap = None
        glossinessMap = None
        refractionGlossinessMap = None
                
        for textureSlot in material.texture_slots:
            if textureSlot is not None:
                if textureSlot.use_map_color_diffuse:
                    diffuseMap = textures[textureSlot.name]
                elif textureSlot.use_map_normal:
                    bumpMap = textures[textureSlot.name]
                elif textureSlot.use_map_hardness:
                    glossinessMap = textures[textureSlot.name]
                elif textureSlot.use_map_translucency:
                    refractionGlossinessMap = textures[textureSlot.name]
        
        if diffuseMap is None:
            dbCursor.execute('INSERT INTO Texture(type) VALUES(?)', ['COLOR'])
            diffuseMap = dbCursor.lastrowid
            dbCursor.execute('INSERT INTO ColorTexture(id, r, g, b) VALUES(?, ?, ?, ?)',
                [diffuseMap, material.diffuse_color.r, material.diffuse_color.g, material.diffuse_color.b])            
        
        kDiffuse = material.diffuse_intensity
        
        kReflectance = material.raytrace_mirror.reflect_factor
        kAmbient = material.get('ambient', 0.0)
        kGlossiness =  material.raytrace_mirror.gloss_factor
        
        kRefractionGlossiness = material.raytrace_transparency.gloss_factor        
        kTransmittance = max(0, min(1.0 - material.alpha, 1))
        kIOR = material.raytrace_transparency.ior
        
        kEmittance = material.emit
        
        materialTuple = [bumpMap, diffuseMap, glossinessMap, refractionGlossinessMap,
            kAmbient, kDiffuse, kReflectance, kGlossiness,
            kRefractionGlossiness, kTransmittance, kIOR, kEmittance]
            
        dbCursor.execute(
            'INSERT INTO Material(bumpTexId, duffuseTexId, glossinessTexId, ' + 
            'refractionGlossinessTexId, kAmbient, kDiffuse, kReflectance, kGlossiness, ' +
            'kRefractionGlossiness, kTransmittance, kIOR, kEmittance) ' +
            'VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', materialTuple)

        materials[material.name] = dbCursor.lastrowid
        
    else:
        print("[ERROR]: ", material.type, 'material type is not supported')
        raise
print('wtf')
print('[<<<<]', len(bpy.data.materials), 'materials written to the scene\n\n')

print('[>>>>] Exporting meshes...')

meshCount = 0

for object in bpy.data.objects:
    if object.type == 'MESH':
        print('[>>>>] Exporting ', object.name ,'...')
        meshCount += 1
        
        objUV = None
        if len(object.data.uv_layers) > 0:
            objUV = object.data.uv_layers[0]
                
        objType = object.get('mesh_type', 'mesh')
        if objType == 'sphere':
            dbCursor.execute("INSERT INTO Geometry(type) VALUES(?)", ['SPHERE'])
            dbCursor.execute("INSERT INTO SphereGeometry(id, radius) VALUES(?, ?)", 
                [dbCursor.lastrowid, object.delta_scale[0]])
        elif objType == 'plane':
            dbCursor.execute("INSERT INTO Geometry(type) VALUES(?)", ['PLANE'])
            dbCursor.execute("INSERT INTO PlaneGeometry(id, width, height) VALUES(?, ?, ?)", 
                [dbCursor.lastrowid, object.delta_scale[0], object.delta_scale[1]])
        else:
            vertexPositionBuffer = bytes()
            vertexNormalBuffer = bytes()
            vertexUvBuffer = bytes()
                                        
            for face in object.data.polygons:
                faceVertexPosBuffer = bytes()
                faceVertexNormalBuffer = bytes()
                faceVertexUVBuffer = bytes()
                                                                
                for vert, loop in zip(face.vertices, face.loop_indices):
                    vert = object.data.vertices[vert]
                                        
                    faceVertexPosBuffer += struct.pack('fff', vert.co[0], vert.co[1], vert.co[2])
                    faceVertexNormalBuffer += struct.pack('fff', vert.normal[0], vert.normal[1], vert.normal[2])                                                           
                    if objUV is not None:
                        uv = objUV.data[loop].uv
                        faceVertexUVBuffer += struct.pack('ff', uv[0], uv[1])
                    else:
                        faceVertexUVBuffer += struct.pack('ff', 0.0, 0.0)                                         
                        
                vertexPositionBuffer += faceVertexPosBuffer
                vertexNormalBuffer   += faceVertexNormalBuffer
                vertexUvBuffer       += faceVertexUVBuffer
                
            dbCursor.execute("INSERT INTO Geometry(type) VALUES(?)", ['MESH'])
            dbCursor.execute("INSERT INTO MeshGeometry(id, points, normals, uvs) VALUES(?, ?, ?, ?)", 
                [dbCursor.lastrowid, vertexPositionBuffer, vertexNormalBuffer, vertexUvBuffer])
        geometryId = dbCursor.lastrowid
        if object.active_material is not None:
            materialId = materials[object.active_material.name]
        else:
            materialId = None
            
        dbCursor.execute("INSERT INTO SceneObject(name, geometryId, materialId, pos,"
            "rotation, scale, visible) VALUES(?, ?, ?, ?, ?, ?, ?)",
            [object.name, geometryId, materialId, 
            struct.pack('fff', object.location[0], object.location[1], object.location[2]),
            struct.pack('fff', object.rotation_euler[0], object.rotation_euler[1], object.rotation_euler[2]),
            struct.pack('fff', object.scale[0], object.scale[1], object.scale[2]),
            1]);
      
print('[<<<<]', meshCount, 'meshes written to the scene\n\n')
  
print('[>>>>] Exporting scene metadata...')

# Scene Metainfo
uniqueId = ''.join([random.choice(string.ascii_lowercase + string.digits) for n in range(32)])
scene = bpy.data.scenes[0]
dbCursor.execute("INSERT INTO Metainfo(uid, name, renderWidth, renderHeight) VALUES(?, ?, ?, ?)",
    [uniqueId, scene.name, scene.render.resolution_x, scene.render.resolution_y])

print('[<<<<] Metadata export completed\n\n')
                    
dbConnection.commit()
dbConnection.close()

print('[>>>>] Creating tar archive...')

scenePath = outputDirectory + uniqueId + '.tar';

tar = tarfile.open(scenePath, 'w');
tar.add(tmpDirectory, '')
tar.close()

print('[<<<<] Tar has been generated\n\n')

print('[>>>>] Rebuilding index...')

# TODO

print('[<<<<] Index has been rebuilt\n\n')


print('[SUCCESS] Scene export finished (' + uniqueId + '.tar)')