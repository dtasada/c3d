#include "../include/engine.hpp"

#include <array>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <OpenGL/gl.h>

// Window dimensions
const u32 WINDOW_WIDTH  = 800;
const u32 WINDOW_HEIGHT = 600;

int main(int argc, char *argv[]) {
    GLFWwindow *window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!window) return EXIT_FAILURE;

    std::array<float, 12> vertices = {
        0.5f,
        0.5f,
        0.0f,  // top right
        0.5f,
        -0.5f,
        0.0f,  // bottom right
        -0.5f,
        -0.5f,
        0.0f,  // bottom left
        -0.5f,
        0.5f,
        0.0f   // top left
    };

    std::array<uint32_t, 6> indices = {
        0,
        1,
        3,  // first triangle
        1,
        2,
        3   // second triangle
    };

	uint32_t vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    uint32_t shaderProgram = create_shader_program();

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return EXIT_SUCCESS;
}
