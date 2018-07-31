#version 330 core 
in vec3 view;
in vec3 fragNor;
uniform vec2 center;
out vec4 color;

void main()
{
   vec3 v = normalize(view);
	vec3 normal = normalize(fragNor);

   color = vec4(0.0, 0.0, 0.0, 1.0);
   if (dot(normal, v) > 0) {
      discard;
   }
   else {
      if (distance(center, gl_FragCoord.xy) > 150) {
         float p = -3.0 + 0.02*distance(center, gl_FragCoord.xy);
         color = vec4(p, p, p, 1.0);
      }
   }
}
