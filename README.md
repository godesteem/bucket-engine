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


## [Docs](https://godesteem.github.io/bucket-engine/index.html) ![Deploy to GitHub Pages](https://github.com/godesteem/bucket-engine/workflows/Deploy%20to%20GitHub%20Pages/badge.svg)
1) Install [doxygen](http://www.doxygen.nl/manual/install.html)
1) Run `doxygen docs/doxygen.conf` to generate docs in `docs/`