#include "../include/light_object.hpp"


namespace andromeda::space
{
	LightObject::LightObject(const LightType& light_type)
		: m_light_type{ light_type }
	{
	}

	LightObject::~LightObject() = default;

	const LightType& LightObject::get_light_type() const
	{
		return m_light_type;
	}
}