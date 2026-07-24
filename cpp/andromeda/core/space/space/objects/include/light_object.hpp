#ifndef ANDROMEDA__SPACE__LIGHT_OBJECT__HPP
#define ANDROMEDA__SPACE__LIGHT_OBJECT__HPP


#include "object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/light/light_types.hpp"
#include "andromeda/space/objects/i_light_object.hpp"


namespace andromeda::space
{
	class SPACE_API LightObject
		: public virtual ILightObject
		, public Object
	{
	public:
		LightObject(const LightType& light_type);
		~LightObject() override;

		// Getters
		const LightType& get_light_type() const override;

	protected:
		LightType m_light_type;
	};
}


#endif // ANDROMEDA__SPACE__LIGHT_OBJECT__HPP