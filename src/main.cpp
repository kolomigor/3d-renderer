#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "mesh_data.h"

struct Triangle {
    Vector3D vertices[3];
};

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed" << std::endl;
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window =
        glfwCreateWindow(800, 600, "3D Renderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    auto loader = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
    if (!gladLoadGLLoader(loader)) {
        std::cerr << "Failed to load GLAD" << std::endl;
        return 1;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    std::cout << "Input triangle coordinates in range [-1, 1]" << std::endl;
    Triangle triangle;
    for (int i = 0; i < 3; i++) {
        std::cin >> triangle.vertices[i].x;
        std::cin >> triangle.vertices[i].y;
        std::cin >> triangle.vertices[i].z;
    }
    glViewport(0, 0, 800, 600);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.vertices), triangle.vertices,
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, // location = 0
                          3, // vec3
                          GL_FLOAT, GL_FALSE, sizeof(Vector3D), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

    const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.4, 0.2, 1.0);
}
)";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}