# ==== Target ====

add_library(api_application INTERFACE)

add_library(andromeda::api::application
    ALIAS api_application
)

target_compile_features(api_application
    INTERFACE
        cxx_std_23
)

# ==== Headers ====

set(APPLICATION_HEADERS
    andromeda/application/i_application.hpp
)

target_sources(api_application
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${APPLICATION_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_application
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

# Add only API targets required directly by i_application.hpp.
#
# Example:
#
# target_link_libraries(api_application
#     INTERFACE
#         andromeda::api::engine
#         andromeda::api::space
# )

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/application
    PREFIX
        "application"
    FILES
        ${APPLICATION_HEADERS}
)