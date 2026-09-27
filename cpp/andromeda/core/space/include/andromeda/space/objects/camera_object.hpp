#pragma once


#include "object.hpp"
#include "../transformations/rotatable.hpp"
#include "andromeda/space/macro_export/macro_export.hpp"
#include "andromeda/space/objects/i_camera_object.hpp"


namespace andromeda::space
{
	/// @brief Represents a camera object within the scene.
	///
	/// Provides a scene object implementation that identifies an object as a
	/// camera while inheriting common object functionality.
	class SPACE_API CameraObject
		: public virtual ICameraObject
		, public Object
	{
	public:
		/// @brief Constructs a camera object.
		CameraObject();

		/// @brief Destroys the camera object.
		~CameraObject() override;
	};
}
