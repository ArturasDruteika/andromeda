#include "../include/gpu_mesh_open_gl.hpp"
#include "../../vertices/include/vertex_layout_open_gl.hpp"
#include "glad/gl.h"


namespace andromeda::rendering
{
    GpuMeshOpenGL::GpuMeshOpenGL()
        : m_vao{ 0 }
        , m_vbo{ 0 }
        , m_ebo{ 0 }
        , m_index_count{ 0 }
    {
    }

    GpuMeshOpenGL::~GpuMeshOpenGL()
    {
        destroy();
    }

    GpuMeshOpenGL::GpuMeshOpenGL(GpuMeshOpenGL&& other) noexcept
        : m_vao{ 0 }
        , m_vbo{ 0 }
        , m_ebo{ 0 }
        , m_index_count{ 0 }
    {
        move_from(other);
    }

    GpuMeshOpenGL& GpuMeshOpenGL::operator=(GpuMeshOpenGL&& other) noexcept
    {
        if (this != &other)
        {
            destroy();
            move_from(other);
        }
        return *this;
    }

    void GpuMeshOpenGL::move_from(GpuMeshOpenGL& other) noexcept
    {
        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_ebo = other.m_ebo;
        m_index_count = other.m_index_count;

        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_ebo = 0;
        other.m_index_count = 0;
    }

    bool GpuMeshOpenGL::is_valid() const
    {
        return m_vao != 0;
    }

    void GpuMeshOpenGL::create(
        const void* vertex_data,
        size_t vertex_data_size_bytes,
        const std::vector<uint32_t>& indices,
        const andromeda::rendering::VertexLayout& layout
    )
    {
        destroy();

        m_index_count = static_cast<uint32_t>(indices.size());

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertex_data_size_bytes), vertex_data, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(uint32_t)), indices.data(), GL_STATIC_DRAW);

        VertexLayoutOpenGL::apply(layout);

        glBindVertexArray(0);
    }

    void GpuMeshOpenGL::create(const IMesh& mesh, const VertexLayout& layout)
    {
        const std::vector<Vertex>& vertices = mesh.get_vertices();
        const std::vector<unsigned int>& indices_ui = mesh.get_indices();

        std::vector<uint32_t> indices_u32;
        indices_u32.reserve(indices_ui.size());
        for (unsigned int idx : indices_ui)
        {
            indices_u32.push_back(static_cast<uint32_t>(idx));
        }

        create(
            vertices.data(),
            vertices.size() * sizeof(Vertex),
            indices_u32,
            layout
        );
    }

    void GpuMeshOpenGL::destroy()
    {
        if (m_ebo != 0)
        {
            glDeleteBuffers(1, &m_ebo);
            m_ebo = 0;
        }
        if (m_vbo != 0)
        {
            glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }
        if (m_vao != 0)
        {
            glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }

        m_index_count = 0;
    }

    uint32_t GpuMeshOpenGL::get_vao() const
    {
        return m_vao;
    }

    uint32_t GpuMeshOpenGL::get_vbo() const
    {
        return m_vbo;
    }

    uint32_t GpuMeshOpenGL::get_ebo() const
    {
        return m_ebo;
    }

    uint32_t GpuMeshOpenGL::get_index_count() const
    {
        return m_index_count;
    }
}