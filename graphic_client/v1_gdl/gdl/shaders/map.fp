uniform vec4 color;
uniform sampler2D fTexture0;
uniform float time;
uniform vec2 resolution;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;

void main(void)
{
  vec2 Uv = fUv;
  Uv.x = mod(Uv.x, 1.0);
  Uv.y = mod(Uv.y, 1.0);
  gl_FragColor = texture2D(fTexture0, Uv) * fColor * color;
}
