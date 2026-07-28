#ifndef ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP
#define ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP


#include "object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/colors/colors.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"
#include "mesh.hpp"


namespace andromeda::space
{
	class SPACE_API GeometricObject
		: public virtual IGeometricObject
		, public Object
	{
	public:
		GeometricObject();
		GeometricObject(const Color& color);
		~GeometricObject() override;

		// Getters
		const Mesh& get_mesh() const override;
		const Color& get_color() const override;
		// Setters
		void set_mesh(const Mesh& mesh);
		void set_color(const Color& color) override;

	protected:
		Color m_color;
		Mesh m_mesh;
	};
}


#endif // ANDROMEDA__SPACE__GEOMETRIC_OBJECT__HPP