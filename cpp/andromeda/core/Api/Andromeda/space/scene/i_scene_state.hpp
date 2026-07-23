#ifndef API__SCENE__I_SCENE_STATE__HPP
#define API__SCENE__I_SCENE_STATE__HPP


#include "../objects/i_geometric_object.hpp"


namespace Andromeda
{
	class ISceneState
	{
	public:
		virtual ~ISceneState() = default;

		virtual bool state_changed(const std::unordered_map<int, IGeometricObject*>& objects) const = 0;
	};
}


#endif // API__SCENE__I_SCENE_STATE__HPP