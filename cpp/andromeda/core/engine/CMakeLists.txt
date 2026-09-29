cmake_minimum_required(VERSION 3.24)

project(engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==== engine ====
set(ENGINE_HEADERS
    include/andromeda/engine/engine.hpp
)

set(ENGINE_SOURCES
    src/engine.cpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES}
)

add_library(andromeda::engine
    ALIAS ${PROJECT_NAME}
)

# ==== Export Header ====
include(GenerateExportHeader)

file(MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export"
)

generate_export_header(${PROJECT_NAME}
    BASE_NAME ENGINE
    EXPORT_MACRO_NAME ENGINE_API
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

# Link libraries (alphabetical)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        rendering
        spdlog::spdlog
    PUBLIC
        precompiled_headers
        andromeda::math
        andromeda::api::macro_exports_api
        andromeda::api::engine

)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    andromeda::math
    andromeda::rendering
    andromeda::utils
    andromeda::window
)


### Post builds
# SPDLog
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(MSVC)
        add_custom_command(
            TARGET 
                ${PROJECT_NAME} POST_BUILD 
            COMMAND 
                ${CMAKE_COMMAND} ARGS -E copy_if_different
                ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    else()
        add_custom_command(
            TARGET 
                ${PROJECT_NAME} POST_BUILD 
            COMMAND 
                ${CMAKE_COMMAND} ARGS -E copy_if_different
                ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif()

# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "engine"
    FILES
        ${ENGINE_HEADERS}
        ${ENGINE_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "macro_exports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)
