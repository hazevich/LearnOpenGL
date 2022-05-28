#include "Shader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

unsigned int CreateShader(const std::string& shaderSource, GLenum shaderType, const char* shaderName)
{
    unsigned int shaderId = glCreateShader(shaderType);
    const char* shaderSourceCStr = shaderSource.c_str();
    glShaderSource(shaderId, 1, &shaderSourceCStr, NULL);
    glCompileShader(shaderId);

    int success;
    char infoLog[512];

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (success)
    {
        std::cout << shaderName << " shader has been successfully compiled" << std::endl;
    }
    else
    {
        glGetShaderInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "An error occurred while compiling " << shaderName << " :" << infoLog << std::endl;
    }

    return shaderId;
}

unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (success)
    {
        std::cout << "Successfully linked shaders" << std::endl;
    }
    else
    {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);

        std::cout << "An error occurred while linking shaders: " << infoLog << std::endl;
    }

    return shaderProgram;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    : Id(0)
{
    std::string vertexSource;
    std::string fragmentSource;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    vertexShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    try
    {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);

        std::stringstream vertexStringStream, fragmentStringStream;

        vertexStringStream << vertexShaderFile.rdbuf();
        vertexSource = vertexStringStream.str();

        fragmentStringStream << fragmentShaderFile.rdbuf();
        fragmentSource = fragmentStringStream.str();

        vertexShaderFile.close();
        fragmentShaderFile.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "an error occurred reading shader files: " << std::endl;
    }

    unsigned int vertexShader = CreateShader(vertexSource, GL_VERTEX_SHADER, "vertex");
    unsigned int fragmentShader = CreateShader(fragmentSource, GL_FRAGMENT_SHADER, "fragment");

    Id = CreateShaderProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use()
{
    glUseProgram(Id);
}

void Shader::SetFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(Id, name), value);
}

void Shader::SetInt(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::SetBool(const char* name, bool value)
{
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::SetMatrix(const char* name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(Id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
