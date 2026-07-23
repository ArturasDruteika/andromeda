#ifndef API__OBJECTS__I_LIGHT_OBJECT__HPP
#define API__OBJECTS__I_LIGHT_OBJECT__HPP


#include "i_object.hpp"
#include "../light/light_types.hpp"


namespace Andromeda
{
	class ILightObject
		: public virtual IObject
	{
	public:
		virtual ~ILightObject() = default;

		// Getters
		virtual const LightType& get_light_type() const = 0;
	};
}


#endif // API__OBJECTS__I_LIGHT_OBJECT__HPP