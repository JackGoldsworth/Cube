#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO;

void create_temp_triangle();

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

    create_temp_triangle();
    Shader* shader = new Shader();
    shader->load_shaders();

    while (!glfwWindowShouldClose(window)) 
    {
        // Get user events.
        glfwPollEvents();

        glClearColor(1.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader->shaderId);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);
        glfwSwapBuffers(window);
    }

    return 0;
}

void create_temp_triangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // Bind Vertex Array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Bind Buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Write data to buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}