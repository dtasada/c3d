#include "../include/engine.hpp"

#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <OpenGL/gl.h>

// Window dimensions
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *create_window(u32 width, u32 height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    framebuffer_size_callback(window, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

uint32_t create_vert_shader() {
    const char *vert_source = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;

        out vec3 pos;

		void main() {
            pos = vec3(aPos);
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vert_source, NULL);
    glCompileShader(vertex_shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return vertex_shader;
}

uint32_t create_frag_shader(uint32_t vert_shader) {
    const char *frag_source = R"(
		#version 330 core
        in vec3 pos;
		out vec4 FragColor;

		void main() {
			FragColor = vec4(pos.x, pos.y, pos.z, 1.0f);
		}
	)";

    uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_source, NULL);
    glCompileShader(frag_shader);

    int  success;
    char infoLog[512];

    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return frag_shader;
}

uint32_t create_shader_program() {
    uint32_t vertex_shader   = create_vert_shader();
    uint32_t fragment_shader = create_frag_shader(vertex_shader);

    uint32_t shader_program = glCreateProgram();

    int  success;
    char infoLog[512];
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "Failed to attach shaders to program!" << infoLog << std::endl;
    }

    glUseProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}
