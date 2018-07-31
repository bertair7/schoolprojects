#version 330 core
in vec3 fragmentColor;
uniform vec2 center;
out vec3 color;

void main()
{
	color = fragmentColor;
   if (distance(center, gl_FragCoord.xy) < 130) {
     color = vec3(0.0, 0.12, 1.0);
   }
   else {
      color = vec3(0.0, 0.38-0.002*distance(center, gl_FragCoord.xy), 1.39-0.003*distance(center, gl_FragCoord.xy));
   }
}
