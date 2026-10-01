cmake_minimum_required(VERSION 3.24)

project(utils)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ==== FileOperations ====
set(FILE_OPERATIONS_HEADERS
    include/andromeda/utils/file_operations/file_operations.hpp
)

set(FILE_OPERATIONS_SOURCES
    src/file_operations/file_operations.cpp
)

# ==== nlohmann ====
set(NLOHMANN_HEADERS
    include/andromeda/utils/nlohmann_json/json.hpp
)

# ==== stb ====
set(STB_HEADERS
    include/andromeda/utils/stb/stb_easy_font.h
)


# Create a library target
add_library(${PROJECT_NAME} 
    STATIC
        ${FILE_OPERATIONS_HEADERS}
        ${FILE_OPERATIONS_SOURCES}
        ${NLOHMANN_HEADERS}
        ${STB_HEADERS}
)

add_library(andromeda::utils
    ALIAS ${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Link spdlog
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        andromeda::precompiled_headers
        spdlog::spdlog
)


source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "file_operations"
    FILES
        ${FILE_OPERATIONS_HEADERS}
        ${FILE_OPERATIONS_SOURCES}
)