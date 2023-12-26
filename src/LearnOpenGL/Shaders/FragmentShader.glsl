#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec4 vertexPosition;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
	FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(texCoord.x * -1, texCoord.y)), mixValue);
}
