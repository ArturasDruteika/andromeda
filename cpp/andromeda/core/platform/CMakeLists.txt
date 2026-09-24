cmake_minimum_required(VERSION 3.24)

project(platform)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPLATFORM_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)

# ==== platform ====
set(PLATFORM_PRIVATE_HEADERS
    include/private/macro_exports.hpp
)

set(PLATFORM_PUBLIC_HEADERS
    include/public/platform/platform.hpp
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

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private/
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public/
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
        api
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
