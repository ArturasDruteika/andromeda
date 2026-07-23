cmake_minimum_required(VERSION 3.24)

project(Math)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DMATH_EXPORT)

# SPDLog


# ==== Constants ====
set(CONSTANTS_HEADERS
    Math/Constants/include/constants.hpp
)

# ==== Linear Algebra ====
set(LINEAR_ALGEBRA_HEADERS
    Math/LinearAlgebra/include/linear_algebra_data_types.hpp
    Math/LinearAlgebra/include/linear_algebra_operations.hpp
    Math/LinearAlgebra/include/quaternions.hpp
)

set(LINEAR_ALGEBRA_SOURCES
    Math/LinearAlgebra/src/linear_algebra_operations.cpp
    Math/LinearAlgebra/src/quaternions.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    Math/MacroExports/include/macro_exports.hpp
)

# ==== Trigonometry ====
set(TRIGONOMETRY_HEADERS
    Math/Trigonometry/include/trigonometry.hpp
)

set(TRIGONOMETRY_SOURCES
    Math/Trigonometry/src/trigonometry.cpp
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
        PrecompiledHeaders
        spdlog::spdlog
        glm::glm
)


# ==== IDE Organization ====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Constants
    PREFIX
        "Constants"
    FILES
        ${CONSTANTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/LinearAlgebra
    PREFIX
        "LinearAlgebra"
    FILES
        ${LINEAR_ALGEBRA_HEADERS}
        ${LINEAR_ALGEBRA_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/MacroExports
    PREFIX
        "MacroExports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Trigonometry
    PREFIX
        "Trigonometry"
    FILES
        ${TRIGONOMETRY_HEADERS}
        ${TRIGONOMETRY_SOURCES}
)
