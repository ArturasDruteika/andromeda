cmake_minimum_required(VERSION 3.24)

project(math)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==== Files ====
set(MATH_HEADERS
    include/andromeda/math/constants/constants.hpp
    include/andromeda/math/linear_algebra/linear_algebra_data_types.hpp
    include/andromeda/math/linear_algebra/linear_algebra_operations.hpp
    include/andromeda/math/linear_algebra/quaternions.hpp
    include/andromeda/math/trigonometry/trigonometry.hpp
)

set(MATH_SOURCES
    src/linear_algebra/linear_algebra_operations.cpp
    src/linear_algebra/quaternions.cpp
    src/trigonometry/trigonometry.cpp
)


# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${MATH_HEADERS}
        ${MATH_SOURCES}
)

add_library(andromeda::math
    ALIAS ${PROJECT_NAME}
)

# ==== Export Header ====
include(GenerateExportHeader)

file(MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export"
)

generate_export_header(${PROJECT_NAME}
    BASE_NAME MATH
    EXPORT_MACRO_NAME MATH_API
    EXPORT_FILE_NAME
        "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export/macro_export.hpp"
)

# ==== Include Directories ====
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CMAKE_CURRENT_BINARY_DIR}/include/
)

# ==== Link Libraries ====
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        andromeda::precompiled_headers
        spdlog::spdlog
        glm::glm
)


# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "math"
    FILES
        ${MATH_HEADERS}
)
