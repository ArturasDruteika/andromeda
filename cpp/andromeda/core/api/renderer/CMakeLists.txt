# ==== Target ====

add_library(api_renderer INTERFACE)

add_library(andromeda::api::renderer
    ALIAS api_renderer
)

target_compile_features(api_renderer
    INTERFACE
        cxx_std_23
)

# ==== Headers ====

set(RENDERER_HEADERS
    andromeda/renderer/i_grid_control.hpp
    andromeda/renderer/i_illumination_control.hpp
    andromeda/renderer/i_renderer.hpp
    andromeda/renderer/i_size_control.hpp
)

target_sources(api_renderer
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${RENDERER_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_renderer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

target_link_libraries(api_renderer
    INTERFACE
        andromeda::api::space
)

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/renderer
    PREFIX
        "renderer"
    FILES
        ${RENDERER_HEADERS}
)