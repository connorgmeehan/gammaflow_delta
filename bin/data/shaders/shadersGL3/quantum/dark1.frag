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

void main(){
    vec3 c;
    float l, t = u_time;
    for(int i = 0; i < 3; i++){ // calc rgb offset;
        vec2 uv, p = gl_FragCoord.xy/u_resolution;
        uv = p;
        p += vec2(-0.5, -0.5);
        l = length(p); // distance from 0 coord
        t += snare/2*l;

        uv+= p*(sin(l*10 - t )+0.2)*(cos(l*5.37659 - t))/l;
        c[i] = .03/length(abs(mod(uv,1.)-.5))*(0.01 + kick/20);
    }
    outputColour = vec4(c*100, u_time);
}