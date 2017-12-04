#version 150

uniform vec2 u_resolution;
uniform float u_time;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float pulse;

out vec4 outputColour;


void main(void)
{
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / u_resolution.xy;
    p.x *= u_resolution.x/u_resolution.y;

    float zoo = .62+.39*sin(.1*u_time);
    float coa = cos( 0.09*(1.0-zoo)*u_time );
    float sia = sin( 0.1*(1.0-zoo)*u_time );
    zoo = pow( zoo,8.0);
    vec2 xy = vec2( p.x*coa-p.y*sia, p.x*sia+p.y*coa)*pulse;
    vec2 cc = vec2(-.745,.186) + xy*zoo;

    vec2 z  = vec2(0.0);
    vec2 z2 = z*z;
    float m2;
    float co = 0.0;


    // chrome/angelproject/nvidia/glslES don't seem to like to "break" a loop...
    // so we have to rewrite it in another way

    for( int i=0; i<256; i++ )
    {
        if( m2<1024.0 )
        {
            z = cc + vec2( z.x*z.x - z.y*z.y, 2.0*z.x*z.y );
            m2 = dot(z,z);
            co += 1.0;
        }
    }

    co = co + 1.0 - log2(.5*log2(m2));

    co = sqrt(co/256.0);
    outputColour = vec4( .5+.5*cos(6.2831*co+0.0),
                         .5+.5*cos(6.2831*co+0.4),
                         .5+.5*cos(6.2831*co+0.7),
                         1.0 );
}
    