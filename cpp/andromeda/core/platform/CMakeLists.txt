cmake_minimum_required(VERSION 3.24)

project(platform)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPLATFORM_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)

# SPDLog

# ==== macro_exports ====
set(MACRO_EXPORTS_HEADERS
    macro_exports/include/macro_exports.hpp
)

# ==== platform ====
set(PLATFORM_HEADERS
    platform/include/platform.hpp
)

set(PLATFORM_SOURCES
    platform/src/platform.cpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${MACRO_EXPORTS_HEADERS}
        ${PLATFORM_HEADERS}
        ${PLATFORM_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE 
        ANDROMEDA_API_BUILD
)

if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

# Link libraries (alphabetical)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        precompiled_headers
        glfw
        OpenGL::GL
        graphics_context
        Glad
        window
        api
        imgui
        spdlog::spdlog
)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    graphics_context
    Glad
    utils
    window
    glfw
    imgui
)

### Post builds
# SPDLog
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_custom_command(
        TARGET 
            ${PROJECT_NAME} POST_BUILD 
        COMMAND 
            ${CMAKE_COMMAND} ARGS -E copy_if_different
            ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif()

# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/macro_exports
    PREFIX
        "macro_exports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/platform
    PREFIX
        "platform"
    FILES
        ${PLATFORM_HEADERS}
        ${PLATFORM_SOURCES}
)
