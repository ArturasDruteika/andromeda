#ifndef API__OBJECTS__I_SPHERE__HPP
#define API__OBJECTS__I_SPHERE__HPP


#include "i_geometric_object.hpp"
#include "i_surface_object.hpp"


namespace andromeda
{
	class ISphere
		: public virtual IGeometricObject
		, public virtual ISurfaceObject
	{
	public:
		virtual ~ISphere() = default;

		virtual float get_radius() const = 0;
	};
}


#endif // API__OBJECTS__I_SPHERE__HPP