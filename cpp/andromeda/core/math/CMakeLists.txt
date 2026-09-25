cmake_minimum_required(VERSION 3.24)

project(math)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DMATH_EXPORT)


# ==== Files ====
set(MATH_HEADERS_PRIVATE
    include/private/macro_exports/macro_exports.hpp
)

set(MATH_HEADERS_PUBLIC
    include/public/math/constants/constants.hpp
    include/public/math/linear_algebra/linear_algebra_data_types.hpp
    include/public/math/linear_algebra/linear_algebra_operations.hpp
    include/public/math/linear_algebra/quaternions.hpp
    include/public/math/trigonometry/trigonometry.hpp
)

set(MATH_SOURCES
    src/linear_algebra/linear_algebra_operations.cpp
    src/linear_algebra/quaternions.cpp
    src/trigonometry/trigonometry.cpp
)


# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${MATH_HEADERS_PRIVATE}
        ${MATH_HEADERS_PUBLIC}
        ${MATH_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private/
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public/
)

# ==== Link Libraries ====
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        precompiled_headers
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

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "linear_algebra"
    FILES
        ${LINEAR_ALGEBRA_HEADERS}
        ${LINEAR_ALGEBRA_SOURCES}
)
