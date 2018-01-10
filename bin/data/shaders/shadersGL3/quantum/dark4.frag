#version 150

#define PI 3.1415926535897932384626433832

out vec4 outputColour;

uniform vec2 u_resolution; // 2d vector of screen resolution
uniform float u_time; // inputs ofGetTimeElapsedf()
uniform float volume; // stores the general volume of the song
uniform vec2 u_translate; //2d vector that can be used to offset uv variable

// beat floats store the amplitude of each beat
uniform float kick;
uniform float snare;
uniform float hihat;

// momentum variables store a 3d vector of momentum 
// in a randomised direction that is based off the velocity of the beat
uniform vec3 kickmom;
uniform vec3 snaremom;
uniform vec3 hihatmom;

uniform vec3 kickpos;
uniform vec3 snarepos;
uniform vec3 hihatpos;

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

float atan2(in float y, in float x)
{
    return x == 0.0 ? sign(y)*PI/2 : atan(y, x);
}

void main(){
    vec3 c;
    float l, t = u_time;
    for(int i = 0; i < 3; i++){ // calc rgb offset;
        vec2 uv, p = gl_FragCoord.xy/u_resolution;
        uv = p;
        p += vec2(-0.5, -0.5);
        float theta = atan2(p.x, p.y);
        float baseRadius = (.05/length(p)/(2-kick*0.1) + -1/(1-length(p)) );
        float noiseRadius = (sin(theta))*snoise(vec2(kickpos.x/10, theta));
        float lightOffset = snare*i*0.08;
        l = baseRadius + noiseRadius + lightOffset; // distance from 0 coord
        c[i] = 0.05/length(abs(mod(l, 1)-.5));
    }
    outputColour = vec4(c, u_time);
}