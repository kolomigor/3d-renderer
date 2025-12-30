#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Init GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW init failed" << std::endl;
        return 1;
    }

    // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MacOS restriction for core profile
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    GLFWwindow *window =
        glfwCreateWindow(800, 600, "3D Renderer", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return 1;
    }

    // Create context
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Load GLAD
    auto loader = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
    if (!gladLoadGLLoader(loader)) {
        std::cerr << "Failed to load GLAD" << std::endl;
        return 1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glViewport(0, 0, 800, 600);

    // Main cycle
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    // Close GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}