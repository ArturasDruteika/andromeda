#ifndef ANDROMEDA__SPACE__MESH__HPP
#define ANDROMEDA__SPACE__MESH__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "pch.hpp"
#include "andromeda/space/vertices/vertex.hpp"
#include "andromeda/space/objects/i_mesh.hpp"


namespace andromeda::space
{
	class SPACE_API Mesh
		: public IMesh
	{
	public:
		Mesh();
		~Mesh();

		// Getters
		unsigned int get_index_count() const override;
		unsigned int get_vertex_count() const override;
		const std::vector<unsigned int>& get_indices() const override;
		const std::vector<Vertex>& get_vertices() const override;
		// Setters
		void set_data(
			const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices
		);

	protected:
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_vertices;
	};
}


#endif // ANDROMEDA__SPACE__MESH__HPP