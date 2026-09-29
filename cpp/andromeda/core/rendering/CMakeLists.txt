cmake_minimum_required(VERSION 3.24)

project(rendering)

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

# ==== OpenGL Backend (platform specific) ====
set(OPENGL_HEADERS
    include/private/open_gl/geometry/gpu_mesh_open_gl.hpp
    include/private/open_gl/renderer/renderer_open_gl_impl.hpp
    include/private/open_gl/utils/face_culling_control_open_gl.hpp
    include/private/open_gl/utils/frame_buffer_open_gl.hpp
    include/private/open_gl/utils/fps_counter.hpp
    include/private/open_gl/utils/mesh_cache_open_gl.hpp
    include/private/open_gl/utils/shadow_renderer_open_gl.hpp
    include/private/open_gl/utils/text_renderer_open_gl.hpp
    include/private/open_gl/vertices/vertex_layout_open_gl.hpp
)

set(OPENGL_SOURCES
    src/open_gl/geometry/gpu_mesh_open_gl.cpp
    src/open_gl/renderer/renderer_open_gl_impl.cpp
    src/open_gl/utils/face_culling_control_open_gl.cpp
    src/open_gl/utils/frame_buffer_open_gl.cpp
    src/open_gl/utils/fps_counter.cpp
    src/open_gl/utils/mesh_cache_open_gl.cpp
    src/open_gl/utils/shadow_renderer_open_gl.cpp
    src/open_gl/utils/text_renderer_open_gl.cpp
    src/open_gl/vertices/vertex_layout_open_gl.cpp
)


# ==== Ray Tracing ====
set(RAY_TRACING_HEADERS
    include/private/ray_tracing/ray.hpp
)


# ==== Renderers ====
set(RENDERERS_HEADERS
    include/public/andromeda/rendering/abstracts/grid_control.hpp
    include/public/andromeda/rendering/abstracts/illumination_control.hpp
    include/public/andromeda/rendering/abstracts/size_control.hpp
    include/public/andromeda/rendering/renderers/renderer_open_gl.hpp
)

set(RENDERERS_SOURCES
    src/renderers/abstracts/grid_control.cpp
    src/renderers/abstracts/illumination_control.cpp
    src/renderers/abstracts/size_control.cpp
    src/renderers/renderers/renderer_open_gl.cpp
)


# ==== Shaders ====
set(SHADERS_HEADERS
    include/private/shaders/abstracts/shader_program_open_gl.hpp
    include/private/shaders/abstracts/shader_source_manager_open_gl.hpp
    include/private/shaders/interfaces/i_shader.hpp
    include/private/shaders/shaders/shader_manager.hpp
    include/private/shaders/shaders/shader_open_gl.hpp
    include/private/shaders/utils/shader_compiler_open_gl.hpp
    include/private/shaders/utils/shader_open_gl_types.hpp
    include/private/shaders/utils/shader_types.hpp
    include/private/shaders/utils/uniform_setter_open_gl.hpp
)

set(SHADERS_SOURCES
    src/shaders/abstracts/shader_program_open_gl.cpp
    src/shaders/abstracts/shader_source_manager_open_gl.cpp
    src/shaders/interfaces/i_shader.cpp
    src/shaders/shaders/shader_manager.cpp
    src/shaders/shaders/shader_open_gl.cpp
    src/shaders/utils/shader_compiler_open_gl.cpp
    src/shaders/utils/uniform_setter_open_gl.cpp
)


# ==== Utilities ====
set(UTILS_HEADERS
    include/private/utils/math_utils.hpp
)

set(UTILS_SOURCES
    src/utils/math_utils.cpp
)


# ==== Vertices (API agnostic) ====
set(VERTEX_HEADERS
    include/private/vertices/vertex_format.hpp
    include/private/vertices/vertex_attributes.hpp
    include/private/vertices/vertex_layouts.hpp
    include/private/vertices/vertex_location_policy.hpp
)

set(VERTEX_SOURCES
    src/vertices/vertex_format.cpp
    src/vertices/vertex_layouts.cpp
    src/vertices/vertex_location_policy.cpp
)

add_library(${PROJECT_NAME}
    SHARED
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

# ==== Export Header ====
include(GenerateExportHeader)

file(MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export"
)

generate_export_header(${PROJECT_NAME}
    BASE_NAME RENDERING
    EXPORT_MACRO_NAME RENDERING_API
    EXPORT_FILE_NAME
        "${CMAKE_CURRENT_BINARY_DIR}/include/andromeda/${PROJECT_NAME}/macro_export/macro_export.hpp"
)

# ==== Include Directories ====
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private/
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public/
        ${CMAKE_CURRENT_BINARY_DIR}/include/
)

# Link libraries - api is INTERFACE, so this just pulls in its usage requirements
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        precompiled_headers
        utils
        glad
        spdlog::spdlog
        glm::glm
    PUBLIC
        math
        andromeda::api::components
        andromeda::api::graphics_context
        andromeda::api::renderer
)

add_dependencies(${PROJECT_NAME}
    utils
    math
    glad
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
    list(APPEND SHADER_SOURCE_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/shader_program_sources/${FILE_NAME}")
endforeach()

# Shaders live next to bin/ in the install res directory
set(SHADER_OUTPUT_DIR
    "${CMAKE_ASSETS_OUTPUT_DIRECTORY}/shader_program_sources"
)

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
