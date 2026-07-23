#ifndef SPACE__OBJECTS__CAMERA_OBJECT__HPP
#define SPACE__OBJECTS__CAMERA_OBJECT__HPP


#include "Object.hpp"
#include "../../Transformations/include/Rotatable.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "andromeda/space/objects/i_camera_object.hpp"


namespace andromeda::Space
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