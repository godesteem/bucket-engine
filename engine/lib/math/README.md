# Math

- matrix.h
- vector.h

## vector.h

### Structs

- vec2:
    - float
    - constructors:
        - `vec2() = {0.0, 0.0}`
        - `vec2(x) = {x, x}`
        - `vec2(x, y) = {x, y}`
        - `Orthogonal()`
    - functions:
        - `Dot(vec2 a, vec2 b)`
- vec3
    - float
    - constructors:
        - `vec3()        = {0.0, 0.0, 0.0}`
        - `vec3(x)       = {  x,   x,   x}`
        - `vec3(x, y)    = {  x,   y, 0.0}`
        - `vec3(x, y, z) = {  x,   y,   z}`
        - `Orthogonal()`
    - functions:
        - `Dot(vec3 a, vec3 b)`
        - `CrossProduct(vec3 a, vec3 b)`


### Methods:
- `Length(const T& vec)`: Vector length
-