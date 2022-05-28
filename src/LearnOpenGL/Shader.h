#pragma once

#include "glm/glm.hpp"

class Shader
{
public:
    unsigned int Id;

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    void Use();

    void SetBool(const char* name, bool value);
    void SetFloat(const char* name, float value);
    void SetInt(const char* name, int value);
    void SetMatrix(const char* name, glm::mat4 matrix);
};

