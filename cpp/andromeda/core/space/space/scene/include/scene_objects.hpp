#ifndef SPACE__SCENE__SCENE_OBJECTS__HPP
#define SPACE__SCENE__SCENE_OBJECTS__HPP


#include "../../objects/include/geometric_object.hpp"
#include "../../objects/include/light_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_objects.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"
#include <map>


namespace andromeda::space
{
	class SPACE_API SceneObjects
		: public virtual ISceneObjects
	{
	public:
		SceneObjects();
		~SceneObjects() override;

		// Getters
		const std::unordered_map<int, IGeometricObject*>& get_objects() const override;
		const std::unordered_map<int, ITransformable*>& get_object_transforms() const override;

		virtual void add_object(int id, IGeometricObject* object) override;
		virtual void remove_object(int id) override;

		void set_object_transform(int id, ITransformable* transform);

	protected:
		std::unordered_map<int, IGeometricObject*> m_objects;
		std::unordered_map<int, ITransformable*> m_object_transforms;
	};
}


#endif // SPACE__SCENE__SCENE_OBJECTS__HPP