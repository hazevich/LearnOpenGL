#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 textureCoordinate;

uniform sampler2D texture;

void main()
{
    FragColor = texture(texture, textureCoordinate) * vertexColor;
}
