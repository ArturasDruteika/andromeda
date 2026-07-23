#ifndef API__OBJECTS__I_SKYROOM__HPP
#define API__OBJECTS__I_SKYROOM__HPP


#include "i_geometric_object.hpp"
#include "i_surface_object.hpp"


namespace Andromeda
{
	class ISkyroom
		: public virtual IGeometricObject
		, public virtual ISurfaceObject
	{
	public:
		virtual ~ISkyroom() = default;

		// Getters
		virtual float get_half_extent() const = 0;
		// Setters
		virtual void set_half_extent(float half_extent) = 0;
	};
}


#endif // API__OBJECTS__I_SKYROOM__HPP