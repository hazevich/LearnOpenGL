#pragma once
class Shader
{
public:
    unsigned int Id;

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    void Use();

    void SetBool(const char* name, bool value);
    void SetFloat(const char* name, float value);
    void SetInt(const char* name, int value);
};

