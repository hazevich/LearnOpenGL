#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <print>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexShaderPath);
        std::stringstream vertexShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        vertexShaderFile.close();
        vertexShaderCode = vertexShaderStream.str();

        fragmentShaderFile.open(fragmentShaderPath);
        std::stringstream fragmentShaderStream;
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        fragmentShaderFile.close();
        fragmentShaderCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::println("Error reading shader file");
        throw;
    }

    uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCStr = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexShaderCStr, NULL);
    glCompileShader(vertexShaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, sizeof(infoLog), NULL, infoLog);
        std::println("Vertex shader compilation failed:");
        std::println("{}", infoLog);
    }

    uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCStr = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentShaderCStr, NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::println("Fragment shader compilation failed:");
        std::println("{}", infoLog);
    }

    ShaderId = glCreateProgram();
    glAttachShader(ShaderId, vertexShaderId);
    glAttachShader(ShaderId, fragmentShaderId);
    glLinkProgram(ShaderId);

    glGetProgramiv(ShaderId, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(ShaderId, sizeof(infoLog), NULL, infoLog);
        std::println("Shader program linking failed:");
        std::println("{}", infoLog);
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

Shader::~Shader()
{
    glDeleteProgram(ShaderId);
}

void Shader::Use()
{
    glUseProgram(ShaderId);
}

void Shader::SetFloat(const std::string& parameterName, float value)
{
    int32_t parameterLocation = glGetUniformLocation(ShaderId, parameterName.c_str());
    glUniform1f(parameterLocation, value);
}