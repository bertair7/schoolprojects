#version 330 core
in vec3 fragmentColor;
out vec3 color;

uniform vec2 center;

void main()
{
   if (distance(center, gl_FragCoord.xy) < 20.0) {
      discard;
   }
   else {
      color = fragmentColor;
      color = color + 0.01*distance(center, gl_FragCoord.xy);
      if (color.r > 1.0)
         color.r = 1.0;
      if (color.g > 1.0)
         color.g = 1.0;
      if (color.b > 1.0)
         color.b = 1.0;
   }
}
