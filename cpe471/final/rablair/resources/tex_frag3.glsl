#version 330 core
uniform sampler2D Texture3;
uniform float IL;

in vec2 vTexCoord;
in vec3 vColor;
in vec3 fragNor;

out vec4 Outcolor;

void main() {
   vec4 BaseColor = vec4(vColor.x, vColor.y, vColor.z, 1) * IL;
   vec4 texColor0 = texture(Texture3, vTexCoord) * IL;
   Outcolor = vec4(texColor0.r*vColor.r, texColor0.g*vColor.g, texColor0.b*vColor.b, 1);
}

