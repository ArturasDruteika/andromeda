# ==== Target ====

add_library(api_window INTERFACE)

add_library(andromeda::api::window
    ALIAS api_window
)

target_compile_features(api_window
    INTERFACE
        cxx_std_23
)

# ==== Events ====

set(EVENT_HEADERS
    andromeda/window/events/event_type.hpp
    andromeda/window/events/i_event.hpp
    andromeda/window/events/i_frame_buffer_events.hpp
    andromeda/window/events/i_key_events.hpp
    andromeda/window/events/i_mouse_events.hpp
)

# ==== Mouse / Keyboard Codes ====

set(INPUT_CODE_HEADERS
    andromeda/window/mouse_and_key_codes/key_codes.hpp
    andromeda/window/mouse_and_key_codes/mouse_codes.hpp
)

# ==== Window ====

set(WINDOW_HEADERS
    andromeda/window/window/i_window.hpp
)

# ==== Header File Set ====

target_sources(api_window
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${EVENT_HEADERS}
            ${INPUT_CODE_HEADERS}
            ${WINDOW_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_window
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

# No other Andromeda API module dependencies currently.

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/window
    PREFIX
        "window"
    FILES
        ${EVENT_HEADERS}
        ${INPUT_CODE_HEADERS}
        ${WINDOW_HEADERS}
)