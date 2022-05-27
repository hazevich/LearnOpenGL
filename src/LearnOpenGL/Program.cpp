#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

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

struct VertexObjects
{
    unsigned int VBO, VAO;
};

VertexObjects CreateVertexObjects(const float vertices[], int size)
{
    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // position pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color pointer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    VertexObjects vdo = {};
    vdo.VAO = VAO;
    vdo.VBO = VBO;

    return vdo;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int width = 800, height = 600;

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

    Shader shader = Shader("Shaders/Vertex.glsl", "Shaders/Fragment.glsl");

    float vertices[] = {
         // positions           // colors
         0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
    };

    VertexObjects vertexObjects = CreateVertexObjects(vertices, sizeof(vertices));

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0.0f, 0.6f, 0.7f, 1.0f); // ocean blue
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        shader.SetFloat("xOffset", 0.5f);

        glBindVertexArray(vertexObjects.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader.Id);
    glDeleteBuffers(1, &vertexObjects.VBO);
    glDeleteVertexArrays(1, &vertexObjects.VAO);

    glfwTerminate();

    return 0;
}

