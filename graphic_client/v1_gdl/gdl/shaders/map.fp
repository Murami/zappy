uniform vec4 color;
uniform sampler2D fTexture0;
uniform float time;
uniform vec2 resolution;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;

void main(void)
{
  vec2 cPos = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
  float cLen = length(cPos);

  vec2 uv = gl_FragCoord.xy / resolution.xy + (cPos / cLen) * cos(cLen*12.0-time*4.0)*0.03;
  uv.x = mod(uv.x, 1.0);
  uv.y = mod(uv.y, 1.0);
  vec3 col = texture2D(fTexture0, fUv).xyz;
  gl_FragColor = vec4(col, 1.0) * fColor;
}
