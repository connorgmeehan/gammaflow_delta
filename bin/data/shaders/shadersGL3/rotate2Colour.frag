#version 150
uniform sampler2DRect tex;
uniform sampler2DRect tex0;

in vec2 texCoordVarying;

out vec4 fragColor;

void main(){

    float blendMultiplier = 90;

    vec4 textureColour = texture(tex, vec2(gl_FragCoord.x, 768 - gl_FragCoord.y));
    vec4 textureColour0 = texture(tex0, vec2(gl_FragCoord.x, 768 - gl_FragCoord.y));

    if(textureColour.a == 0){
        fragColor = vec4( cos( radians(
            vec3(textureColour.r, textureColour.g, textureColour.b)*blendMultiplier -
            vec3(textureColour0.r, textureColour0.g, textureColour0.b)*blendMultiplier
        ) ), 1.0); 
    } else {
        
    }

    fragColor = vec4( cos( radians(
        vec3(textureColour.r, textureColour.g, textureColour.b)*blendMultiplier -
        vec3(textureColour0.r, textureColour0.g, textureColour0.b)*blendMultiplier
    ) ), 1.0);
}