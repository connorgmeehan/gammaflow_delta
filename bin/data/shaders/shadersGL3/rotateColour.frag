#version 150
uniform sampler2DRect tex;

in vec2 texCoordVarying;

out vec4 fragColor;

void main(){
    vec4 textureColor = texture(tex, vec2(gl_FragCoord.x, gl_FragCoord.y));
    textureColor.rgb = cos(vec3(textureColor.r, textureColor.g, textureColor.b)*1.5);
    fragColor = vec4(textureColor);
}