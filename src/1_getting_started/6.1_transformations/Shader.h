#pragma once

#include <stdint.h>
#include <string>

class Shader
{
public:
    uint32_t ShaderId;

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void Use();

    void SetInt(const std::string& parameterName, int32_t value);
};