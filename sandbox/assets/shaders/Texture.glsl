#type vertex
#version 130
in vec3 position;
in vec2 textCord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TextCord;

void main() {
  v_TextCord = textCord;
  gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
}


#type fragment
#version 130
in vec2 v_TextCord;

out vec4 color;

uniform sampler2D u_Texture;

void main() {
  color = texture(u_Texture, v_TextCord);
}

