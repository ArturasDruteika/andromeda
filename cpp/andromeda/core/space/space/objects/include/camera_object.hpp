#ifndef SPACE__OBJECTS__CAMERA_OBJECT__HPP
#define SPACE__OBJECTS__CAMERA_OBJECT__HPP


#include "object.hpp"
#include "../../transformations/include/rotatable.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
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


#endif // SPACE__OBJECTS__CAMERA_OBJECT__HPP