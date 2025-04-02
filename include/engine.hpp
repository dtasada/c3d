#include <cstdint>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <OpenGL/gl.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float  f32;
typedef double f64;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLFWwindow *create_window(u32 width, u32 height);

uint32_t create_vert_shader();
uint32_t create_frag_shader(u32 vert_shader);
uint32_t create_shader_program();
