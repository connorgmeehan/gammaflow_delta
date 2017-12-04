#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;

void main(){
	vec4 pos = position
	pos.u += sin(pos.u*10);
	gl_Position = modelViewProjectionMatrix * position;
}
