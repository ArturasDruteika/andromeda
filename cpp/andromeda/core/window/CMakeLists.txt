cmake_minimum_required(VERSION 3.24)

project(window)

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


# ==== Events ====
set(EVENTS_HEADERS
    window/events/include/event_base.hpp
    window/events/include/mouse_events.hpp
    window/events/include/key_events.hpp
    window/events/include/frame_buffer_events.hpp
    window/events/include/event_dispatcher.hpp
)

set(EVENTS_SOURCES
    window/events/src/event_base.cpp
    window/events/src/mouse_events.cpp
    window/events/src/frame_buffer_events.cpp
    window/events/src/key_events.cpp
    window/events/src/event_dispatcher.cpp
)

# ==== WindowGLFW ====
set(WINDOW_GLFW_HEADERS
    window/window_glfw/include/window_glfw.hpp
)

set(WINDOW_GLFW_SOURCES
    window/window_glfw/src/window_glfw.cpp
)

add_library(${PROJECT_NAME} 
    STATIC
        ${EVENTS_HEADERS}
        ${EVENTS_SOURCES}
        ${WINDOW_GLFW_HEADERS}
        ${WINDOW_GLFW_SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        precompiled_headers
        utils
        glfw
        OpenGL::GL
        spdlog::spdlog
    PUBLIC
        api
)

add_dependencies(${PROJECT_NAME} 
    utils
    glfw
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/events 
    PREFIX 
        "events" 
    FILES
        ${EVENTS_HEADERS}
        ${EVENTS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/window_glfw 
    PREFIX 
        "window_glfw" 
    FILES
        ${WINDOW_GLFW_HEADERS}
        ${WINDOW_GLFW_SOURCES}
)
