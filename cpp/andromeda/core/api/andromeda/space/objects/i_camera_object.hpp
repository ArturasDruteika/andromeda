#ifndef API__OBJECTS__I_CAMERA_OBJECT__HPP
#define API__OBJECTS__I_CAMERA_OBJECT__HPP


#include "i_object.hpp"


namespace andromeda
{
	class ICameraObject
		: public virtual IObject
	{
	public:
		virtual ~ICameraObject() = default;
	};
}


#endif // API__OBJECTS__I_CAMERA_OBJECT__HPP