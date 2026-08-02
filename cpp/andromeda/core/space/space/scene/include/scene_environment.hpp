#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_environment.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	/// @brief Stores global scene environment settings.
	///
	/// Provides environment-wide rendering properties such as ambient lighting,
	/// background color, and grid scaling.
	class SPACE_API SceneEnvironment
		: public virtual ISceneEnvironment
	{
	public:
		/// @brief Constructs a scene environment.
		SceneEnvironment();

		/// @brief Destroys the scene environment.
		~SceneEnvironment() override;

		// Getters

		/// @brief Retrieves the ambient lighting strength.
		///
		/// @return Ambient lighting strength.
		float get_ambient_strength() const override;

		/// @brief Retrieves the scene background color.
		///
		/// @return Background color.
		const math::Vec4& get_background_color() const override;

		// Setters

		/// @brief Sets the ambient lighting strength.
		///
		/// @param ambient_strength New ambient lighting strength.
		void set_ambient_strength(float ambient_strength) override;

		/// @brief Sets the scene background color.
		///
		/// @param background_color New background color.
		void set_background_color(const math::Vec4& background_color) override;

		/// @brief Resizes the scene grid.
		///
		/// @param resize_factor Scale factor applied to the grid.
		void resize_grid(float resize_factor) override;

	protected:
		/// @brief Ambient lighting strength.
		float m_ambient_strength;

		/// @brief Scene background color.
		math::Vec4 m_background_color;
	};
}
