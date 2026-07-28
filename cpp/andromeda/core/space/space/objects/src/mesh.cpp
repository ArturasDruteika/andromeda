#include "../include/mesh.hpp"


namespace andromeda::space
{
	Mesh::Mesh() = default;

	Mesh::~Mesh() = default;

	unsigned int Mesh::get_index_count() const
	{
		return m_indices.size();
	}

	unsigned int Mesh::get_vertex_count() const
	{
		return m_vertices.size();
	}

	const std::vector<unsigned int>& Mesh::get_indices() const
	{
		return m_indices;
	}

	const std::vector<Vertex>& Mesh::get_vertices() const
	{
		return m_vertices;
	}

	void Mesh::set_data(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices)
	{
		m_vertices = vertices;
		m_indices = indices;
	}
}