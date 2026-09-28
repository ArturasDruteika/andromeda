#pragma once


#include "../../../vertices/include/vertex_layouts.hpp"
#include "pch.hpp"
#include "andromeda/space/objects/i_mesh.hpp"


namespace andromeda::rendering
{
    /// @brief Represents a mesh stored in OpenGL GPU memory.
    ///
    /// Manages the lifetime of OpenGL vertex array, vertex buffer, and index
    /// buffer objects used for rendering mesh geometry.
    class GpuMeshOpenGL
    {
    public:
        /// @brief Constructs an empty GPU mesh.
        GpuMeshOpenGL();

        /// @brief Destroys the GPU mesh and releases its resources.
        ~GpuMeshOpenGL();

        GpuMeshOpenGL(const GpuMeshOpenGL& other) = delete;
        GpuMeshOpenGL& operator=(const GpuMeshOpenGL& other) = delete;

        /// @brief Move constructor.
        ///
        /// Transfers ownership of GPU resources from another mesh.
        GpuMeshOpenGL(GpuMeshOpenGL&& other) noexcept;

        /// @brief Move assignment operator.
        ///
        /// Transfers ownership of GPU resources from another mesh.
        GpuMeshOpenGL& operator=(GpuMeshOpenGL&& other) noexcept;

        /// @brief Checks whether the GPU mesh has been created.
        ///
        /// @return `true` if the mesh owns valid OpenGL resources; otherwise,
        /// `false`.
        bool is_valid() const;

        /// @brief Creates GPU resources from raw vertex and index data.
        ///
        /// @param vertex_data Pointer to vertex data.
        /// @param vertex_data_size_bytes Size of the vertex data in bytes.
        /// @param indices Index buffer.
        /// @param layout Vertex buffer layout.
        void create(
            const void* vertex_data,
            size_t vertex_data_size_bytes,
            const std::vector<uint32_t>& indices,
            const andromeda::rendering::VertexLayout& layout
        );

        /// @brief Creates GPU resources from a mesh.
        ///
        /// @param mesh Source mesh.
        /// @param layout Vertex buffer layout.
        void create(const IMesh& mesh, const VertexLayout& layout);

        /// @brief Releases all GPU resources owned by the mesh.
        void destroy();

        /// @brief Retrieves the OpenGL vertex array object identifier.
        ///
        /// @return VAO identifier.
        uint32_t get_vao() const;

        /// @brief Retrieves the OpenGL vertex buffer object identifier.
        ///
        /// @return VBO identifier.
        uint32_t get_vbo() const;

        /// @brief Retrieves the OpenGL element buffer object identifier.
        ///
        /// @return EBO identifier.
        uint32_t get_ebo() const;

        /// @brief Retrieves the number of mesh indices.
        ///
        /// @return Number of indices stored in the index buffer.
        uint32_t get_index_count() const;

    private:
        /// @brief Transfers GPU resource ownership from another mesh.
        ///
        /// @param other Mesh to move resources from.
        void move_from(GpuMeshOpenGL& other) noexcept;

    private:
        /// @brief OpenGL vertex array object.
        uint32_t m_vao;

        /// @brief OpenGL vertex buffer object.
        uint32_t m_vbo;

        /// @brief OpenGL element buffer object.
        uint32_t m_ebo;

        /// @brief Number of indices in the mesh.
        uint32_t m_index_count;
    };
}
