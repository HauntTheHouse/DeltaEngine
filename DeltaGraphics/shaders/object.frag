#version 330 core

in vec3 fColor;
in vec2 fTexPosition;

out vec4 FragColor;

uniform sampler2D uDefaultTexture;
uniform sampler2D uPink;

void main()
{
    FragColor = mix(texture(uDefaultTexture, fTexPosition), texture(uPink, fTexPosition), 0.2f);
}
