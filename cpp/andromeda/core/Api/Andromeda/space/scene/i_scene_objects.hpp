#ifndef API__SCENE__I_SCENE_OBJECTS__HPP
#define API__SCENE__I_SCENE_OBJECTS__HPP


#include "../objects/i_geometric_object.hpp"
#include "../objects/i_light_object.hpp"
#include "../transformations/i_transformable.hpp"
#include <map>


namespace Andromeda
{
	class ISceneObjects
	{
	public:
		virtual ~ISceneObjects() = default;

		// Getters
		virtual const std::unordered_map<int, IGeometricObject*>& get_objects() const = 0;
		virtual const std::unordered_map<int, ITransformable*>& get_object_transforms() const = 0;
		
		virtual void add_object(int id, IGeometricObject* object) = 0;
		virtual void remove_object(int id) = 0;
	};
}


#endif // API__SCENE__I_SCENE_OBJECTS__HPP