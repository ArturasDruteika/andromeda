#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_scalable.hpp"


namespace andromeda
{
	/// @brief Provides scaling functionality for transformable objects.
	///
	/// Stores the current scale and its corresponding transformation matrix while
	/// tracking whether the scaling state has changed.
	class SPACE_API Scalable
		: public virtual IScalable
	{
	public:
		/// @brief Constructs a scalable object.
		Scalable();

		/// @brief Destroys the scalable object.
		~Scalable() override;

		// Getters

		/// @brief Checks whether the scale state has changed.
		///
		/// @return `true` if the scale has changed since the last reset;
		/// otherwise, `false`.
		bool state_changed() const override;

		/// @brief Retrieves the current scale.
		///
		/// @return Scale factors along each axis.
		const math::Vec3& get_scale() const override;

		/// @brief Retrieves the scale transformation matrix.
		///
		/// @return Scale matrix corresponding to the current scale.
		const math::Mat4& get_scale_matrix() const override;

		// Setters

		/// @brief Resets the scale state change flag.
		void reset_state() override;

		/// @brief Sets the scale.
		///
		/// @param scale New scale factors along each axis.
		void set_scale(const math::Vec3& scale) override;

		/// @brief Applies a non-uniform scaling operation.
		///
		/// @param scale Scale factors to apply.
		void scale(const math::Vec3& scale) override;

		/// @brief Applies a uniform scaling operation.
		///
		/// @param uniform_scale Uniform scale factor.
		void scale(float uniform_scale) override;

	protected:
		/// @brief Updates the cached scale matrix.
		void update_scale_matrix();

	private:
		/// @brief Indicates whether the scale state has changed.
		bool m_state_changed;

		/// @brief Current scale factors.
		math::Vec3 m_scale;

		/// @brief Cached scale transformation matrix.
		math::Mat4 m_scale_matrix;
	};
}
