#pragma once

#include <stdint.h>

class Shader
{
public:
    uint32_t ShaderId;

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void Use();
};