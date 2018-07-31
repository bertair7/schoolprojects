#version 330 core 
uniform vec2 center;
out vec4 color;

void main()
{
	vec3 Ncolor = vec3(1.2-0.005*distance(center, gl_FragCoord.xy), 0.0, -0.5+0.07*distance(center, gl_FragCoord.xy));
	color = vec4(Ncolor, 1.0);
}
