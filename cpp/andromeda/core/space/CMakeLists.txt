cmake_minimum_required(VERSION 3.24)

project(space)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPACE_EXPORT)


# ==== Camera ====
set(CAMERA_HEADERS
    Space/camera/include/perspective_control.hpp
    Space/camera/include/camera_view.hpp
    Space/camera/include/camera_controller.hpp
    Space/camera/include/camera.hpp
)

set(CAMERA_SOURCES
    Space/camera/src/perspective_control.cpp
    Space/camera/src/camera_view.cpp
    Space/camera/src/camera_controller.cpp
    Space/camera/src/camera.cpp
)

# ==== Coordinates ====
set(COORDINATES_HEADERS
    Space/coordinates/include/points.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    Space/light/include/light.hpp
    Space/light/include/directional_light.hpp
    Space/light/include/point_light.hpp
    Space/light/include/spot_light.hpp
    Space/light/include/light_data.hpp
)

set(LIGHT_SOURCES
    Space/light/src/light.cpp
    Space/light/src/directional_light.cpp
    Space/light/src/point_light.cpp
    Space/light/src/spot_light.cpp
    Space/light/src/light_data.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    Space/macro_exports/include/macro_exports.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    Space/materials/include/materials.hpp
    Space/materials/include/materials_library.hpp
    Space/materials/include/material_types.hpp
)

set(MATERIALS_SOURCES
    Space/materials/src/materials.cpp
    Space/materials/src/materials_library.cpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    Space/objects/include/camera_object.hpp
    Space/objects/include/cube.hpp
    Space/objects/include/geometric_object.hpp
    Space/objects/include/light_object.hpp
    Space/objects/include/mesh.hpp
    Space/objects/include/object.hpp
    Space/objects/include/skyroom.hpp
    Space/objects/include/sphere.hpp
    Space/objects/include/surface_object.hpp
)

set(OBJECTS_SOURCES
    Space/objects/src/camera_object.cpp
    Space/objects/src/cube.cpp
    Space/objects/src/geometric_object.cpp
    Space/objects/src/light_object.cpp
    Space/objects/src/mesh.cpp
    Space/objects/src/object.cpp
    Space/objects/src/skyroom.cpp
    Space/objects/src/sphere.cpp
    Space/objects/src/surface_object.cpp
)

# ==== Scene ====
set(SCENE_HEADERS
    Space/scene/include/camera_handler.hpp
    Space/scene/include/scene.hpp
    Space/scene/include/scene_environment.hpp
    Space/scene/include/scene_lighting.hpp
    Space/scene/include/scene_node_manager.hpp
    Space/scene/include/scene_objects.hpp
    Space/scene/include/scene_state.hpp
    Space/scene/include/scene_update_hooks.hpp
)

# ==== UpdateHooks ====
set(UPDATE_HOOKS_HEADERS
    Space/update_hooks/include/update_hooks.hpp
)

set(UPDATE_HOOKS_SOURCES
    Space/update_hooks/src/update_hooks.cpp
)

set(SCENE_SOURCES
    Space/scene/src/camera_handler.cpp
    Space/scene/src/scene.cpp
    Space/scene/src/scene_environment.cpp
    Space/scene/src/scene_lighting.cpp
    Space/scene/src/scene_node_manager.cpp
    Space/scene/src/scene_objects.cpp
    Space/scene/src/scene_state.cpp
    Space/scene/src/scene_update_hooks.cpp
)

# ==== SceneGraph ====
set(SCENE_GRAPH_HEADERS
    Space/scene_graph/include/scene_component.hpp
    Space/scene_graph/include/scene_node.hpp
    Space/scene_graph/include/object_component.hpp
    Space/scene_graph/include/light_component.hpp
)

set(SCENE_GRAPH_SOURCES
    Space/scene_graph/src/scene_component.cpp
    Space/scene_graph/src/scene_node.cpp
    Space/scene_graph/src/object_component.cpp
    Space/scene_graph/src/light_component.cpp
)

# ==== Transformations ====
set(TRANSFORMATIONS_HEADERS
    Space/transformations/include/rotatable.hpp
    Space/transformations/include/scalable.hpp
    Space/transformations/include/transformable.hpp
    Space/transformations/include/transformation_types.hpp
    Space/transformations/include/translatable.hpp
)

set(TRANSFORMATIONS_SOURCES
    Space/transformations/src/rotatable.cpp
    Space/transformations/src/scalable.cpp
    Space/transformations/src/transformable.cpp
    Space/transformations/src/translatable.cpp
)

# ==== Target ====
add_library(${PROJECT_NAME}
    SHARED
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
        ${COORDINATES_HEADERS}
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
        ${MACRO_EXPORTS_HEADERS}
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
        ${OBJECTS_HEADERS}
        ${OBJECTS_SOURCES}
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
        ${UPDATE_HOOKS_HEADERS}
        ${UPDATE_HOOKS_SOURCES}
        ${SCENE_GRAPH_HEADERS}
        ${SCENE_GRAPH_SOURCES}
        ${TRANSFORMATIONS_HEADERS}
        ${TRANSFORMATIONS_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# ==== Link Libraries ====
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        precompiled_headers
        api
        math
        utils
        spdlog::spdlog
)

# ==== Dependencies ====
add_dependencies(${PROJECT_NAME}
    math
    utils
)


## Material properties
set(MATERIAL_JSON_FILENAME "material_properties.json")
set(MATERIAL_JSON_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/MaterialProperties/${MATERIAL_JSON_FILENAME}"
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(MATERIAL_JSON_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/$<CONFIG>/material_properties")
else()
    set(MATERIAL_JSON_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/material_properties")
endif()

set(MATERIAL_JSON_OUTPUT "${MATERIAL_JSON_OUTPUT_DIR}/${MATERIAL_JSON_FILENAME}")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${MATERIAL_JSON_OUTPUT_DIR}"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MATERIAL_JSON_SOURCE}"
        "${MATERIAL_JSON_OUTPUT}"

    COMMENT "Copying ${MATERIAL_JSON_FILENAME} to ${MATERIAL_JSON_OUTPUT_DIR}"
)


# ==== IDE Organization ====
source_group(
    TREE 
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/camera
    PREFIX
        "camera"
    FILES
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/coordinates
    PREFIX
        "coordinates"
    FILES
        ${COORDINATES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/light
    PREFIX
        "light"
    FILES
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/macro_exports
    PREFIX
        "macro_exports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/materials
    PREFIX
        "materials"
    FILES
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/objects
    PREFIX
        "objects"
    FILES
        ${OBJECTS_HEADERS}
        ${OBJECTS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/scene
    PREFIX
        "scene"
    FILES
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/scene_graph
    PREFIX
        "scene_graph"
    FILES
        ${SCENE_GRAPH_HEADERS}
        ${SCENE_GRAPH_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/transformations
    PREFIX
        "transformations"
    FILES
        ${TRANSFORMATIONS_HEADERS}
        ${TRANSFORMATIONS_SOURCES}
)
