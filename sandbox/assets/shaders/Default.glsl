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

float near = 0.1;
float far  = 100.0;

void LinearizeDepth(float depth, float depthOut)
{
  float z = depth * 2.0 - 1.0; // back to NDC
  depthOut = (2.0 * near * far) / (far + near - z * (far - near));
}

void main() {
  float depth;
  LinearizeDepth(gl_FragCoord.z, depth);
  depth = depth / far; // divide by far for demonstration
  color = vec4(vec3(depth), 1.0);

}


