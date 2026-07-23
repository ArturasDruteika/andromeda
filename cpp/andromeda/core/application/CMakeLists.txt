cmake_minimum_required(VERSION 3.24)

project(application)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DAPPLICATION_EXPORT)


# SPDLog


# ==== applicationGLFW ====
set(APPLICATION_HEADERS
    application/include/application.hpp
)

set(APPLICATION_SOURCES
    application/src/application.cpp
)

add_library(${PROJECT_NAME} 
    SHARED
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        ANDROMEDA_API_BUILD
)

# Link GLFW and OpenGL to the executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        precompiled_headers
        spdlog::spdlog
    PUBLIC
        engine
        platform
        Api
)


# Organize files into Solution Explorer folders
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}
    PREFIX 
        "application" 
    FILES
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)
