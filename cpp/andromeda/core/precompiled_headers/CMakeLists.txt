cmake_minimum_required(VERSION 3.24)

project(precompiled_headers LANGUAGES CXX)

# ==== Target ====

add_library(precompiled_headers INTERFACE)

add_library(andromeda::precompiled_headers
    ALIAS precompiled_headers
)

target_compile_features(precompiled_headers
    INTERFACE
        cxx_std_23
)

# ==== Include Directories ====

target_include_directories(precompiled_headers
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ==== Precompiled Headers ====

target_precompile_headers(precompiled_headers
    INTERFACE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp>"
)

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX
        "precompiled_headers"
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp
)