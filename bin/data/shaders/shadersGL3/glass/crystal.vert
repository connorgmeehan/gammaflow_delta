#version 150

uniform mat4 modelViewProjectionMatrix;

uniform vec3  LightPosition;
uniform vec3  SurfaceColor;
uniform vec3  Offset;
uniform float ScaleIn;
uniform float ScaleOut;
varying vec4  Color;
 
void main()
{
    vec3 normal = gl_Normal;
    vec3 vertex = gl_Vertex.xyz +
                  noise3(Offset + gl_Vertex.xyz * ScaleIn) * ScaleOut;
 
    // Posting question 1: this normal I think is wrong, dont we need to recalculate first?
    normal = normalize(gl_NormalMatrix * normal);
    vec3 position = vec3(gl_ModelViewMatrix * vec4(vertex,1.0));
    vec3 lightVec = normalize(LightPosition - position);
    float diffuse = max(dot(lightVec, normal), 0.0);
 
    if (diffuse < 0.125)
         diffuse = 0.125;
 
    Color = vec4(SurfaceColor * diffuse, 1.0);
 
    // Posting question 2: dont we need to save the new vertex normal for future calculations
    gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex,1.0);
}   