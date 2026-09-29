cmake_minimum_required(VERSION 3.24)

project(window)

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
    include/andromeda/window/events/event_base.hpp
    include/andromeda/window/events/mouse_events.hpp
    include/andromeda/window/events/key_events.hpp
    include/andromeda/window/events/frame_buffer_events.hpp
    include/andromeda/window/events/event_dispatcher.hpp
)

set(EVENTS_SOURCES
    src/events/event_base.cpp
    src/events/mouse_events.cpp
    src/events/frame_buffer_events.cpp
    src/events/key_events.cpp
    src/events/event_dispatcher.cpp
)

# ==== WindowGLFW ====
set(WINDOW_GLFW_HEADERS
    include/andromeda/window/window_glfw/window_glfw.hpp
)

set(WINDOW_GLFW_SOURCES
    src/window_glfw/window_glfw.cpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
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
        andromeda::api::window
)

add_dependencies(${PROJECT_NAME} 
    utils
    glfw
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX 
        "events" 
    FILES
        ${EVENTS_HEADERS}
        ${EVENTS_SOURCES}
)
