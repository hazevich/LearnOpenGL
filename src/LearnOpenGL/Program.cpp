#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void FramebufferResized(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

const char* VertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* FragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

bool CheckShaderCompileStatus(int shaderId, char* shaderName)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << shaderName << " compilation failed" << std::endl << infoLog << std::endl;

        return false;
    }

    std::cout << shaderName << " has been compiled successfully" << std::endl;

    return true;
}

unsigned int CompileShader(const char* shaderSource, GLenum shaderType, char* shaderName, unsigned int& shaderId)
{
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);

    return CheckShaderCompileStatus(shaderId, shaderName);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int width = 1280, height = 720;

    GLFWwindow* window = glfwCreateWindow(width, height, "Hello world", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Could not create a window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Could not load GLAD" << std::endl;
        return 1;
    }

    glfwSetFramebufferSizeCallback(window, FramebufferResized);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int vertexShader;

    if (!CompileShader(VertexShaderSource, GL_VERTEX_SHADER, "vertex shader", vertexShader))
    {
        glfwTerminate();
        return 1;
    }

    unsigned int fragmentShader;
    if (!CompileShader(FragmentShaderSource, GL_FRAGMENT_SHADER, "fragment shader", fragmentShader))
    {
        glfwTerminate();
        return 1;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    {
        int success;
        char infoLog[512];

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "Failed linking shaders: " << infoLog << std::endl;

            glfwTerminate();
            return 1;
        }
        else
        {
            std::cout << "Shaders have been linked successfully" << std::endl;
        }
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0.0f, 0.6f, 0.7f, 1.0f); // ocean blue
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}

