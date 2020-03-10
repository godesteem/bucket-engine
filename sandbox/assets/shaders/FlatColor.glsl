#type vertex
#version 130
in vec3 position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;

void main() {
  v_Position = position;

  vec4 point[5];
  point[0] = vec4(0.31, 0.26, 0.42, 0.0);
  point[1] = vec4(0.28, 0.64, 0.30, 0.0);
  point[2] = vec4(0.60, 0.07, 0.01, 0.0);
  point[3] = vec4(0.83, 0.75, 0.10, 0.0);
  point[4] = u_ViewProjection * u_Transform * vec4(position, 1.0);

  float m_dist = 1.0;

  for(int i=0; i<5; i++){
    float dist = distance(gl_Position, point[i]);
    m_dist = min(m_dist, dist);
  }
  gl_Position = point[4];
}


#type fragment
#version 130
in vec3 v_Position;
uniform vec3 u_Color;
out vec4 color;
void main() {
  color = vec4(u_Color, 1.0);
}

