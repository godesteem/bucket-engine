#type vertex
#version 130

in vec4 v_coord;
in vec3 u_Normal;

uniform mat4 model;
uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;
uniform mat3 m_3x3_inv_transp;

out vec4 color;

void main(void)
{
    mat4 mvp = u_ViewProjection * model * u_Transform;
    gl_Position = mvp * gl_Vertex;
    color = gl_Vertex;
    gl_TexCoord[0]  = gl_MultiTexCoord0;
}


#type fragment
#version 130
in vec4 color;
uniform mat4 u_Transform;

void main()
{             
    if(color.x < 0.25)
        gl_FragColor = vec4(0.1, 0.2, 1.0, 1.0);
    else
        gl_FragColor = vec4(0.2, 1.0, 1.0, 1.0);        
}  
