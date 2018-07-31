#version 330 core 
in vec3 li;
in vec3 viewPos;
in vec3 fragNor;
uniform vec3 kd;
uniform vec3 ka;
uniform vec3 ks;
uniform float shine;
uniform vec3 IL;
out vec4 color;

void main()
{
   vec3 N = normalize(fragNor);
   vec3 L = normalize(li);
   vec3 V = normalize(viewPos);
   vec3 H = normalize(L + V);

	vec3 diffuse = kd * max(dot(N, L), 0.0) * IL;
   vec3 spec = ks * pow(max(dot(N, H), 0.0), shine) * IL;
   vec3 amb = ka * IL;

   vec3 Ncolor = diffuse + spec + amb;
   color = vec4(Ncolor, 1.0);
}
