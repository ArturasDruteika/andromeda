# ==== Target ====

add_library(api_components INTERFACE)

add_library(andromeda::api::components
    ALIAS api_components
)

target_compile_features(api_components
    INTERFACE
        cxx_std_23
)

# ==== Headers ====

set(COMPONENTS_HEADERS
    andromeda/components/graphics_backend.hpp
)

target_sources(api_components
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${COMPONENTS_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_components
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

# No dependencies currently.
# graphics_backend.hpp is a standalone API component.

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/components
    PREFIX
        "components"
    FILES
        ${COMPONENTS_HEADERS}
)