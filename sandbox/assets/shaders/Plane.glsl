#type vertex
#version 130
in vec3 position;
in vec2 textCord;

uniform mat4 model;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec2 v_TextCord;

void main() {
  v_TextCord = textCord;
  gl_Position = u_ViewProjection * model * u_Transform * gl_Vertex * vec4(position, 1.0);
}


#type fragment
#version 130
in vec2 v_TextCord;

out vec4 color;

uniform sampler2D u_Texture;

void main() {
  color = texture(u_Texture, v_TextCord);
}

