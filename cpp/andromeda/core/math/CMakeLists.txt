cmake_minimum_required(VERSION 3.24)

project(math)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DMATH_EXPORT)


# ==== constants ====
set(CONSTANTS_HEADERS
    math/constants/include/constants.hpp
)

# ==== Linear Algebra ====
set(LINEAR_ALGEBRA_HEADERS
    math/linear_algebra/include/linear_algebra_data_types.hpp
    math/linear_algebra/include/linear_algebra_operations.hpp
    math/linear_algebra/include/quaternions.hpp
)

set(LINEAR_ALGEBRA_SOURCES
    math/linear_algebra/src/linear_algebra_operations.cpp
    math/linear_algebra/src/quaternions.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    math/macro_exports/include/macro_exports.hpp
)

# ==== Trigonometry ====
set(TRIGONOMETRY_HEADERS
    math/trigonometry/include/trigonometry.hpp
)

set(TRIGONOMETRY_SOURCES
    math/trigonometry/src/trigonometry.cpp
)


# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${CONSTANTS_HEADERS}
        ${LINEAR_ALGEBRA_HEADERS}
        ${LINEAR_ALGEBRA_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${TRIGONOMETRY_HEADERS}
        ${TRIGONOMETRY_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/constants
    PREFIX
        "constants"
    FILES
        ${CONSTANTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/linear_algebra
    PREFIX
        "linear_algebra"
    FILES
        ${LINEAR_ALGEBRA_HEADERS}
        ${LINEAR_ALGEBRA_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/macro_exports
    PREFIX
        "macro_exports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/trigonometry
    PREFIX
        "trigonometry"
    FILES
        ${TRIGONOMETRY_HEADERS}
        ${TRIGONOMETRY_SOURCES}
)
