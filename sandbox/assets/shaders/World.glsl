#type vertex
#version 130
uniform mat4 model;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
  vec4 pos = u_ViewProjection * model * u_Transform * gl_Vertex;
  gl_Position = pos + vec4(0.0, 0.0, 0.0, 0.0);
}


#type fragment
#version 130
uniform mat4 u_Transform;

void main()
{
  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
