#pragma once
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    uint32_t ProgramId;

    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    void Use();

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int32_t value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMatrix(const std::string& name, glm::mat4 value) const;
};
