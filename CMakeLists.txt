cmake_minimum_required(VERSION 3.31)
project(c3d)
set(CMAKE_CXX_STANDARD 23)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# For Apple Silicon, explicitly set architecture to arm64
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for macOS" FORCE)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files
set(SOURCES src/main.cpp)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

if(APPLE)
    find_package(OpenGL REQUIRED)
    # Add Apple-specific compiler flags
    add_compile_definitions("GL_SILENCE_DEPRECATION")
elseif(WIN32)
    find_package(OpenGL REQUIRED)
    set(GLAD_DIR "${CMAKE_SOURCE_DIR}/external/glad")
    set(GLAD_SOURCES ${GLAD_DIR}/src/glad.c)
    include_directories(${GLAD_DIR}/include)
    list(APPEND SOURCES ${GLAD_SOURCES})
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glm::glm
    OpenGL::GL
)

# Print architecture info for debugging
message(STATUS "Target architectures: ${CMAKE_OSX_ARCHITECTURES}")
