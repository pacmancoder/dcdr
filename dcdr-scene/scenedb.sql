CREATE TABLE Metainfo (
    uid TEXT,
    name TEXT,
    renderWidth INTEGER,
    renderHeight INTEGER
);

CREATE TABLE Geometry (
    id INTEGER PRIMARY KEY,
    type TEXT
);

CREATE TABLE PlaneGeometry (
    id INTEGER PRIMARY KEY,
    width REAL,
    height REAL
);

CREATE TABLE SphereGeometry (
    id INTEGER PRIMARY KEY,
    radius REAL
);

CREATE TABLE MeshGeometry (
    id INTEGER PRIMARY KEY,
    points BLOB,
    normals BLOB,
    uvs BLOB
);


CREATE TABLE Texture (
    id INTEGER PRIMARY KEY,
    type TEXT
);

CREATE TABLE ColorTexture (
    id INTEGER PRIMARY KEY,
    r REAL,
    g REAL,
    b REAL
);

CREATE TABLE BitmapTexture (
    id INTEGER PRIMARY KEY,
    format TEXT,
    path TEXT,
    channels TEXT,
    filter TEXT
);

CREATE TABLE Material (
    id INTEGER PRIMARY KEY,
    bumpTexId INTEGER,
    duffuseTexId INTEGER,
    glossinessTexId INTEGER,
    refractionGlossinessTexId INTEGER,
    kAmbient REAL,
    kDiffuse REAL,
    kReflectance REAL,
    kGlossiness REAL,
    kRefractionGlossiness REAL,
    kTransmittance REAL,
    kIOR REAL,
    kEmittance REAL
);

CREATE TABLE SceneObject (
    id INTEGER PRIMARY KEY,
    name TEXT,
    geometryId INTEGER,
    materialId INTEGER,
    pos BLOB,
    rotation BLOB,
    scale BLOB,
    visible INTEGER
);

CREATE TABLE Camera (
    id INTEGER PRIMARY KEY,
    pos BLOB,
    rotation BLOB,
    fov REAL,
    dofDistance REAL,
    dofRadius REAL
);
