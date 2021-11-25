#version 330 core

varying vec4 FragColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_FragColor = FragColor;
}