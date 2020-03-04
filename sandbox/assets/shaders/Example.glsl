#type vertex
#version 130

in vec4 v_coord;
in vec3 u_Normal;

uniform mat4 model;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = u_ViewProjection * model * u_Transform * gl_Vertex;
}


#type fragment
#version 130
in vec4 color;
in vec3 Normal;
in vec3 FragPos;

uniform mat4 u_Transform;

out vec4 FragColor;
vec3 objectColor = vec3(1.0, 1.0, 0.0);
vec3 lightColor = vec3(1.0, 1.0, 1.0);
vec3 lightPos = vec3(-1.0, -1.0, 0.0);
void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
