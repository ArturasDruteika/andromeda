#version 330 core
in vec3 gWorldPos;

uniform vec3 u_light_pos;
uniform float u_far_plane;

void main()
{
    float lightDist = length(gWorldPos - u_light_pos);
    gl_FragDepth = lightDist / u_far_plane;  // write to depth
}
