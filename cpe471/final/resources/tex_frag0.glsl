#version 330 core
uniform sampler2D Texture0;

in vec2 vTexCoord;
in vec3 vColor;
in vec3 fragNor;

uniform float IL;

out vec4 Outcolor;

void main() {
   vec4 BaseColor = vec4(vColor.x, vColor.y, vColor.z, 1) * IL;
   vec4 texColor0 = texture(Texture0, vTexCoord) * IL;
   Outcolor = vec4(texColor0.r*vColor.r, texColor0.g*vColor.g, texColor0.b*vColor.b, 1);
   if (Outcolor.r <= 0.00001 && Outcolor.g <= 0.00001 && Outcolor.b <= 0.00001) {
      Outcolor = vec4(0.2*IL, 0.6*IL, 0.2*IL, 1.0);
   }
}

