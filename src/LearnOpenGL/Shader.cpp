#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

uint32_t createShader(GLenum shaderType, const std::string& shaderSource)
{
    uint32_t shaderId = glCreateShader(shaderType);
    const char* shaderSourceCStr = shaderSource.c_str();
    glShaderSource(shaderId, 1, &shaderSourceCStr, NULL);
    glCompileShader(shaderId);

    int32_t success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "Error compiling shader:" << std::endl << infoLog << std::endl;
    }

    return shaderId;
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        std::stringstream vertexShaderStream, fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Error reading shader files" << std::endl << e.what() << std::endl;
    }

    uint32_t vertexShader = createShader(GL_VERTEX_SHADER, vertexCode);
    uint32_t fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentCode);

    uint32_t shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    int32_t success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        std::cout << "Shader linking failed" << std::endl << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ProgramId = shaderProgram;
}

Shader::~Shader()
{
    glDeleteProgram(ProgramId);
}

void Shader::Use()
{
    glUseProgram(ProgramId);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), (int32_t) value);
}

void Shader::SetInt(const std::string& name, int32_t value) const
{
    glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void Shader::SetMatrix(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
