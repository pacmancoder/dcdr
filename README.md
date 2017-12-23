DCDR
===
#### Distributed Computing Distributed Raytracer

__Last result__  
![Last result](res/images/spheres_01.png)

### CheckList

Implemented:
- Math
    - [x] Vector3D
    - [x] Matrix4D
- Camera
    - [x] Depth of view
    - [x] Look at
    - [ ] Aperture shape
- Sphere
    - [x] Intersection
    - [ ] UV mapping selection
- Rasterizer
    - [x] Chunk-based rendering
    - [x] PPM rasterizer
    - [ ] Realtime surface rasterizer
    - [ ] Parallelization (CPU)

### Running dcdr-server
execute the following for allowing dcdr-server to bind 80 port
```bash
sudo setcap 'cap_net_bind_service=+ep' $PATH_TO_DCDR_SERVER
```
