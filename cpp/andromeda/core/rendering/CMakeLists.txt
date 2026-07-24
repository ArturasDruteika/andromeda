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

# SPDLog

# ==== Macro Exports ====
set(MACRO_EXPORTS_HEADERS
    rendering/macro_exports/include/macro_exports.hpp
)

# ==== OpenGL backend (platform specific) ====
set(OPENGL_HEADERS
    rendering/OpenGL/Geometry/include/GpuMeshOpenGL.hpp
    rendering/OpenGL/Renderer/include/RendererOpenGLImpl.hpp
    rendering/OpenGL/Support/include/FaceCullingControlOpenGL.hpp
    rendering/OpenGL/Support/include/FrameBufferOpenGL.hpp
    rendering/OpenGL/Support/include/FPSCounter.hpp
    rendering/OpenGL/Support/include/MeshCacheOpenGL.hpp
    rendering/OpenGL/Support/include/ShadowRendererOpenGL.hpp
    rendering/OpenGL/Support/include/TextRendererOpenGL.hpp
    rendering/OpenGL/vertices/include/VertexLayoutOpenGL.hpp
)

set(OPENGL_SOURCES
    rendering/OpenGL/Geometry/src/GpuMeshOpenGL.cpp
    rendering/OpenGL/Renderer/src/RendererOpenGLImpl.cpp
    rendering/OpenGL/Support/src/FaceCullingControlOpenGL.cpp
    rendering/OpenGL/Support/src/FrameBufferOpenGL.cpp
    rendering/OpenGL/Support/src/FPSCounter.cpp
    rendering/OpenGL/Support/src/MeshCacheOpenGL.cpp
    rendering/OpenGL/Support/src/ShadowRendererOpenGL.cpp
    rendering/OpenGL/Support/src/TextRendererOpenGL.cpp
    rendering/OpenGL/vertices/src/VertexLayoutOpenGL.cpp
)

# ==== RayTracing ====
set(RAYTRACING_HEADERS
    rendering/RayTracing/include/Ray.hpp
)

# ==== Renderers ====
set(RENDERERS_HEADERS
    rendering/Renderers/Abstracts/include/GridControl.hpp
    rendering/Renderers/Abstracts/include/IlluminationControl.hpp
    rendering/Renderers/Abstracts/include/SizeControl.hpp
    rendering/Renderers/Renderers/include/RendererOpenGL.hpp
)

set(RENDERERS_SOURCES
    rendering/Renderers/Abstracts/src/GridControl.cpp
    rendering/Renderers/Abstracts/src/IlluminationControl.cpp
    rendering/Renderers/Abstracts/src/SizeControl.cpp
    rendering/Renderers/Renderers/src/RendererOpenGL.cpp
)

# ==== Shaders ====
set(SHADERS_HEADERS
    rendering/Shaders/Abstracts/include/ShaderProgramOpenGL.hpp
    rendering/Shaders/Abstracts/include/ShaderSourceManagerOpenGL.hpp
    rendering/Shaders/Interfaces/include/IShader.hpp
    rendering/Shaders/Shaders/include/ShaderManager.hpp
    rendering/Shaders/Shaders/include/ShaderOpenGL.hpp
    rendering/Shaders/Support/include/ShaderCompilerOpenGL.hpp
    rendering/Shaders/Support/include/ShaderOpenGLTypes.hpp
    rendering/Shaders/Support/include/ShaderTypes.hpp
    rendering/Shaders/Support/include/UniformSetterOpenGL.hpp
)

set(SHADERS_SOURCES
    rendering/Shaders/Abstracts/src/ShaderProgramOpenGL.cpp
    rendering/Shaders/Abstracts/src/ShaderSourceManagerOpenGL.cpp
    rendering/Shaders/Interfaces/src/IShader.cpp
    rendering/Shaders/Shaders/src/ShaderManager.cpp
    rendering/Shaders/Shaders/src/ShaderOpenGL.cpp
    rendering/Shaders/Support/src/ShaderCompilerOpenGL.cpp
    rendering/Shaders/Support/src/UniformSetterOpenGL.cpp
)

# ==== Utilities ====
set(UTILS_HEADERS
    rendering/Utils/include/mathUtils.hpp
)

set(UTILS_SOURCES
    rendering/Utils/src/mathUtils.cpp
)

# ==== vertices (API agnostic) ====
set(VERTEX_HEADERS
    rendering/vertices/include/VertexFormat.hpp
    rendering/vertices/include/VertexAttributes.hpp
    rendering/vertices/include/VertexLayouts.hpp
    rendering/vertices/include/VertexLocationPolicy.hpp
)

set(VERTEX_SOURCES
    rendering/vertices/src/VertexFormat.cpp
    rendering/vertices/src/VertexLayouts.cpp
    rendering/vertices/src/VertexLocationPolicy.cpp
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
        Utils
        Glad
        spdlog::spdlog
        glm::glm
    PUBLIC
        math
        Api
)

add_dependencies(${PROJECT_NAME}
    Utils
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/RayTracing
    PREFIX
        "RayTracing"
    FILES
        ${RAYTRACING_HEADERS}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Renderers
    PREFIX
        "Renderers"
    FILES
        ${RENDERERS_HEADERS}
        ${RENDERERS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Scene
    PREFIX
        "Scene"
    FILES
        ${SCENE_HEADERS}
        ${SCENE_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Shaders
    PREFIX
        "Shaders"
    FILES
        ${SHADERS_HEADERS}
        ${SHADERS_SOURCES}
)

source_group(
    TREE
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/Utils
    PREFIX
        "Utils"
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
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/OpenGL
    PREFIX
        "OpenGL"
    FILES
        ${OPENGL_HEADERS}
        ${OPENGL_SOURCES}
)
