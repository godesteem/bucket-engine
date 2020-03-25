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
    color.a = 0.1;
}


#type fragment
#version 130
in vec4 color;
in vec3 Normal;
in vec3 FragPos;

uniform mat4 u_Transform;

vec4 col;

void main() {
    col = color;
    col.a = 0.0f;
    gl_FragColor = color;
}
