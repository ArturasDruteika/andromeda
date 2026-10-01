cmake_minimum_required(VERSION 3.24)

project(application)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APPLICATION_HEADERS
    include/andromeda/application/application.hpp
)

set(APPLICATION_SOURCES
    src/application.cpp
)

add_library(${PROJECT_NAME} 
    SHARED
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)

add_library(andromeda::application
    ALIAS ${PROJECT_NAME}
)

# ==== Export Header ====
include(GenerateExportHeader)

file(MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export"
)

generate_export_header(${PROJECT_NAME}
    BASE_NAME APPLICATION
    EXPORT_MACRO_NAME APPLICATION_API
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

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        andromeda::precompiled_headers
        spdlog::spdlog
    PUBLIC
        andromeda::engine
        andromeda::platform
        andromeda::api::platform
        andromeda::api::application
)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    andromeda::engine
    andromeda::platform
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX 
        "application" 
    FILES
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)
