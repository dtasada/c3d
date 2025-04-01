cmake_minimum_required(VERSION 3.31)
project(c3d)
set(CMAKE_CXX_STANDARD 23)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Architecture handling for macOS
if(APPLE)
    # Check if architecture is explicitly specified via command line
    if(NOT DEFINED CMAKE_OSX_ARCHITECTURES OR CMAKE_OSX_ARCHITECTURES STREQUAL "")
        # Detect host architecture and set it as the target
        execute_process(
            COMMAND uname -m
            OUTPUT_VARIABLE HOST_ARCH
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        
        message(STATUS "Detected host architecture: ${HOST_ARCH}")
        
        # Set architecture based on host
        set(CMAKE_OSX_ARCHITECTURES "${HOST_ARCH}" CACHE STRING "Build architecture for macOS" FORCE)
    endif()
    
    # Option for universal binary
    option(BUILD_UNIVERSAL "Build universal binary for both arm64 and x86_64" OFF)
    if(BUILD_UNIVERSAL)
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "Build architectures for macOS" FORCE)
    endif()
    
    message(STATUS "Target architecture(s): ${CMAKE_OSX_ARCHITECTURES}")
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
