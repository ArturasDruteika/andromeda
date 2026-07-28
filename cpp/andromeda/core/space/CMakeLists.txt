cmake_minimum_required(VERSION 3.24)

project(space)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPACE_EXPORT)


# ==== Camera ====
set(CAMERA_HEADERS
    space/camera/include/perspective_control.hpp
    space/camera/include/camera_view.hpp
    space/camera/include/camera_controller.hpp
    space/camera/include/camera.hpp
)

set(CAMERA_SOURCES
    space/camera/src/perspective_control.cpp
    space/camera/src/camera_view.cpp
    space/camera/src/camera_controller.cpp
    space/camera/src/camera.cpp
)

# ==== Coordinates ====
set(COORDINATES_HEADERS
    space/coordinates/include/points.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    space/light/include/light.hpp
    space/light/include/directional_light.hpp
    space/light/include/point_light.hpp
    space/light/include/spot_light.hpp
    space/light/include/light_data.hpp
)

set(LIGHT_SOURCES
    space/light/src/light.cpp
    space/light/src/directional_light.cpp
    space/light/src/point_light.cpp
    space/light/src/spot_light.cpp
    space/light/src/light_data.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    space/macro_exports/include/macro_exports.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    space/materials/include/materials.hpp
    space/materials/include/materials_library.hpp
    space/materials/include/material_types.hpp
)

set(MATERIALS_SOURCES
    space/materials/src/materials.cpp
    space/materials/src/materials_library.cpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    space/objects/include/camera_object.hpp
    space/objects/include/cube.hpp
    space/objects/include/geometric_object.hpp
    space/objects/include/light_object.hpp
    space/objects/include/mesh.hpp
    space/objects/include/object.hpp
    space/objects/include/skyroom.hpp
    space/objects/include/sphere.hpp
    space/objects/include/surface_object.hpp
)

set(OBJECTS_SOURCES
    space/objects/src/camera_object.cpp
    space/objects/src/cube.cpp
    space/objects/src/geometric_object.cpp
    space/objects/src/light_object.cpp
    space/objects/src/mesh.cpp
    space/objects/src/object.cpp
    space/objects/src/skyroom.cpp
    space/objects/src/sphere.cpp
    space/objects/src/surface_object.cpp
)

# ==== Scene ====
set(SCENE_HEADERS
    space/scene/include/camera_handler.hpp
    space/scene/include/scene.hpp
    space/scene/include/scene_environment.hpp
    space/scene/include/scene_lighting.hpp
    space/scene/include/scene_node_manager.hpp
    space/scene/include/scene_objects.hpp
    space/scene/include/scene_state.hpp
    space/scene/include/scene_update_hooks.hpp
)

# ==== UpdateHooks ====
set(UPDATE_HOOKS_HEADERS
    space/update_hooks/include/update_hooks.hpp
)

set(UPDATE_HOOKS_SOURCES
    space/update_hooks/src/update_hooks.cpp
)

set(SCENE_SOURCES
    space/scene/src/camera_handler.cpp
    space/scene/src/scene.cpp
    space/scene/src/scene_environment.cpp
    space/scene/src/scene_lighting.cpp
    space/scene/src/scene_node_manager.cpp
    space/scene/src/scene_objects.cpp
    space/scene/src/scene_state.cpp
    space/scene/src/scene_update_hooks.cpp
)

# ==== SceneGraph ====
set(SCENE_GRAPH_HEADERS
    space/scene_graph/include/scene_component.hpp
    space/scene_graph/include/scene_node.hpp
    space/scene_graph/include/object_component.hpp
    space/scene_graph/include/light_component.hpp
)

set(SCENE_GRAPH_SOURCES
    space/scene_graph/src/scene_component.cpp
    space/scene_graph/src/scene_node.cpp
    space/scene_graph/src/object_component.cpp
    space/scene_graph/src/light_component.cpp
)

# ==== Transformations ====
set(TRANSFORMATIONS_HEADERS
    space/transformations/include/rotatable.hpp
    space/transformations/include/scalable.hpp
    space/transformations/include/transformable.hpp
    space/transformations/include/transformation_types.hpp
    space/transformations/include/translatable.hpp
)

set(TRANSFORMATIONS_SOURCES
    space/transformations/src/rotatable.cpp
    space/transformations/src/scalable.cpp
    space/transformations/src/transformable.cpp
    space/transformations/src/translatable.cpp
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
    "${CMAKE_CURRENT_SOURCE_DIR}/material_properties/${MATERIAL_JSON_FILENAME}"
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
