#ifndef API__OBJECTS__I_GEOMETRIC_OBJECT__HPP
#define API__OBJECTS__I_GEOMETRIC_OBJECT__HPP


#include "i_object.hpp"
#include "i_mesh.hpp"
#include "../colors/colors.hpp"
#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
	class IGeometricObject
        : public virtual IObject
	{
	public:
		virtual ~IGeometricObject() = default;
		
		// Getters
        virtual const IMesh& get_mesh() const = 0;
		virtual const Color& get_color() const = 0;
		// Setters
        virtual void set_color(const Color& color) = 0;
	};
}


#endif // API__OBJECTS__I_GEOMETRIC_OBJECT__HPP