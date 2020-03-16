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
//    gl_Position = u_ViewProjection * model * u_Transform * gl_Vertex;
//    FragPos = vec3(model * v_coord);
//    Normal = u_Normal;
//    color = vec4(FragPos, 1.0);
    vec3 normal, lightDir;
    vec4 diffuse, ambient, globalAmbient;
    float NdotL;

    Normal = normalize(gl_NormalMatrix * gl_Normal);
    lightDir = normalize(vec3(gl_LightSource[0].position));
    NdotL = max(dot(normal, lightDir), 0.0);
    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    /* Compute the ambient and globalAmbient terms */

    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
    globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
    gl_FrontColor =  NdotL * diffuse + globalAmbient + ambient;

    gl_Position = u_ViewProjection * model * u_Transform * gl_Vertex;
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
    gl_FragColor = gl_Color;
}
