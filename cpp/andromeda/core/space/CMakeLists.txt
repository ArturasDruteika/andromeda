cmake_minimum_required(VERSION 3.24)

project(space)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ==== Camera ====
set(CAMERA_HEADERS
    include/andromeda/space/camera/perspective_control.hpp
    include/andromeda/space/camera/camera_view.hpp
    include/andromeda/space/camera/camera_controller.hpp
    include/andromeda/space/camera/camera.hpp
)

set(CAMERA_SOURCES
    src/camera/perspective_control.cpp
    src/camera/camera_view.cpp
    src/camera/camera_controller.cpp
    src/camera/camera.cpp
)


# ==== Coordinates ====
set(COORDINATES_HEADERS
    include/andromeda/space/coordinates/points.hpp
)


# ==== Light ====
set(LIGHT_HEADERS
    include/andromeda/space/light/light.hpp
    include/andromeda/space/light/directional_light.hpp
    include/andromeda/space/light/point_light.hpp
    include/andromeda/space/light/spot_light.hpp
    include/andromeda/space/light/light_data.hpp
)

set(LIGHT_SOURCES
    src/light/light.cpp
    src/light/directional_light.cpp
    src/light/point_light.cpp
    src/light/spot_light.cpp
    src/light/light_data.cpp
)


# ==== Materials ====
set(MATERIALS_HEADERS
    include/andromeda/space/materials/materials.hpp
    include/andromeda/space/materials/materials_library.hpp
    include/andromeda/space/materials/material_types.hpp
)

set(MATERIALS_SOURCES
    src/materials/materials.cpp
    src/materials/materials_library.cpp
)


# ==== Objects ====
set(OBJECTS_HEADERS
    include/andromeda/space/objects/camera_object.hpp
    include/andromeda/space/objects/cube.hpp
    include/andromeda/space/objects/geometric_object.hpp
    include/andromeda/space/objects/light_object.hpp
    include/andromeda/space/objects/mesh.hpp
    include/andromeda/space/objects/object.hpp
    include/andromeda/space/objects/skyroom.hpp
    include/andromeda/space/objects/sphere.hpp
    include/andromeda/space/objects/surface_object.hpp
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
    include/andromeda/space/scene/camera_handler.hpp
    include/andromeda/space/scene/scene.hpp
    include/andromeda/space/scene/scene_environment.hpp
    include/andromeda/space/scene/scene_lighting.hpp
    include/andromeda/space/scene/scene_node_manager.hpp
    include/andromeda/space/scene/scene_objects.hpp
    include/andromeda/space/scene/scene_state.hpp
    include/andromeda/space/scene/scene_update_hooks.hpp
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


# ==== Update Hooks ====
set(UPDATE_HOOKS_HEADERS
    include/andromeda/space/update_hooks/update_hooks.hpp
)

set(UPDATE_HOOKS_SOURCES
    src/update_hooks/update_hooks.cpp
)


# ==== Scene Graph ====
set(SCENE_GRAPH_HEADERS
    include/andromeda/space/scene_graph/scene_component.hpp
    include/andromeda/space/scene_graph/scene_node.hpp
    include/andromeda/space/scene_graph/object_component.hpp
    include/andromeda/space/scene_graph/light_component.hpp
)

set(SCENE_GRAPH_SOURCES
    src/scene_graph/scene_component.cpp
    src/scene_graph/scene_node.cpp
    src/scene_graph/object_component.cpp
    src/scene_graph/light_component.cpp
)


# ==== Transformations ====
set(TRANSFORMATIONS_HEADERS
    include/andromeda/space/transformations/rotatable.hpp
    include/andromeda/space/transformations/scalable.hpp
    include/andromeda/space/transformations/transformable.hpp
    include/andromeda/space/transformations/transformation_types.hpp
    include/andromeda/space/transformations/translatable.hpp
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


# ==== Export Header ====
include(GenerateExportHeader)

generate_export_header(${PROJECT_NAME}
    BASE_NAME SPACE
    EXPORT_MACRO_NAME SPACE_API
    EXPORT_FILE_NAME
        "${CMAKE_CURRENT_SOURCE_DIR}/include/andromeda/space/macro_export/macro_export.hpp"
)


# ==== Include Directories ====
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
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


# ==== Material Properties ====
set(MATERIAL_JSON_FILENAME
    "material_properties.json"
)

set(MATERIAL_JSON_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/material_properties/${MATERIAL_JSON_FILENAME}"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(MATERIAL_JSON_OUTPUT_DIR
        "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/$<CONFIG>/material_properties"
    )
else()
    set(MATERIAL_JSON_OUTPUT_DIR
        "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/material_properties"
    )
endif()

set(MATERIAL_JSON_OUTPUT
    "${MATERIAL_JSON_OUTPUT_DIR}/${MATERIAL_JSON_FILENAME}"
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${MATERIAL_JSON_OUTPUT_DIR}"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MATERIAL_JSON_SOURCE}"
        "${MATERIAL_JSON_OUTPUT}"

    COMMENT
        "Copying ${MATERIAL_JSON_FILENAME} to ${MATERIAL_JSON_OUTPUT_DIR}"
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
        "update_hooks"
    FILES
        ${UPDATE_HOOKS_HEADERS}
        ${UPDATE_HOOKS_SOURCES}
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