cmake_minimum_required(VERSION 3.31)

set(PROJECT_NAME c3d)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optimize GNU compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GNU CXX detected, adding compile flags")
	add_compile_options(-Wall -Wextra -Wsign-compare -O3)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch dependencies
include(FetchContent)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

set(GLAD_DIR "${CMAKE_SOURCE_DIR}/lib/glad")

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLAD_DIR}/include)

# Add executables
add_executable(${PROJECT_NAME} src/main.cpp ${GLAD_DIR}/src/glad.c)


target_link_libraries(${PROJECT_NAME}
	OpenGL::GL
	glfw
	glm::glm
)
