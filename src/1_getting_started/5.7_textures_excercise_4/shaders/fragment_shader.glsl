#version 460 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D containerTexture;
uniform sampler2D awesomefaceTexture;
uniform float mixValue;

void main()
{
    FragColor = mix(texture(containerTexture, TexCoord), texture(awesomefaceTexture, TexCoord), mixValue);
}
