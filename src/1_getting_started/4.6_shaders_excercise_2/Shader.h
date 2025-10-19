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

    void SetFloat(const std::string& parameterName, float value);
};