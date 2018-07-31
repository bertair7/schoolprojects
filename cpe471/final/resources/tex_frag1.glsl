#version 330 core
uniform sampler2D Texture1;

in vec2 vTexCoord;
in vec3 vColor;

uniform float IL;

out vec4 Outcolor;

void main() {
  vec4 BaseColor = vec4(vColor.x, vColor.y, vColor.z, 1) * IL;
  vec4 texColor1 = texture(Texture1, vTexCoord) + IL;

  Outcolor = vec4(texColor1.r*vColor.r, texColor1.g*vColor.g, texColor1.b*vColor.b, 1);
}

