#version 120

uniform sampler2D fTexture0;
uniform vec4 color;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;

void main(void)
{
  vec2 Uv = fUv;
  Uv.x = mod(Uv.x, 1.0);
  Uv.y = mod(Uv.y, 1.0);
  vec4 colorTex = texture2D(fTexture0, Uv);
  colorTex.a = 1;
  gl_FragColor = colorTex * fColor * color;
}
