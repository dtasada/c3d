cmake_minimum_required(VERSION 3.31)

project(c3d)
set(CMAKE_CXX_STANDARD 23)

# Optimize GNU compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GNU CXX detected, adding compile flags")
	add_compile_options(-Wall -Wextra -Wsign-compare -O3)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Gather source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Add executables
add_executable(src ${SRC_FILES})

# Fetch dependencies
include(FetchContent)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(src
	OpenGL::GL
	glfw
	glm::glm
)
