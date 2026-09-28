# ==== Target ====

add_library(api_platform INTERFACE)

add_library(andromeda::api::platform
    ALIAS api_platform
)

target_compile_features(api_platform
    INTERFACE
        cxx_std_23
)

# ==== Headers ====

set(PLATFORM_HEADERS
    andromeda/platform/i_platform.hpp
)

target_sources(api_platform
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${PLATFORM_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_platform
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

target_link_libraries(api_platform
    INTERFACE
        andromeda::api::components
        andromeda::api::graphics_context
        andromeda::api::window
)

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/platform
    PREFIX
        "platform"
    FILES
        ${PLATFORM_HEADERS}
)