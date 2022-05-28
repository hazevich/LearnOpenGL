#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 textureCoordinate;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, textureCoordinate), texture(texture2, vec2(1.0 - textureCoordinate.x, textureCoordinate.y)), 0.2);
}
