cmake_minimum_required(VERSION 3.24)

project(utils)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ==== FileOperations ====
set(FILE_OPERATIONS_HEADERS
    utils/file_operations/include/file_operations.hpp
)

set(FILE_OPERATIONS_SOURCES
    utils/file_operations/src/file_operations.cpp
)

# ==== nlohmann ====
set(NLOHMANN_HEADERS
    utils/nlohmann_json/include/json.hpp
)

# ==== stb ====
set(STB_HEADERS
    utils/stb/include/stb_easy_font.h
)


# Create a library target
add_library(${PROJECT_NAME} 
    STATIC
        ${FILE_OPERATIONS_HEADERS}
        ${FILE_OPERATIONS_SOURCES}
        ${NLOHMANN_HEADERS}
        ${STB_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Link spdlog
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        precompiled_headers
        spdlog::spdlog
)


source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/file_operations
    PREFIX
        "file_operations"
    FILES
        ${FILE_OPERATIONS_HEADERS}
        ${FILE_OPERATIONS_SOURCES}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/nlohmann_json
    PREFIX
        "nlohmann_json"
    FILES
        ${NLOHMANN_HEADERS}
)

source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/stb
    PREFIX
        "stb"
    FILES
        ${STB_HEADERS}
)