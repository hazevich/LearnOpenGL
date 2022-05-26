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

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Could not load GLAD" << std::endl;
        return 1;
    }

    glfwSetFramebufferSizeCallback(window, FramebufferResized);

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0.0f, 0.6f, 0.7f, 1.0f); // ocean blue
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

