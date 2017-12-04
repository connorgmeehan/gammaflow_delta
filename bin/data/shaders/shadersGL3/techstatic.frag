#version 150

out vec4 outputColour;

uniform vec2 u_resolution;
uniform float u_time;

#define PI 3.14159265358979323846

vec2 rotate2D(vec2 _st, float _angle){
    _st -= 0.5;
    _st =  mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle)) * _st;
    _st += 0.5;
    return _st;
}

vec2 odd(vec2 _st, float scale){
    _st.x *= scale;
    _st.x += step(1., mod(_st.y,2.0)) * 2.0;
    return fract(_st);
}

void main(void){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st = odd(st, 20.0);
    outputColour = vec4( vec3( step( 0.025, mod(st.x, 0.05))), 1.0);
}