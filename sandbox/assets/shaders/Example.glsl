#type vertex
#version 130

// Input vertex data, different for all executions of this shader.
in vec3 position;
in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 u_Pos;

// Values that stay constant for the whole mesh.
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat4 model;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  u_ViewProjection * model * u_Transform * vec4(position, 1.0);
    u_Pos = gl_Position;
    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}


#type fragment
#version 130
// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 u_Pos;

// Ouput data
out vec4 color;


void main() {
    color = u_Pos;
}
