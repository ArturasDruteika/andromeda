#pragma once


#include "object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/colors/colors.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"
#include "mesh.hpp"


namespace andromeda::space
{
	/// @brief Represents a geometric object in the scene.
	///
	/// Provides a common implementation for renderable geometry by storing its
	/// mesh data and display color.
	class SPACE_API GeometricObject
		: public virtual IGeometricObject
		, public Object
	{
	public:
		/// @brief Constructs a geometric object with default properties.
		GeometricObject();

		/// @brief Constructs a geometric object with the specified color.
		///
		/// @param color Initial object color.
		GeometricObject(const Color& color);

		/// @brief Destroys the geometric object.
		~GeometricObject() override;

		// Getters

		/// @brief Retrieves the object's mesh.
		///
		/// @return Mesh describing the object's geometry.
		const Mesh& get_mesh() const override;

		/// @brief Retrieves the object's display color.
		///
		/// @return Object color.
		const Color& get_color() const override;

		// Setters

		/// @brief Sets the object's mesh.
		///
		/// @param mesh New mesh describing the object's geometry.
		void set_mesh(const Mesh& mesh);

		/// @brief Sets the object's display color.
		///
		/// @param color New object color.
		void set_color(const Color& color) override;

	protected:
		/// @brief Display color of the object.
		Color m_color;

		/// @brief Mesh describing the object's geometry.
		Mesh m_mesh;
	};
}
