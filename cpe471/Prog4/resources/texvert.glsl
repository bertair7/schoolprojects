#version 330 core
layout (location = 0) in vec3 vertPos;
uniform mat4 P;
uniform mat4 M;
uniform mat4 V;

out vec2 TexCoords;

void main() 
{
   gl_Position = P * V * M * vec4(vertPos.xyz, 1.0);
   TexCoords = (vertPos.xy+vec2(1,1))/2.0;
}
