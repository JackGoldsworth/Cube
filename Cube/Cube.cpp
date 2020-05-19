#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 800;

int main()
{
    if (!glfwInit()) 
    {
        printf("GLFW Init failed.");
        glfwTerminate();
        return 1;
    }

    // OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Disable backwards compatibility.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Enable forwards compatibility.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Cube", NULL, NULL);

    if (!window)
    {
        printf("GLFW window creation failed.");
        glfwTerminate();
        return 1;
    }

    // Get buffer information.
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    // Set window to draw to.
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW init failed.");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // Set viewport size.
    glViewport(0, 0, bufferWidth, bufferHeight);

    while (!glfwWindowShouldClose(window)) 
    {
        // Get user events.
        glfwPollEvents();

        glClearColor(1.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    return 0;
}