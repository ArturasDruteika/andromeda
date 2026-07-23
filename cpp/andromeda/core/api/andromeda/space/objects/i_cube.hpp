#ifndef API__OBJECTS__INTERFACES__I_CUBE__HPP
#define API__OBJECTS__INTERFACES__I_CUBE__HPP


#include "i_geometric_object.hpp"
#include "i_surface_object.hpp"


namespace Andromeda
{
	class ICube
		: public virtual IGeometricObject
		, public virtual ISurfaceObject
	{
	public:
		virtual ~ICube() = default;

		virtual float get_half_extent() const = 0;
	};
}


#endif // API__OBJECTS__INTERFACES__I_CUBE__HPP