# ==== Target ====

add_library(api_graphics_context INTERFACE)

add_library(andromeda::api::graphics_context
    ALIAS api_graphics_context
)

target_compile_features(api_graphics_context
    INTERFACE
        cxx_std_23
)

# ==== Headers ====

set(GRAPHICS_CONTEXT_HEADERS
    andromeda/graphics_context/i_graphics_context.hpp
)

target_sources(api_graphics_context
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${GRAPHICS_CONTEXT_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_graphics_context
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

target_link_libraries(api_graphics_context
    INTERFACE
        andromeda::api::window
)

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/graphics_context
    PREFIX
        "graphics_context"
    FILES
        ${GRAPHICS_CONTEXT_HEADERS}
)