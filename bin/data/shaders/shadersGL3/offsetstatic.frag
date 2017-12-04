#version 150

uniform vec2 u_mouse;

#define PI 3.14159265359

out vec4 outputColour;

uniform vec2 u_resolution;
uniform float u_time;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
	st -= vec2(0.5);
	st = rotate2d( sin(u_time)*PI ) * st;
	st += vec2(0.5);
	st*=30;
	float iTime = floor(u_time*30);
	
    float rnd = random( floor(st) + iTime );

    outputColour = vec4(random(floor(st+0.1) + iTime), random( floor(st+0.2) + iTime ), random( floor(st+0.4) + iTime ),0.5);
}