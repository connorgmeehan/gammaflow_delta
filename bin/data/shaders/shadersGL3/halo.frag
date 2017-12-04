#version 150


out vec4 outputColour;

uniform vec2 u_resolution;
uniform float u_time;
uniform float pulse;
uniform vec2 u_translate;

uniform float param1;
uniform float param2;
uniform float param3;

out vec4 fragColor;

void main(){
    vec2 fragCoord = gl_FragCoord.xy;
	vec3 c;
	float l,z=u_time;
	for(int i=0;i<3;i++) {
		vec2 uv,p=fragCoord.xy/u_resolution;
		uv=p;
		p-=u_translate;
		p.x*=u_resolution.x/u_resolution.y;
		z+=pulse/10;
		l=length(p);
		uv+=p/l*(sin(z)+param1)*abs(sin(l*10.-z*2.));
		c[i]=.01/length(abs(mod(uv,1.)-.5));
	}
	fragColor=vec4(c/l,u_time);
}