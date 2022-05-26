#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void FramebufferResized(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

