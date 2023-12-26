// LearnOpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include "Texture2D.h"

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

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    Shader shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

    float vertices[] = {
        // positions        // colors          // texture coordinates
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.60f, 0.60f,
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.60f, 0.40f,
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.40f, 0.40f,
       -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.40f, 0.60f,
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    Texture2D containerTexture("Assets/container.jpg", ColorValue::RGB, WrappingMethod::ClampToEdge);
    Texture2D awesomefaceTexture("Assets/awesomeface.png", ColorValue::RGBA, WrappingMethod::Repeat);

    uint32_t VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTexture.TextureId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomefaceTexture.TextureId);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
