#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertexColor;
uniform mat4 P;
uniform mat4 MV;
uniform vec2 v;
uniform float t;
out vec3 fragmentColor;

void main()
{
   vec2 vec = vec2(v.x*vertPos.x, v.y*vertPos.y); 
	//gl_Position = P * MV * vec4(vertPos, 1.0);
   gl_Position = P * MV * vec4(vertPos.xy + t*vec*vertPos.z, vertPos.z, 1.0);
     
   fragmentColor = vertexColor;
}
