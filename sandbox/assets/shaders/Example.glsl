#type vertex
#version 130

in vec4 v_coord;
in vec3 u_Normal;
in vec3 position;

uniform mat4 model;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec4 color;
out vec3 Normal;
out vec3 FragPos;
void main()
{
    gl_Position = u_ViewProjection * model * u_Transform * gl_Vertex;
    FragPos = vec3(model * v_coord);
    Normal = u_Normal;
    color.rgb = position;
    color.a = 1.0;
}


#type fragment
#version 130
in vec4 color;
in vec3 Normal;
in vec3 FragPos;

uniform mat4 u_Transform;

out vec4 FragColor;

float random (in vec2 _st) {
    return fract(sin(dot(_st.xy,
    vec2(12.9898, 78.233)))*
    43758.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 _st) {
    vec2 i = floor(_st);
    vec2 f = fract(_st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
    (c - a)* u.y * (1.0 - u.x) +
    (d - b) * u.x * u.y;
}

    #define NUM_OCTAVES 5

float fbm (in vec2 _st) {
    float v = 0.0;
    float a = 0.5;
    vec2 shift = vec2(100.0);
    // Rotate to reduce axial bias
    mat2 rot = mat2(cos(0.5), sin(0.5),
    -sin(0.5), cos(0.50));
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(_st);
        _st = rot * _st * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}

void main() {
    gl_FragColor = color;
}
