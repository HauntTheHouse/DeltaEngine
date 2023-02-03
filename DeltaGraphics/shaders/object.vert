#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexPosition;

uniform mat4 uModel;
uniform mat4 uViewProject;

out vec3 fColor;
out vec2 fTexPosition;

void main()
{
    fColor = vColor;
    fTexPosition = vTexPosition;
    gl_Position = uViewProject * uModel * vec4(vPosition, 1.0f);
}
