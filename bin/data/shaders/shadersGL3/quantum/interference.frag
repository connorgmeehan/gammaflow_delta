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
        p += vec2(-0.5, -0.5);
        t += pulse;

        l = length(p); // distance from 0 coord
        //uv +=p*(sin(t + l*1.) + 0.5) * cos(l*20 - t*2. + snare)*hihat;
        uv.x += p.x*sin(l*20. - t*2.)*sin(l*5. + t*2.) - t/5;
        uv.y += p.y*cos(l*20. - t*2.)*sin(l)*l;
        //uv+= p*(sin(l/5 - t*10. )+0.5)*(cos(l*50. - t*10.)*);
        c[i] = (.1 + kick*0.1)/length(abs(mod(uv,1.)-.5));
    }
    outputColour = vec4(vec3(c), 1);
}