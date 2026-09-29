cmake_minimum_required(VERSION 3.24)

project(platform)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)

# ==== platform ====
set(PLATFORM_PUBLIC_HEADERS
    include/andromeda/platform/platform.hpp
)

set(PLATFORM_SOURCES
    src/platform.cpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${PLATFORM_PRIVATE_HEADERS}
        ${PLATFORM_PUBLIC_HEADERS}
        ${PLATFORM_SOURCES}
)

# ==== Export Header ====
include(GenerateExportHeader)

file(MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export"
)

generate_export_header(${PROJECT_NAME}
    BASE_NAME PLATFORM
    EXPORT_MACRO_NAME PLATFORM_API
    EXPORT_FILE_NAME
        "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export/macro_export.hpp"
)

# ==== Include Directories ====
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CMAKE_CURRENT_BINARY_DIR}/include/
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
        glad
        window
        andromeda::api::macro_exports_api
        andromeda::api::platform
        imgui
        spdlog::spdlog
)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    graphics_context
    glad
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
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "platform"
    FILES
        ${PLATFORM_HEADERS}
        ${PLATFORM_SOURCES}
)
