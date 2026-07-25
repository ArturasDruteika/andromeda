#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat3 u_normal_matrix;
uniform mat4 u_light_space_matrix;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec4 v_FragPosLightSpace;

void main()
{
    vec4 worldPos = u_model * vec4(aPos, 1.0);
    v_FragPos = worldPos.xyz;
    v_Normal = normalize(u_normal_matrix * aNormal);
    v_FragPosLightSpace = u_light_space_matrix * worldPos;
    gl_Position = u_projection * u_view * worldPos;
}
