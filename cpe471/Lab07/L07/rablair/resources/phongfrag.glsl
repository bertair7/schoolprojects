#version 330 core 
in vec3 L;
in vec3 fragNor;
uniform vec3 kd;
uniform vec3 ka;
uniform vec3 IL;
out vec4 Fcolor;

void main()
{
	vec3 color = (kd * (dot(normalize(fragNor), normalize(L))) * IL) + (ka * IL);
	Fcolor = vec4(color, 1.0);
}
