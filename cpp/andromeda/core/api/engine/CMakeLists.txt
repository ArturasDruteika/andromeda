# ==== Target ====

add_library(api_engine INTERFACE)

add_library(andromeda::api::engine
    ALIAS api_engine
)

target_compile_features(api_engine
    INTERFACE
        cxx_std_23
)

# ==== Headers ====

set(ENGINE_HEADERS
    andromeda/engine/i_engine.hpp
)

target_sources(api_engine
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${ENGINE_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_engine
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

target_link_libraries(api_engine
    INTERFACE
        andromeda::api::macro_exports_api
        andromeda::api::components
        andromeda::api::renderer
        andromeda::api::space
        andromeda::api::window
)

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/engine
    PREFIX
        "engine"
    FILES
        ${ENGINE_HEADERS}
)