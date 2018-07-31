#version 330 core

in vec2 texCoord;
uniform sampler2D texBuf;
uniform vec2 frame;
out vec4 color;

void main(){
   //neighbors 
   vec4 color0 = vec4(texture( texBuf, vec2(texCoord.x, texCoord.y-(2.0/frame.y)) ).rgb, 1);
   vec4 color1 = vec4(texture( texBuf, vec2(texCoord.x, texCoord.y-(1.0/frame.y)) ).rgb, 1);
   vec4 color2 = vec4(texture( texBuf, texCoord ).rgb, 1);
   vec4 color3 = vec4(texture( texBuf, vec2(texCoord.x, texCoord.y+(1.0/frame.y)) ).rgb, 1);
   vec4 color4 = vec4(texture( texBuf, vec2(texCoord.x, texCoord.y+(2.0/frame.y)) ).rgb, 1);

   float r = (color0.r + 4*color1.r + 6*color2.r + 4*color3.r + color4.r)/16.0;
   float g = (color0.g + 4*color1.g + 6*color2.g + 4*color3.g + color4.g)/16.0;
   float b = (color0.b + 4*color1.b + 6*color2.b + 4*color3.b + color4.b)/16.0;

   //parsed color
   color = vec4(r, g, b, 1.0);
}
