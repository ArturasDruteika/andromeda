cmake_minimum_required(VERSION 3.24)

project(graphics_context)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

# ==== graphics_context ====
set(GRAPHICS_CONTEXT_HEADERS
    graphics_context/include/graphics_contextGLFW.hpp
)

set(GRAPHICS_CONTEXT_SOURCES
    graphics_context/src/graphics_contextGLFW.cpp
)

add_library(${PROJECT_NAME} 
    STATIC
        ${GRAPHICS_CONTEXT_HEADERS}
        ${GRAPHICS_CONTEXT_SOURCES}
)

# SPDLog

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ..//glfw//include//
        ..//glfw//
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        precompiled_headers
        Api
        Window
        Glad
        glfw
        OpenGL::GL
        spdlog::spdlog
)

add_dependencies(${PROJECT_NAME} 
	glfw
    Glad
    Window
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics_context
    PREFIX
        "graphics_context"
    FILES
        ${GRAPHICS_CONTEXT_HEADERS}
        ${GRAPHICS_CONTEXT_SOURCES}
)