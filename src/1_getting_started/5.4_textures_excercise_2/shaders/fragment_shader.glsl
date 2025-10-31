#version 460 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D containerTexture;
uniform sampler2D awesomefaceTexture;

void main()
{
    FragColor = mix(texture(containerTexture, TexCoord), texture(awesomefaceTexture, vec2(TexCoord.x, TexCoord.y)), 0.2f);
}
