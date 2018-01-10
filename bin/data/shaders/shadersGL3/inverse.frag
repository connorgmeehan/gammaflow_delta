#version 150
uniform sampler2DRect tex0;
uniform sampler2DRect tex;

in vec2 texCoordVarying;

out vec4 fragColor;

void main(){
    vec4 textureColor = texture(tex, vec2(gl_FragCoord.x, 768 - gl_FragCoord.y));
    fragColor = vec4(1.0 - textureColor.r,1.0 -textureColor.g,1.0 -textureColor.b,textureColor.a);
}