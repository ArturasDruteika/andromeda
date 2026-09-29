cmake_minimum_required(VERSION 3.24)

project(api LANGUAGES CXX)

# ==============================================================================
# Macro Exports API
# ==============================================================================

add_library(api_macro_exports_api INTERFACE)

add_library(andromeda::api::macro_exports_api
    ALIAS api_macro_exports_api
)

target_sources(api_macro_exports_api
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/macro_exports_api
        FILES
            ${CMAKE_CURRENT_SOURCE_DIR}/macro_exports_api/macro_exports.hpp
)

target_include_directories(api_macro_exports_api
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/macro_exports_api
)

# ==============================================================================
# API Modules
# ==============================================================================

# Leaf modules first.
add_subdirectory(components)
add_subdirectory(window)
add_subdirectory(space)

# Modules depending on the leaf modules.
add_subdirectory(graphics_context)
add_subdirectory(renderer)

# Higher-level modules.
add_subdirectory(platform)
add_subdirectory(engine)
add_subdirectory(application)

# ==============================================================================
# Complete Andromeda API
# ==============================================================================

# Convenience target providing access to the entire public Andromeda API.
add_library(${PROJECT_NAME} INTERFACE)

add_library(andromeda::api
    ALIAS ${PROJECT_NAME}
)

target_compile_features(${PROJECT_NAME}
    INTERFACE
        cxx_std_23
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        andromeda::api::application
        andromeda::api::components
        andromeda::api::engine
        andromeda::api::graphics_context
        andromeda::api::macro_exports_api
        andromeda::api::platform
        andromeda::api::renderer
        andromeda::api::space
        andromeda::api::window
)