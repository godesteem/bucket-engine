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
  //https://coolors.co/394053-a3d9ff-dceed1-4cb963-7a7978
  if(y>0.25)            col = vec3(122.0/255.0, 121.0/255.0, 120.0/255.0);
  if(-0.25<y && y<0.00) col = vec3(220.0/255.0, 238.0/255.0, 209.0/255.0);
  if( 0.00<y && y<0.25) col = vec3(76.0/255.0, 185.0/255.0, 99.0/255.0);
  if(-0.25>y)           col = vec3(163.0/255.0, 217.0/255.0, 255.0/255.0);
  if(-0.35>y)           col = vec3(57.0/255.0, 64.0/255.0, 83.0/255.0);
  FragColor.rgb = col;
  FragColor.a = 1.0f;
}
