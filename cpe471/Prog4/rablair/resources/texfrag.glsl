#version 330 core
in vec2 TexCoords;
uniform sampler2D texBuf;
out vec4 color;

void main() 
{
   color = texture(texBuf, TexCoords);
   color.x -= 0.03;
   color.y -= 0.03;
   color.z -= 0.03;
}
