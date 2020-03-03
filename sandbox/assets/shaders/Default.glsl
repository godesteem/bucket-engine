#type vertex
#version 130
in vec3 u_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat4 model;
uniform vec4 u_Color;

out vec3 v_Position;
out vec4 v_Color;
void main()
{
  v_Position = u_Normal;
  v_Color = u_Color;
  gl_Position = u_ViewProjection * model * u_Transform * vec4(u_Normal, 1.0);
}

#type fragment
#version 130
in vec4 v_Color;
in vec3 v_Position;
out vec4 color;
void main() {
  color = vec4(v_Position * 0.5 + 0.5, 1.0);
  color = v_Color;
}


