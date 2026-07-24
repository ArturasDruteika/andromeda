cmake_minimum_required(VERSION 3.24)

project(rendering)

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DRENDERING_EXPORT)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()


# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    rendering/macro_exports/include/macro_exports.hpp
)

# ==== OpenGL backend (platform specific) ====
set(OPENGL_HEADERS
    rendering/open_gl/geometry/include/gpu_mesh_open_gl.hpp
    rendering/open_gl/renderer/include/open_gl_renderer_impl.hpp
    rendering/open_gl/support/include/face_culling_control_open_gl.hpp
    rendering/open_gl/support/include/frame_buffer_open_gl.hpp
    rendering/open_gl/support/include/fps_counter.hpp
    rendering/open_gl/support/include/mesh_cache_open_gl.hpp
    rendering/open_gl/support/include/shadow_renderer_open_gl.hpp
    rendering/open_gl/support/include/text_renderer_open_gl.hpp
    rendering/open_gl/vertices/include/vertex_layout_open_gl.hpp
)

set(OPENGL_SOURCES
    rendering/open_gl/geometry/src/gpu_mesh_open_gl.cpp
    rendering/open_gl/renderer/src/open_gl_renderer_impl.cpp
    rendering/open_gl/support/src/face_culling_control_open_gl.cpp
    rendering/open_gl/support/src/frame_buffer_open_gl.cpp
    rendering/open_gl/support/src/fps_counter.cpp
    rendering/open_gl/support/src/mesh_cache_open_gl.cpp
    rendering/open_gl/support/src/shadow_renderer_open_gl.cpp
    rendering/open_gl/support/src/text_renderer_open_gl.cpp
    rendering/open_gl/vertices/src/vertex_layout_open_gl.cpp
)

# ==== Ray Tracing ====
set(RAY_TRACING_HEADERS
    rendering/ray_tracing/include/ray.hpp
)

# ==== Renderers ====
set(RENDERERS_HEADERS
    rendering/renderers/abstracts/include/grid_control.hpp
    rendering/renderers/abstracts/include/illumination_control.hpp
    rendering/renderers/abstracts/include/size_control.hpp
    rendering/renderers/renderers/include/open_gl_renderer.hpp
)

set(RENDERERS_SOURCES
    rendering/renderers/abstracts/src/grid_control.cpp
    rendering/renderers/abstracts/src/illumination_control.cpp
    rendering/renderers/abstracts/src/size_control.cpp
    rendering/renderers/renderers/src/open_gl_renderer.cpp
)

# ==== Shaders ====
set(SHADERS_HEADERS
    rendering/shaders/abstracts/include/shader_program_open_gl.hpp
    rendering/shaders/abstracts/include/shader_source_manager_open_gl.hpp
    rendering/shaders/interfaces/include/i_shader.hpp
    rendering/shaders/shaders/include/shader_manager.hpp
    rendering/shaders/shaders/include/shader_open_gl.hpp
    rendering/shaders/support/include/shader_compiler_open_gl.hpp
    rendering/shaders/support/include/shader_open_gl_types.hpp
    rendering/shaders/support/include/shader_types.hpp
    rendering/shaders/support/include/uniform_setter_open_gl.hpp
)

set(SHADERS_SOURCES
    rendering/shaders/abstracts/src/shader_program_open_gl.cpp
    rendering/shaders/abstracts/src/shader_source_manager_open_gl.cpp
    rendering/shaders/interfaces/src/i_shader.cpp
    rendering/shaders/shaders/src/shader_manager.cpp
    rendering/shaders/shaders/src/shader_open_gl.cpp
    rendering/shaders/support/src/shader_compiler_open_gl.cpp
    rendering/shaders/support/src/uniform_setter_open_gl.cpp
)

# ==== Utilities ====
set(UTILS_HEADERS
    rendering/utils/include/math_utils.hpp
)

set(UTILS_SOURCES
    rendering/utils/src/math_utils.cpp
)

# ==== Vertices (API agnostic) ====
set(VERTEX_HEADERS
    rendering/vertices/include/vertex_format.hpp
    rendering/vertices/include/vertex_attributes.hpp
    rendering/vertices/include/vertex_layouts.hpp
    rendering/vertices/include/vertex_location_policy.hpp
)

set(VERTEX_SOURCES
    rendering/vertices/src/vertex_format.cpp
    rendering/vertices/src/vertex_layouts.cpp
    rendering/vertices/src/vertex_location_policy.cpp
)

add_library(${PROJECT_NAME}
    SHARED
        ${MACRO_EXPORTS_HEADERS}
        ${RAYTRACING_HEADERS}
        ${RENDERERS_HEADERS}
        ${RENDERERS_SOURCES}
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
        ${SHADERS_HEADERS}
        ${SHADERS_SOURCES}
        ${UTILS_HEADERS}
        ${UTILS_SOURCES}
        ${VERTEX_HEADERS}
        ${VERTEX_SOURCES}
        ${OPENGL_HEADERS}
        ${OPENGL_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Link libraries - Api is INTERFACE, so this just pulls in its usage requirements
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        precompiled_headers
        utils
        Glad
        spdlog::spdlog
        glm::glm
    PUBLIC
        math
        api
)

add_dependencies(${PROJECT_NAME}
    utils
    math
    Glad
)

### Post builds

## Shaders
# Define filenames
# Define shader filenames
set(SHADER_FILES
    "vertex.glsl"
    "fragment.glsl"
    "vertex_illumination.glsl"
    "vertex_grid.glsl"
    "vertex_point_shadow.glsl"
    "fragment_grid.glsl"
    "fragment_luminous_objects.glsl"
    "fragment_non_luminous_objects.glsl"
    "vertex_depth_only.glsl"
    "fragment_depth_only.glsl"
    "fragment_point_shadow.glsl"
    "geometry_point_shadow.glsl"
    "vertex_text.glsl"
)

# Create full source paths
set(SHADER_SOURCE_PATHS "")
foreach(FILE_NAME IN LISTS SHADER_FILES)
    list(APPEND SHADER_SOURCE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgramSources/${FILE_NAME}")
endforeach()

# Determine output directory based on platform
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SHADER_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/$<CONFIG>/shader_program_sources")
else()
    set(SHADER_OUTPUT_DIR "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/shader_program_sources")
endif()

# Create output directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Creating directory ${SHADER_OUTPUT_DIR} for shaders"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_OUTPUT_DIR}"
)

# Copy shaders with echo for each
foreach(SHADER_PATH IN LISTS SHADER_SOURCE_PATHS)
    get_filename_component(FILE_NAME "${SHADER_PATH}" NAME)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying ${FILE_NAME} to ${SHADER_OUTPUT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SHADER_PATH}" "${SHADER_OUTPUT_DIR}/${FILE_NAME}"
    )
endforeach()

# Organize files into Solution Explorer folders
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/ray_tracing
    PREFIX
        "ray_tracing"
    FILES
        ${RAY_TRACING_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/renderers
    PREFIX
        "renderers"
    FILES
        ${RENDERERS_HEADERS}
        ${RENDERERS_SOURCES}
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/shaders
    PREFIX
        "shaders"
    FILES
        ${SHADERS_HEADERS}
        ${SHADERS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/utils
    PREFIX
        "utils"
    FILES
        ${UTILS_HEADERS}
        ${UTILS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/vertices
    PREFIX
        "vertices"
    FILES
        ${VERTEX_HEADERS}
        ${VERTEX_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/open_gl
    PREFIX
        "open_gl"
    FILES
        ${OPENGL_HEADERS}
        ${OPENGL_SOURCES}
)
