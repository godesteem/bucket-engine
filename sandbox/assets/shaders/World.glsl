#type vertex
#version 130
uniform mat4 model;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;
in vec3 position;

out vec3 v_Position;

void main()
{
  vec4 pos = u_ViewProjection * model * u_Transform * gl_Vertex;
  gl_Position = pos;
  v_Position = (model * u_Transform * gl_Vertex).xyz;
}


#type fragment
#version 130
uniform mat4 u_Transform;

in vec3 v_Position;
out vec4 FragColor;
void main()
{
  float y = v_Position.y;
  vec3 col;
  if(y>0.25) col = vec3(0.8, 0.0f, 0.0f);
  if(-0.25<y && y<0.25) col = vec3(0.0f, 0.8, 0.0f);
  if(-0.25>y) col = vec3(0.0f, 0.0f, 0.8);
  FragColor.rgb = col;
  FragColor.a = 1.0f;
}
