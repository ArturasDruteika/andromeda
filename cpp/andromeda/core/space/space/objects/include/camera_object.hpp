#ifndef SPACE__OBJECTS__CAMERA_OBJECT__HPP
#define SPACE__OBJECTS__CAMERA_OBJECT__HPP


#include "object.hpp"
#include "../../transformations/include/rotatable.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/objects/i_camera_object.hpp"


namespace andromeda::space
{
	class SPACE_API CameraObject
		: public virtual ICameraObject
		, public Object
	{
	public:
		CameraObject();
		~CameraObject() override;
	};
}


#endif // SPACE__OBJECTS__CAMERA_OBJECT__HPP