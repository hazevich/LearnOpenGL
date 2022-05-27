#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;
out vec4 vertexPosition;
uniform float xOffset;

void main()
{
    vec3 upsideDown = aPos * -1;
    vec3 offsetPos = vec3(upsideDown.x + xOffset, upsideDown.yz);
    gl_Position = vec4(offsetPos, 1.0);
    vertexPosition = gl_Position;
    vertexColor = vec4(aColor, 1.0);
}
