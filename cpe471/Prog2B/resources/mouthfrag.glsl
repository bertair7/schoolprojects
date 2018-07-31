#version 330 core 
uniform vec2 point;
out vec4 color;

void main()
{
	vec3 Ncolor = vec3(0.0, 0.0, 0.0);
	color = vec4(Ncolor, 1.0);

   if (distance(point, gl_FragCoord.xy) < 20)
      color = vec4(1.0, 0.0, 0.0, 1.0);
}
