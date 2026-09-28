# ==== Target ====

add_library(api_space INTERFACE)

add_library(andromeda::api::space
    ALIAS api_space
)

target_compile_features(api_space
    INTERFACE
        cxx_std_23
)

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

# ==== Scene Graph ====

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

# ==== Vertices ====

set(VERTICES_HEADERS
    andromeda/space/vertices/vertex.hpp
)

# ==== Header File Set ====

target_sources(api_space
    INTERFACE
        FILE_SET HEADERS
        BASE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/
        FILES
            ${CAMERA_HEADERS}
            ${COLORS_HEADERS}
            ${LIGHT_HEADERS}
            ${MATERIALS_HEADERS}
            ${OBJECTS_HEADERS}
            ${SCENE_HEADERS}
            ${SCENE_GRAPH_HEADERS}
            ${TRANSFORMATION_HEADERS}
            ${VERTICES_HEADERS}
)

# ==== Include Directories ====

target_include_directories(api_space
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Dependencies ====

target_link_libraries(api_space
    INTERFACE
        math
)

# ==== IDE Organization ====

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/andromeda/space
    PREFIX
        "space"
    FILES
        ${CAMERA_HEADERS}
        ${COLORS_HEADERS}
        ${LIGHT_HEADERS}
        ${MATERIALS_HEADERS}
        ${OBJECTS_HEADERS}
        ${SCENE_HEADERS}
        ${SCENE_GRAPH_HEADERS}
        ${TRANSFORMATION_HEADERS}
        ${VERTICES_HEADERS}
)