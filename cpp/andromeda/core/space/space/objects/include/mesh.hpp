#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "pch.hpp"
#include "andromeda/space/vertices/vertex.hpp"
#include "andromeda/space/objects/i_mesh.hpp"


namespace andromeda::space
{
	/// @brief Stores mesh geometry data.
	///
	/// Provides a concrete implementation of the mesh interface by storing the
	/// vertex and index buffers that define a renderable mesh.
	class SPACE_API Mesh
		: public IMesh
	{
	public:
		/// @brief Constructs an empty mesh.
		Mesh();

		/// @brief Destroys the mesh.
		~Mesh();

		// Getters

		/// @brief Retrieves the number of mesh indices.
		///
		/// @return Number of indices.
		unsigned int get_index_count() const override;

		/// @brief Retrieves the number of mesh vertices.
		///
		/// @return Number of vertices.
		unsigned int get_vertex_count() const override;

		/// @brief Retrieves the mesh index buffer.
		///
		/// @return Collection of mesh indices.
		const std::vector<unsigned int>& get_indices() const override;

		/// @brief Retrieves the mesh vertex buffer.
		///
		/// @return Collection of mesh vertices.
		const std::vector<Vertex>& get_vertices() const override;

		// Setters

		/// @brief Sets the mesh geometry data.
		///
		/// @param vertices Vertex buffer.
		/// @param indices Index buffer.
		void set_data(
			const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices
		);

	protected:
		/// @brief Mesh index buffer.
		std::vector<unsigned int> m_indices;

		/// @brief Mesh vertex buffer.
		std::vector<Vertex> m_vertices;
	};
}
