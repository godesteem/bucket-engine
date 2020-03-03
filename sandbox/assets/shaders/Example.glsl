#type vertex
#version 130

// Input vertex data, different for all executions of this shader.
in vec3 position;
in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  u_ViewProjection * vec4(position,1) * u_Transform;

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}


#type fragment
#version 130
// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

    // Output color = color of the texture at the specified UV
    color = texture( myTextureSampler, UV ).rgb;
}