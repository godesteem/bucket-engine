#type vertex
#version 130
in vec3 position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;

void main() {
  v_Position = position;
  gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
}


#type fragment
#version 130
in vec3 v_Position;
uniform vec3 u_Color;
out vec4 color;
void main() {
  color = vec4(u_Color, 1.0);
}

