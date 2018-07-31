#version  330 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec3 vertNor;
layout(location = 2) in vec2 vertTex;
uniform mat4 P;
uniform mat4 MV;
uniform vec3 light;
out vec3 li;
out vec3 viewPos;
out vec3 fragNor;

void main()
{
	gl_Position = P * MV * vertPos;
	fragNor = (MV * vec4(vertNor, 0.0)).xyz;
   li = vec3(light - (MV * vertPos).xyz);
   viewPos = vec3(-(MV * vertPos).xyz);
}
