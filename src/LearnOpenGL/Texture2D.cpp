#include "Texture2D.h"
#include "stb_image.h"
#include "glad/glad.h"

Texture2D::Texture2D(const std::string& path, ColorValue colorValue)
{
    int32_t width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum sourceColorValue;

    switch (colorValue)
    {
    case ColorValue::RGB:
        sourceColorValue = GL_RGB;
        break;
    case ColorValue::RGBA:
    default:
        sourceColorValue = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, sourceColorValue, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    TextureId = texture;
    Width = width;
    Height = height;
}
