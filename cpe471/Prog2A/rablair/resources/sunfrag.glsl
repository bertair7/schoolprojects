#version 330 core
in vec3 fragmentColor;
uniform vec2 center;
out vec3 color;

void main()
{
	color = fragmentColor;
   if (distance(center, gl_FragCoord.xy) < 77) {
      color = vec3(1.0, 1.0, 0.008*distance(center, gl_FragCoord.xy));
      if (color.b > 1.0)
         color.b = 1.0;
   }
   else {
      color = vec3(1.0, 0.1+0.007*distance(center, gl_FragCoord.xy), 0.1+0.001*distance(center, gl_FragCoord.xy));
   }
}
