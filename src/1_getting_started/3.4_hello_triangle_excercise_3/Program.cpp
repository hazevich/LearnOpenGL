#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float _vertices[] = {
    -1.0f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,

     0.0f, -0.5f, 0.0f,
     1.0f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
};

const char* _vertexShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* _fragmentShader = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0f, 0.34f, 0.72f, 1.0f);
}

)";

const char* _fragmentShader2 = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.84, 0.0f, 1.0f);
}

)";


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    uint32_t vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &_vertexShader, NULL);
    glCompileShader(vertexShaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    uint32_t fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &_fragmentShader, NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    uint32_t shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgramId, sizeof(infoLog), NULL, infoLog);
        std::cout << "Shader linking failed\n" << infoLog << std::endl;
    }

    uint32_t fragmentShaderId2;
    fragmentShaderId2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId2, 1, &_fragmentShader2, NULL);
    glCompileShader(fragmentShaderId2);

    glGetShaderiv(fragmentShaderId2, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId2, sizeof(infoLog), NULL, infoLog);
        std::cout << "Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    uint32_t shaderProgramId2 = glCreateProgram();
    glAttachShader(shaderProgramId2, vertexShaderId);
    glAttachShader(shaderProgramId2, fragmentShaderId2);
    glLinkProgram(shaderProgramId2);

    glGetProgramiv(shaderProgramId2, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgramId2, sizeof(infoLog), NULL, infoLog);
        std::cout << "Shader linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteShader(fragmentShaderId2);

    uint32_t verticesCount = 9;

    uint32_t VBO1;
    glGenBuffers(1, &VBO1);

    uint32_t VAO1;
    glGenVertexArrays(1, &VAO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), _vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    uint32_t VBO2;
    glGenBuffers(1, &VBO2);

    uint32_t VAO2;
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), _vertices + verticesCount, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(139.f / 255.f, 139.f / 255.f, 141.f / 255.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);

        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramId2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);

    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);

    glDeleteProgram(shaderProgramId);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
