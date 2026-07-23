cmake_minimum_required(VERSION 3.24)

project(Api LANGUAGES CXX)

# Static (header-only) library
add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# ==== Camera ====
set(CAMERA_HEADERS
    Andromeda/space/camera/i_camera.hpp
    Andromeda/space/camera/i_perspective_control.hpp
    Andromeda/space/camera/i_camera_view.hpp
    Andromeda/space/camera/i_camera_controller.hpp
)

# ==== Colors ====
set(COLORS_HEADERS
    Andromeda/space/colors/colors.hpp
)

# ==== Components ====
set(COMPONENTS_HEADERS
    Andromeda/components/graphics_backend.hpp
)

# ==== Engine ====
set(ENGINE_HEADERS
    Andromeda/engine/i_engine.hpp
)

# ==== GraphicsContext ====
set(GRAPHICS_CONTEXT_HEADERS
    Andromeda/graphics_context/i_graphics_context.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    Andromeda/space/light/i_directional_light.hpp
    Andromeda/space/light/i_point_light.hpp
    Andromeda/space/light/i_light.hpp
    Andromeda/space/light/i_spot_light.hpp
    Andromeda/space/light/light_types.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    Andromeda/space/materials/i_material.hpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    Andromeda/space/objects/i_camera_object.hpp
    Andromeda/space/objects/i_cube.hpp
    Andromeda/space/objects/i_geometric_object.hpp
    Andromeda/space/objects/i_light_object.hpp
    Andromeda/space/objects/i_mesh.hpp
    Andromeda/space/objects/i_object.hpp
    Andromeda/space/objects/i_skyroom.hpp
    Andromeda/space/objects/i_sphere.hpp
    Andromeda/space/objects/i_surface_object.hpp
)

# ==== Platform ====
set(PLATFORM_HEADERS
    Andromeda/platform/i_platform.hpp
)

# ==== Renderer ====
set(RENDERER_HEADERS
    Andromeda/renderer/i_grid_control.hpp
    Andromeda/renderer/i_illumination_control.hpp
    Andromeda/renderer/i_renderer.hpp
    Andromeda/renderer/i_size_control.hpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Andromeda/space/scene/i_camera_handler.hpp
    Andromeda/space/scene/i_scene_node_manager.hpp
    Andromeda/space/scene/i_scene.hpp
    Andromeda/space/scene/i_scene_environment.hpp
    Andromeda/space/scene/i_scene_lighting.hpp
    Andromeda/space/scene/i_scene_objects.hpp
    Andromeda/space/scene/i_scene_state.hpp
    Andromeda/space/scene/i_update_hooks.hpp
    Andromeda/space/scene/i_scene_update_hooks.hpp
)

# ==== SceneGraph ====
set(SCENE_GRAPH_HEADERS
    Andromeda/space/scene_graph/i_scene_component.hpp
    Andromeda/space/scene_graph/i_scene_node.hpp
)

# ==== Transformations ====
set(TRANSFORMATION_HEADERS
    Andromeda/space/transformations/i_rotatable.hpp
    Andromeda/space/transformations/i_scalable.hpp
    Andromeda/space/transformations/i_transformable.hpp
    Andromeda/space/transformations/i_translatable.hpp
    Andromeda/space/transformations/transformation_types.hpp
)

# ==== Vertices ====
set(VERTICES_HEADERS
    Andromeda/space/vertices/vertex.hpp
)

# ==== Window ====
set(WINDOW_HEADERS
    Andromeda/window/events/event_type.hpp
    Andromeda/window/events/i_event.hpp
    Andromeda/window/events/i_frame_buffer_events.hpp
    Andromeda/window/events/i_key_events.hpp
    Andromeda/window/events/i_mouse_events.hpp
    Andromeda/window/mouse_and_key_codes/key_codes.hpp
    Andromeda/window/mouse_and_key_codes/mouse_codes.hpp
    Andromeda/window/window/i_window.hpp
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
        Math
)

# ===== Visual Studio filters (Solution Explorer groups) =====
source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/camera
    PREFIX
        "Camera"
    FILES
        ${CAMERA_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/colors
    PREFIX
        "Colors"
    FILES
        ${COLORS_HEADERS}
)


source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/components
    PREFIX
        "Components"
    FILES
        ${COMPONENTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/graphics_context
    PREFIX
        "GraphicsContext"
    FILES
        ${GRAPHICS_CONTEXT_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/engine
    PREFIX
        "Engine"
    FILES
        ${ENGINE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/light
    PREFIX
        "Light"
    FILES
        ${LIGHT_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/materials
    PREFIX
        "Materials"
    FILES
        ${MATERIALS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/objects
    PREFIX
        "Objects"
    FILES
        ${OBJECTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/platform
    PREFIX
        "Platform"
    FILES
        ${PLATFORM_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/renderer
    PREFIX
        "Renderer"
    FILES
        ${RENDERER_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/scene_graph
    PREFIX
        "SceneGraph"
    FILES
        ${SCENE_GRAPH_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/transformations
    PREFIX
        "Transformations"
    FILES
        ${TRANSFORMATION_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/space/vertices
    PREFIX
        "Vertices"
    FILES
        ${VERTICES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/Andromeda/window
    PREFIX
        "Window"
    FILES
        ${WINDOW_HEADERS}
)
