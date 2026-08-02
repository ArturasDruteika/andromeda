#ifndef SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP
#define SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP


#include "rotatable.hpp"
#include "scalable.hpp"
#include "translatable.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"


namespace andromeda
{
	/// @brief Combines translation, rotation, and scaling into a single transform.
	///
	/// Maintains a model matrix representing the combined transformation and
	/// provides functionality for updating and querying the object's transform.
	class SPACE_API Transformable
		: public virtual ITransformable
		, public Rotatable
		, public Scalable
		, public Translatable
	{
	public:
		/// @brief Constructs an identity transform.
		Transformable();

		/// @brief Constructs a transform with an initial position.
		///
		/// @param position Initial world-space position.
		Transformable(const math::Vec3& position);

		/// @brief Destroys the transform.
		~Transformable() override;

		// Getters

		/// @brief Checks whether any transformation state has changed.
		///
		/// @return `true` if the transform has changed since the last reset;
		/// otherwise, `false`.
		bool state_changed() const override;

		/// @brief Retrieves the current model matrix.
		///
		/// @return Model transformation matrix.
		math::Mat4 get_model_matrix() override;

		// Setters

		/// @brief Sets the model matrix directly.
		///
		/// @param model_matrix New model transformation matrix.
		void set_model_matrix(const math::Mat4& model_matrix) override;

		/// @brief Recomputes the model matrix from the current translation,
		/// rotation, and scale.
		void update_model_matrix() override;

		/// @brief Resets the transform state change flags.
		void reset_state() override;

	private:
		/// @brief Indicates whether the transform state has changed.
		bool m_state_changed;

		/// @brief Cached model transformation matrix.
		math::Mat4 m_model_matrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP