cmake_minimum_required(VERSION 3.24)

project(math)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DMATH_EXPORT)


# ==== Files ====
set(MATH_HEADERS
    include/math/constants/constants.hpp
    include/math/linear_algebra/linear_algebra_data_types.hpp
    include/math/linear_algebra/linear_algebra_operations.hpp
    include/math/linear_algebra/quaternions.hpp
    include/math/macro_exports/macro_exports.hpp
    include/math/trigonometry/trigonometry.hpp
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

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
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
        ${CMAKE_CURRENT_SOURCE_DIR}/include/math/
    PREFIX
        "math"
    FILES
        ${MATH_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PREFIX
        "linear_algebra"
    FILES
        ${LINEAR_ALGEBRA_HEADERS}
        ${LINEAR_ALGEBRA_SOURCES}
)
