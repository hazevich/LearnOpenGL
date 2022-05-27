#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;
out vec4 vertexPosition;
uniform float xOffset;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexPosition = gl_Position;
    vertexColor = vec4(aColor, 1.0);
}
