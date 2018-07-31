#version 330 core 
in vec3 color;
out vec4 Fcolor;

void main()
{
	//vec3 normal = normalize(fragNor);
	// Map normal in the range [-1, 1] to color in range [0, 1];
	//vec3 Ncolor = 0.5*normal + 0.5;
	Fcolor = vec4(color, 1.0);
}
