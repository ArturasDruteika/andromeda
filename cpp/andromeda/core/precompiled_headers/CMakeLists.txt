cmake_minimum_required(VERSION 3.24)

project(precompiled_headers LANGUAGES CXX)

# Require C++23 for consumers
add_library(precompiled_headers INTERFACE)
target_compile_features(precompiled_headers INTERFACE cxx_std_23)

# Header location exported to consumers
target_include_directories(precompiled_headers
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# The actual PCH (applies to any target that links this INTERFACE)
target_precompile_headers(precompiled_headers
    INTERFACE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp>"
)

# (Optional) group for IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "precompiled_headers" FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp
)
