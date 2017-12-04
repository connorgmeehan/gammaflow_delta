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

out vec4 fragColor;

void main(){
    vec3 c;
    float l, t = u_time;
    for(int i = 0; i < 3; i++){ // calc rgb offset;
        vec2 uv, p = gl_FragCoord.xy/u_resolution;
        uv = p;
        p.x-= u_translate.x;
        p.y += u_translate.y;
        t += pulse/5;

        l = length(p); // distance from 0 coord
        uv.x += p.x*sin(l*5. - t*5.)*sin(l*2. + t*5.)*2;
        uv.y += p.y*cos(l*5.- t*5.)*sin(l*2.)*10*tan(l);
        //uv+= p*(sin(l/5 - t*10. )+0.5)*(cos(l*50. - t*10.)*);
        c[i] = length(abs(mod(uv,1.)-.5))/l/50;
    }
    outputColour = vec4(c*t/100, u_time);
}