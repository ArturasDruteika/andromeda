#pragma once


#include "object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/light/light_types.hpp"
#include "andromeda/space/objects/i_light_object.hpp"


namespace andromeda::space
{
	/// @brief Represents a light object in the scene.
	///
	/// Associates a scene object with a specific light type while providing the
	/// common object functionality shared by all scene objects.
	class SPACE_API LightObject
		: public virtual ILightObject
		, public Object
	{
	public:
		/// @brief Constructs a light object.
		///
		/// @param light_type Type of light represented by this object.
		LightObject(const LightType& light_type);

		/// @brief Destroys the light object.
		~LightObject() override;

		// Getters

		/// @brief Retrieves the type of light represented by this object.
		///
		/// @return Light type.
		const LightType& get_light_type() const override;

	protected:
		/// @brief Type of light represented by this object.
		LightType m_light_type;
	};
}
