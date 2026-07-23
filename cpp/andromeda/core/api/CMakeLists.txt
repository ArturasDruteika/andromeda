cmake_minimum_required(VERSION 3.24)

project(api LANGUAGES CXX)

# Static (header-only) library
add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# ==== Camera ====
set(CAMERA_HEADERS
    andromeda/space/camera/i_camera.hpp
    andromeda/space/camera/i_perspective_control.hpp
    andromeda/space/camera/i_camera_view.hpp
    andromeda/space/camera/i_camera_controller.hpp
)

# ==== Colors ====
set(COLORS_HEADERS
    andromeda/space/colors/colors.hpp
)

# ==== Components ====
set(COMPONENTS_HEADERS
    andromeda/components/graphics_backend.hpp
)

# ==== engine ====
set(ENGINE_HEADERS
    andromeda/engine/i_engine.hpp
)

# ==== graphics_context ====
set(GRAPHICS_CONTEXT_HEADERS
    andromeda/graphics_context/i_graphics_context.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    andromeda/space/light/i_directional_light.hpp
    andromeda/space/light/i_point_light.hpp
    andromeda/space/light/i_light.hpp
    andromeda/space/light/i_spot_light.hpp
    andromeda/space/light/light_types.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    andromeda/space/materials/i_material.hpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    andromeda/space/objects/i_camera_object.hpp
    andromeda/space/objects/i_cube.hpp
    andromeda/space/objects/i_geometric_object.hpp
    andromeda/space/objects/i_light_object.hpp
    andromeda/space/objects/i_mesh.hpp
    andromeda/space/objects/i_object.hpp
    andromeda/space/objects/i_skyroom.hpp
    andromeda/space/objects/i_sphere.hpp
    andromeda/space/objects/i_surface_object.hpp
)

# ==== platform ====
set(PLATFORM_HEADERS
    andromeda/platform/i_platform.hpp
)

# ==== Renderer ====
set(RENDERER_HEADERS
    andromeda/renderer/i_grid_control.hpp
    andromeda/renderer/i_illumination_control.hpp
    andromeda/renderer/i_renderer.hpp
    andromeda/renderer/i_size_control.hpp
)

# ==== Scene ====
set(SCENE_HEADERS
    andromeda/space/scene/i_camera_handler.hpp
    andromeda/space/scene/i_scene_node_manager.hpp
    andromeda/space/scene/i_scene.hpp
    andromeda/space/scene/i_scene_environment.hpp
    andromeda/space/scene/i_scene_lighting.hpp
    andromeda/space/scene/i_scene_objects.hpp
    andromeda/space/scene/i_scene_state.hpp
    andromeda/space/scene/i_update_hooks.hpp
    andromeda/space/scene/i_scene_update_hooks.hpp
)

# ==== SceneGraph ====
set(SCENE_GRAPH_HEADERS
    andromeda/space/scene_graph/i_scene_component.hpp
    andromeda/space/scene_graph/i_scene_node.hpp
)

# ==== Transformations ====
set(TRANSFORMATION_HEADERS
    andromeda/space/transformations/i_rotatable.hpp
    andromeda/space/transformations/i_scalable.hpp
    andromeda/space/transformations/i_transformable.hpp
    andromeda/space/transformations/i_translatable.hpp
    andromeda/space/transformations/transformation_types.hpp
)

# ==== vertices ====
set(VERTICES_HEADERS
    andromeda/space/vertices/vertex.hpp
)

# ==== Window ====
set(WINDOW_HEADERS
    andromeda/window/events/event_type.hpp
    andromeda/window/events/i_event.hpp
    andromeda/window/events/i_frame_buffer_events.hpp
    andromeda/window/events/i_key_events.hpp
    andromeda/window/events/i_mouse_events.hpp
    andromeda/window/mouse_and_key_codes/key_codes.hpp
    andromeda/window/mouse_and_key_codes/mouse_codes.hpp
    andromeda/window/window/i_window.hpp
)

target_sources(${PROJECT_NAME}
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            ${CAMERA_HEADERS}
            ${COLORS_HEADERS}
            ${COMPONENTS_HEADERS}
            ${ENGINE_HEADERS}
            ${GRAPHICS_CONTEXT_HEADERS}
            ${OBJECTS_HEADERS}
            ${PLATFORM_HEADERS}
            ${RENDERER_HEADERS}
            ${SCENE_HEADERS}
            ${SCENE_GRAPH_HEADERS}
            ${WINDOW_HEADERS}
            ${LIGHT_HEADERS}
            ${MATERIALS_HEADERS}
            ${TRANSFORMATION_HEADERS}
            ${VERTICES_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        math
)

# ===== Visual Studio filters (Solution Explorer groups) =====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/colors
    PREFIX
        "Colors"
    FILES
        ${COLORS_HEADERS}
)


source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/components
    PREFIX
        "Components"
    FILES
        ${COMPONENTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/graphics_context
    PREFIX
        "graphics_context"
    FILES
        ${GRAPHICS_CONTEXT_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/engine
    PREFIX
        "engine"
    FILES
        ${ENGINE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/light
    PREFIX
        "Light"
    FILES
        ${LIGHT_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/materials
    PREFIX
        "Materials"
    FILES
        ${MATERIALS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/objects
    PREFIX
        "Objects"
    FILES
        ${OBJECTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/platform
    PREFIX
        "platform"
    FILES
        ${PLATFORM_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/renderer
    PREFIX
        "Renderer"
    FILES
        ${RENDERER_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/scene_graph
    PREFIX
        "SceneGraph"
    FILES
        ${SCENE_GRAPH_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/transformations
    PREFIX
        "Transformations"
    FILES
        ${TRANSFORMATION_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space/vertices
    PREFIX
        "vertices"
    FILES
        ${VERTICES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/window
    PREFIX
        "Window"
    FILES
        ${WINDOW_HEADERS}
)
