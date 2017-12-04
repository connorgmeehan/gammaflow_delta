#version 150
 
out vec4 outputF;
 
void main()
{   

    float dist = mod(gl_FragCoord.x, 100);
    outputF = vec3(dist/100);
}