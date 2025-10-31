#version 460 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D containerTexture;
uniform sampler2D awesomefaceTexture;
uniform vec2 texCoordOffset;

void main()
{
    FragColor = mix(
        texture(containerTexture, vec2(TexCoord.x + texCoordOffset.x, TexCoord.y + texCoordOffset.y)), 
        texture(awesomefaceTexture, vec2(TexCoord.x + texCoordOffset.x, TexCoord.y + texCoordOffset.y)), 
        0.2f);
}
