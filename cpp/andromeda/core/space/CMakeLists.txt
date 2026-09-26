cmake_minimum_required(VERSION 3.24)

project(space)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSPACE_EXPORT)


# ==== Camera ====
set(CAMERA_HEADERS_PUBLIC
    include/public/space/camera/perspective_control.hpp
    include/public/space/camera/camera_view.hpp
    include/public/space/camera/camera_controller.hpp
    include/public/space/camera/camera.hpp
)

set(CAMERA_SOURCES
    src/camera/perspective_control.cpp
    src/camera/camera_view.cpp
    src/camera/camera_controller.cpp
    src/camera/camera.cpp
)

# ==== Coordinates ====
set(COORDINATES_HEADERS
    include/public/space/coordinates/points.hpp
)

# ==== Light ====
set(LIGHT_HEADERS
    include/public/space/light/light.hpp
    include/public/space/light/directional_light.hpp
    include/public/space/light/point_light.hpp
    include/public/space/light/spot_light.hpp
    include/public/space/light/light_data.hpp
)

set(LIGHT_SOURCES
    src/light/light.cpp
    src/light/directional_light.cpp
    src/light/point_light.cpp
    src/light/spot_light.cpp
    src/light/light_data.cpp
)

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    include/private/macro_exports/macro_exports.hpp
)

# ==== Materials ====
set(MATERIALS_HEADERS
    include/public/space/materials/materials.hpp
    include/public/space/materials/materials_library.hpp
    include/public/space/materials/material_types.hpp
)

set(MATERIALS_SOURCES
    src/materials/materials.cpp
    src/materials/materials_library.cpp
)

# ==== Objects ====
set(OBJECTS_HEADERS
    include/public/space/objects/camera_object.hpp
    include/public/space/objects/cube.hpp
    include/public/space/objects/geometric_object.hpp
    include/public/space/objects/light_object.hpp
    include/public/space/objects/mesh.hpp
    include/public/space/objects/object.hpp
    include/public/space/objects/skyroom.hpp
    include/public/space/objects/sphere.hpp
    include/public/space/objects/surface_object.hpp
)

set(OBJECTS_SOURCES
    src/objects/camera_object.cpp
    src/objects/cube.cpp
    src/objects/geometric_object.cpp
    src/objects/light_object.cpp
    src/objects/mesh.cpp
    src/objects/object.cpp
    src/objects/skyroom.cpp
    src/objects/sphere.cpp
    src/objects/surface_object.cpp
)

# ==== Scene ====
set(SCENE_HEADERS
    include/public/space/scene/camera_handler.hpp
    include/public/space/scene/scene.hpp
    include/public/space/scene/scene_environment.hpp
    include/public/space/scene/scene_lighting.hpp
    include/public/space/scene/scene_node_manager.hpp
    include/public/space/scene/scene_objects.hpp
    include/public/space/scene/scene_state.hpp
    include/public/space/scene/scene_update_hooks.hpp
)

# ==== UpdateHooks ====
set(UPDATE_HOOKS_HEADERS
    include/private/update_hooks/update_hooks.hpp
)

set(UPDATE_HOOKS_SOURCES
    src/update_hooks/update_hooks.cpp
)

set(SCENE_SOURCES
    src/scene/camera_handler.cpp
    src/scene/scene.cpp
    src/scene/scene_environment.cpp
    src/scene/scene_lighting.cpp
    src/scene/scene_node_manager.cpp
    src/scene/scene_objects.cpp
    src/scene/scene_state.cpp
    src/scene/scene_update_hooks.cpp
)

# ==== SceneGraph ====
set(SCENE_GRAPH_HEADERS
    include/public/space/scene_graph/scene_component.hpp
    include/public/space/scene_graph/scene_node.hpp
    include/public/space/scene_graph/object_component.hpp
    include/public/space/scene_graph/light_component.hpp
)

set(SCENE_GRAPH_SOURCES
    src/scene_graph/scene_component.cpp
    src/scene_graph/scene_node.cpp
    src/scene_graph/object_component.cpp
    src/scene_graph/light_component.cpp
)

# ==== Transformations ====
set(TRANSFORMATIONS_HEADERS
    include/public/space/transformations/rotatable.hpp
    include/public/space/transformations/scalable.hpp
    include/public/space/transformations/transformable.hpp
    include/public/space/transformations/transformation_types.hpp
    include/public/space/transformations/translatable.hpp
)

set(TRANSFORMATIONS_SOURCES
    src/transformations/rotatable.cpp
    src/transformations/scalable.cpp
    src/transformations/transformable.cpp
    src/transformations/translatable.cpp
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
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private/
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public/
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
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "camera"
    FILES
        ${CAMERA_HEADERS}
        ${CAMERA_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "coordinates"
    FILES
        ${COORDINATES_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "light"
    FILES
        ${LIGHT_HEADERS}
        ${LIGHT_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "macro_exports"
    FILES
        ${MACRO_EXPORTS_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "materials"
    FILES
        ${MATERIALS_HEADERS}
        ${MATERIALS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "objects"
    FILES
        ${OBJECTS_HEADERS}
        ${OBJECTS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "scene"
    FILES
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "scene_graph"
    FILES
        ${SCENE_GRAPH_HEADERS}
        ${SCENE_GRAPH_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/
    PREFIX
        "transformations"
    FILES
        ${TRANSFORMATIONS_HEADERS}
        ${TRANSFORMATIONS_SOURCES}
)
