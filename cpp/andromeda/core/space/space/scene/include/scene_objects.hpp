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
	/// @brief Manages the geometric objects contained within a scene.
	///
	/// Stores renderable objects together with their associated transforms,
	/// allowing efficient lookup by object identifier.
	class SPACE_API SceneObjects
		: public virtual ISceneObjects
	{
	public:
		/// @brief Constructs a scene object manager.
		SceneObjects();

		/// @brief Destroys the scene object manager.
		~SceneObjects() override;

		// Getters

		/// @brief Retrieves all geometric objects in the scene.
		///
		/// @return Map of geometric objects indexed by object identifier.
		const std::unordered_map<int, IGeometricObject*>& get_objects() const override;

		/// @brief Retrieves the transforms associated with scene objects.
		///
		/// @return Map of object transforms indexed by object identifier.
		const std::unordered_map<int, ITransformable*>& get_object_transforms() const override;

		/// @brief Registers a geometric object with the scene.
		///
		/// @param id Object identifier.
		/// @param object Pointer to the geometric object.
		virtual void add_object(int id, IGeometricObject* object) override;

		/// @brief Removes a geometric object from the scene.
		///
		/// @param id Identifier of the object to remove.
		virtual void remove_object(int id) override;

		/// @brief Associates a transform with a scene object.
		///
		/// @param id Object identifier.
		/// @param transform Pointer to the object's transform.
		void set_object_transform(int id, ITransformable* transform);

	protected:
		/// @brief Collection of geometric objects indexed by object identifier.
		std::unordered_map<int, IGeometricObject*> m_objects;

		/// @brief Collection of object transforms indexed by object identifier.
		std::unordered_map<int, ITransformable*> m_object_transforms;
	};
}


#endif // SPACE__SCENE__SCENE_OBJECTS__HPP