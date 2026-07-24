#include "../include/skyroom.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::space
{
    Skyroom::Skyroom(float half_extent, const Color& color)
        : GeometricObject(color)
        , m_half_extent(half_extent)
    {
        construct_skyroom(m_half_extent, color);
    }

    Skyroom::~Skyroom() = default;

    float Skyroom::get_half_extent() const
    {
        return m_half_extent;
    }

    void Skyroom::set_half_extent(float half_extent)
    {
        validate_skyroom_params(half_extent);

        if (half_extent <= 0.0f)
        {
            spdlog::error("Skyroom half-extent must be greater than zero. Given half-extent: {}", half_extent);
            return;
        }

        m_half_extent = half_extent;
        construct_skyroom(m_half_extent, get_color());
    }

    void Skyroom::validate_skyroom_params(float half_extent) const
    {
        (void)half_extent;
        // You can clamp/abs here if you want; I keep it strict like Sphere/Cube.
    }

    void Skyroom::construct_skyroom(float half_extent, const Color& color)
    {
        if (half_extent <= 0.0f)
        {
            spdlog::error("Skyroom half-extent must be greater than zero. Given half-extent: {}", half_extent);
            return;
        }

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        reserve_skyroom_buffers(vertices, indices);

        std::array<SkyroomFaceData, 6> faces = build_skyroom_faces(half_extent);

        unsigned int index_offset = 0;
        for (const SkyroomFaceData& face : faces)
        {
            append_face_inside(face, color, vertices, indices, index_offset);
        }

        Mesh mesh;
        mesh.set_data(vertices, indices);

        set_mesh(mesh);
    }

    std::array<SkyroomFaceData, 6> Skyroom::build_skyroom_faces(float half_extent)
    {
        // Inward normals (pointing toward center) and vertex order chosen for inside-facing triangles.
        // This is basically the cube, but normals flipped and winding appropriate for inside view.

        return std::array<SkyroomFaceData, 6>
        {
            SkyroomFaceData
            {
                math::Vec3(0.0f, 0.0f, 1.0f), // inward for back (-Z)
                {
                    math::Vec3(-half_extent, -half_extent, -half_extent),
                    math::Vec3(half_extent, -half_extent, -half_extent),
                    math::Vec3(half_extent,  half_extent, -half_extent),
                    math::Vec3(-half_extent,  half_extent, -half_extent)
                }
            },

            SkyroomFaceData
            {
                math::Vec3(0.0f, 0.0f, -1.0f), // inward for front (+Z)
                {
                    math::Vec3(-half_extent, -half_extent,  half_extent),
                    math::Vec3(-half_extent,  half_extent,  half_extent),
                    math::Vec3(half_extent,  half_extent,  half_extent),
                    math::Vec3(half_extent, -half_extent,  half_extent)
                }
            },

            SkyroomFaceData
            {
                math::Vec3(1.0f, 0.0f, 0.0f), // inward for left (-X)
                {
                    math::Vec3(-half_extent, -half_extent, -half_extent),
                    math::Vec3(-half_extent,  half_extent, -half_extent),
                    math::Vec3(-half_extent,  half_extent,  half_extent),
                    math::Vec3(-half_extent, -half_extent,  half_extent)
                }
            },

            SkyroomFaceData
            {
                math::Vec3(-1.0f, 0.0f, 0.0f), // inward for right (+X)
                {
                    math::Vec3(half_extent, -half_extent, -half_extent),
                    math::Vec3(half_extent, -half_extent,  half_extent),
                    math::Vec3(half_extent,  half_extent,  half_extent),
                    math::Vec3(half_extent,  half_extent, -half_extent)
                }
            },

            SkyroomFaceData
            {
                math::Vec3(0.0f, 1.0f, 0.0f), // inward for bottom (-Y)
                {
                    math::Vec3(-half_extent, -half_extent, -half_extent),
                    math::Vec3(-half_extent, -half_extent,  half_extent),
                    math::Vec3(half_extent, -half_extent,  half_extent),
                    math::Vec3(half_extent, -half_extent, -half_extent)
                }
            },

            SkyroomFaceData
            {
                math::Vec3(0.0f, -1.0f, 0.0f), // inward for top (+Y)
                {
                    math::Vec3(-half_extent,  half_extent, -half_extent),
                    math::Vec3(half_extent,  half_extent, -half_extent),
                    math::Vec3(half_extent,  half_extent,  half_extent),
                    math::Vec3(-half_extent,  half_extent,  half_extent)
                }
            }
        };
    }

    void Skyroom::reserve_skyroom_buffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
    {
        vertices.reserve(24);
        indices.reserve(36);
    }

    void Skyroom::append_face_inside(
        const SkyroomFaceData& face,
        const Color& color,
        std::vector<Vertex>& out_vertices,
        std::vector<unsigned int>& out_indices,
        unsigned int& index_offset
    )
    {
        for (const math::Vec3& pos : face.vertices)
        {
            out_vertices.emplace_back(pos, color, face.normal);
        }

        // Same quad split as Cube. Winding is determined by vertex order in build_skyroom_faces.
        out_indices.push_back(index_offset + 0);
        out_indices.push_back(index_offset + 1);
        out_indices.push_back(index_offset + 2);

        out_indices.push_back(index_offset + 2);
        out_indices.push_back(index_offset + 3);
        out_indices.push_back(index_offset + 0);

        index_offset += 4;
    }
}