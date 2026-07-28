#ifndef RENDERING__GEOMETRY__GPU_MESH_OPENGL__HPP
#define RENDERING__GEOMETRY__GPU_MESH_OPENGL__HPP


#include "../../../vertices/include/vertex_layouts.hpp"
#include "pch.hpp"
#include "andromeda/space/objects/i_mesh.hpp"


namespace andromeda::rendering
{
    class GpuMeshOpenGL
    {
    public:
        GpuMeshOpenGL();
        ~GpuMeshOpenGL();

        GpuMeshOpenGL(const GpuMeshOpenGL& other) = delete;
        GpuMeshOpenGL& operator=(const GpuMeshOpenGL& other) = delete;

        GpuMeshOpenGL(GpuMeshOpenGL&& other) noexcept;
        GpuMeshOpenGL& operator=(GpuMeshOpenGL&& other) noexcept;

        bool is_valid() const;

        void create(
            const void* vertex_data,
            size_t vertex_data_size_bytes,
            const std::vector<uint32_t>& indices,
            const andromeda::rendering::VertexLayout& layout
        );

        // New high-level API (renderer should use this)
        void create(const IMesh& mesh, const VertexLayout& layout);

        void destroy();

        uint32_t get_vao() const;
        uint32_t get_vbo() const;
        uint32_t get_ebo() const;
        uint32_t get_index_count() const;

    private:
        void move_from(GpuMeshOpenGL& other) noexcept;

    private:
        uint32_t m_vao;
        uint32_t m_vbo;
        uint32_t m_ebo;
        uint32_t m_index_count;
    };
}

#endif // RENDERING__GEOMETRY__GPU_MESH_OPENGL__HPP