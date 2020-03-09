#type vertex
#version 130

in vec4 v_coord;
in vec3 u_Normal;

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
}


#type fragment
#version 130
in vec4 color;
in vec3 Normal;
in vec3 FragPos;

uniform mat4 u_Transform;

out vec4 FragColor;
vec3 objectColor = vec3(1.0, 0.2, 0.0);
vec3 lightColor = vec3(1.0, 1.0, 1.0);
vec3 lightPos = vec3(-1.0, -1.0, 0.0);
void main()
{
    FragColor = gl_FragCoord;
}
