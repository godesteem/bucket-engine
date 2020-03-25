# Bucket Engine

C++ 3D/2D-Game Engine inspired by the YouTube series of "The Cherno".


### Current supported platforms:
currently only the support for OpenGL 3 is implemented, but the necessary
API is already present to add other engines/backends.

- [x] Linux: OpenGL 3
- [x] Windows: OpenGL 3
- [x] MacOS: OpenGL 3
- [x] XBox 360: OpenGL 3
- [x] Playstation 2/3/4: OpenGL 3
- [ ] XBox One:
- [ ] HTML5: WebGL

Next step: Vulkan


## Development
1) close repository `git clone --recurse-submodules -j8 git://github.com/godesteem/bucket-engine.git`
1) run `cd engine/vendor/spdlog && cmake . && make` 
1) develop
1) run `build.sh`


## usage

### Minimal setup see `/minimal/src/Minimal.cpp`
- create child from `Application`
- define `Engine::Application* Engine::CreateApplication()`