#include "../include/cube.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::space
{
	Cube::Cube(float half_extent, const Color& color)
		: GeometricObject(color)
		, m_half_extent(half_extent)
	{
		construct_cube(m_half_extent, color);
	}

	Cube::~Cube() = default;

	float Cube::get_half_extent() const
	{
		return m_half_extent;
	}

	void Cube::set_half_extent(float half_extent)
	{
		if (half_extent <= 0.0f)
		{
			spdlog::error("Cube half-extent must be greater than zero. Given half-extent: {}", half_extent);
			return;
		}

		m_half_extent = half_extent;
		construct_cube(m_half_extent, m_color);
	}

	void Cube::construct_cube(float half_extent, const Color& color)
	{
		if (half_extent <= 0.0f)
		{
			spdlog::error("Cube half-extent must be greater than zero. Given half-extent: {}", half_extent);
			return;
		}

		const float h = half_extent;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		reserve_cube_buffers(vertices, indices);

		std::array<CubeFaceData, 6> faces = build_cube_faces(h);

		unsigned int index_offset = 0;
		for (const CubeFaceData& face : faces)
		{
			append_face(face, color, vertices, indices, index_offset);
		}

		Mesh mesh;
		mesh.set_data(vertices, indices);

		set_mesh(mesh);
	}

	std::array<CubeFaceData, 6> Cube::build_cube_faces(float half_extent)
	{
		return std::array<CubeFaceData, 6>
		{
			CubeFaceData
			{
				math::Vec3(0.0f, 0.0f, -1.0f),
				{
					math::Vec3(-half_extent, -half_extent, -half_extent),
					math::Vec3(-half_extent,  half_extent, -half_extent),
					math::Vec3(half_extent,  half_extent, -half_extent),
					math::Vec3(half_extent, -half_extent, -half_extent)
				}
			}, // Back (-Z)

			CubeFaceData
			{
				math::Vec3(0.0f, 0.0f,  1.0f),
				{
					math::Vec3(-half_extent, -half_extent,  half_extent),
					math::Vec3(half_extent, -half_extent,  half_extent),
					math::Vec3(half_extent,  half_extent,  half_extent),
					math::Vec3(-half_extent,  half_extent,  half_extent)
				}
			}, // Front (+Z)

			CubeFaceData
			{
				math::Vec3(-1.0f, 0.0f, 0.0f),
				{
					math::Vec3(-half_extent, -half_extent, -half_extent),
					math::Vec3(-half_extent, -half_extent,  half_extent),
					math::Vec3(-half_extent,  half_extent,  half_extent),
					math::Vec3(-half_extent,  half_extent, -half_extent)
				}
			}, // Left (-X)

			CubeFaceData
			{
				math::Vec3(1.0f, 0.0f, 0.0f),
				{
					math::Vec3(half_extent, -half_extent, -half_extent),
					math::Vec3(half_extent,  half_extent, -half_extent),
					math::Vec3(half_extent,  half_extent,  half_extent),
					math::Vec3(half_extent, -half_extent,  half_extent)
				}
			}, // Right (+X)

			CubeFaceData
			{
				math::Vec3(0.0f, -1.0f, 0.0f),
				{
					math::Vec3(-half_extent, -half_extent, -half_extent),
					math::Vec3(half_extent, -half_extent, -half_extent),
					math::Vec3(half_extent, -half_extent,  half_extent),
					math::Vec3(-half_extent, -half_extent,  half_extent)
				}
			}, // Bottom (-Y)

			CubeFaceData
			{
				math::Vec3(0.0f,  1.0f, 0.0f),
				{
					math::Vec3(-half_extent,  half_extent,  half_extent),
					math::Vec3(half_extent,  half_extent,  half_extent),
					math::Vec3(half_extent,  half_extent, -half_extent),
					math::Vec3(-half_extent,  half_extent, -half_extent)
				}
			}  // Top (+Y)
		};
	}

	void Cube::reserve_cube_buffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
	{
		// 6 faces * 4 verts each = 24 verts (flat normals per face)
		// 6 faces * 2 triangles each * 3 = 36 indices
		vertices.reserve(24);
		indices.reserve(36);
	}

	void Cube::append_face(
		const CubeFaceData& face,
		const Color& color,
		std::vector<Vertex>& out_vertices,
		std::vector<unsigned int>& out_indices,
		unsigned int& index_offset
	)
	{
		for (const math::Vec3& pos : face.vertices)
		{
			out_vertices.emplace_back(
				pos,
				color,
				face.normal
			);
		}

		// Two triangles: (0,1,2) and (2,3,0) in face-local quad
		out_indices.push_back(index_offset + 0);
		out_indices.push_back(index_offset + 1);
		out_indices.push_back(index_offset + 2);

		out_indices.push_back(index_offset + 2);
		out_indices.push_back(index_offset + 3);
		out_indices.push_back(index_offset + 0);

		index_offset += 4;
	}
}