// fragment shader
#version 150

out vec4 outputColour;

uniform vec2 u_resolution;
uniform float u_time;
uniform float pulse;
uniform vec2 u_translate;

uniform float param1;
uniform float param2;
uniform float param3;

uniform float kick;
uniform float snare;
uniform float hihat;

vec3 permute(vec3 x) { return mod(((x*34.0)+1.0)*x, 289.0); }

float snoise(vec2 v){
  const vec4 C = vec4(0.211324865405187, 0.366025403784439,
           -0.577350269189626, 0.024390243902439);
  vec2 i  = floor(v + dot(v, C.yy) );
  vec2 x0 = v -   i + dot(i, C.xx);
  vec2 i1;
  i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
  vec4 x12 = x0.xyxy + C.xxzz;
  x12.xy -= i1;
  i = mod(i, 289.0);
  vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
  + i.x + vec3(0.0, i1.x, 1.0 ));
  vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy),
    dot(x12.zw,x12.zw)), 0.0);
  m = m*m ;
  m = m*m ;
  vec3 x = 2.0 * fract(p * C.www) - 1.0;
  vec3 h = abs(x) - 0.5;
  vec3 ox = floor(x + 0.5);
  vec3 a0 = x - ox;
  m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
  vec3 g;
  g.x  = a0.x  * x0.x  + h.x  * x0.y;
  g.yz = a0.yz * x12.xz + h.yz * x12.yw;
  return 130.0 * dot(m, g);
}


void main(){

    //settings
    float ribSpacing = 0.01;
    float t = u_time + kick/2;

    vec3 c;

    for(int i = 0; i < 3; i++){
        vec2 uv = gl_FragCoord.yx/ u_resolution;

        uv += vec2(-0.5, -0.5);
        uv += vec2( 
            cos(length(uv.x+u_time/5)*10)+snoise(vec2(uv.x*5,t))/(snare*0.1+10)*5,
            cos(length(uv.y)*10)+snoise(vec2(uv.x*5,t))/(snare*0.1+10)*5
        );

        uv += vec2(
            sin(snoise(vec2(uv.x,1)))*sin(snoise(vec2(uv.x,1))),
            cos(snoise(vec2(uv.y,1)))*cos(snoise(vec2(uv.y,1)))
        );
        uv += length(uv*(-0.6 + i*0.3));

        c[i] = .3/length(uv*(5-kick))+(i*0.003);
    }
    outputColour = vec4( c, 1.0);
}