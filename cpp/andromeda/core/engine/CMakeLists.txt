cmake_minimum_required(VERSION 3.24)

project(engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DENGINECORE_EXPORT)

# SPDLog


# ==== engine ====
set(ENGINE_HEADERS
    include/engine/engine.hpp
    include/engine/macro_exports.hpp
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

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
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
        math
        api

)

# Explicit build ordering (alphabetical)
add_dependencies(${PROJECT_NAME}
    math
    rendering
    utils
    window
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
