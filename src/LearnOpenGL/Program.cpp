#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "stb_image.h"

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
    unsigned int VBO, VAO, EBO;
};

VertexObjects CreateVertexObjects(const float vertices[], int verticesSize, const unsigned int indices[], int indicesSize)
{
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    VertexObjects vdo = {};
    vdo.VAO = VAO;
    vdo.VBO = VBO;
    vdo.EBO = EBO;

    return vdo;
}

unsigned int CreateTexture(const char* texturePath, GLenum format, GLint wrapType)
{
    stbi_set_flip_vertically_on_load(true);
    int textureWidth, textureHeight, nrChannels;
    unsigned char* data = stbi_load(texturePath, &textureWidth, &textureHeight, &nrChannels, 0);

    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return 0;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
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
        // positions            // colors            // texture coordinates 
         0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 
         0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    VertexObjects vertexObjects = CreateVertexObjects(vertices, sizeof(vertices), indices, sizeof(indices));

    unsigned int containerTexture = CreateTexture("Textures/container.jpg", GL_RGB, GL_REPEAT);
    unsigned int awesomeFaceTexture = CreateTexture("Textures/awesomeface.png", GL_RGBA, GL_REPEAT);

    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0.0f, 0.6f, 0.7f, 1.0f); // ocean blue
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        float time = glfwGetTime();
        float mixValue = (sin(time) + 1) * 0.5f;
        shader.SetFloat("mixValue", mixValue);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeFaceTexture);

        glBindVertexArray(vertexObjects.VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

