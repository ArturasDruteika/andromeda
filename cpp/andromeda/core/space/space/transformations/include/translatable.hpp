#ifndef SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP
#define SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_translatable.hpp"


namespace andromeda
{
	/// @brief Provides translation functionality for transformable objects.
	///
	/// Stores the object's position and corresponding translation matrix while
	/// tracking whether the translation state has changed.
	class SPACE_API Translatable
		: public virtual ITranslatable
	{
	public:
		/// @brief Constructs a translatable object at the origin.
		Translatable();

		/// @brief Constructs a translatable object with an initial position.
		///
		/// @param position Initial world-space position.
		Translatable(const math::Vec3& position);

		/// @brief Destroys the translatable object.
		~Translatable() override;

		// Getters

		/// @brief Checks whether the translation state has changed.
		///
		/// @return `true` if the position has changed since the last reset;
		/// otherwise, `false`.
		bool state_changed() const override;

		/// @brief Retrieves the current position.
		///
		/// @return Current world-space position.
		const math::Vec3& get_position() const override;

		/// @brief Retrieves the translation matrix.
		///
		/// @return Translation matrix corresponding to the current position.
		const math::Mat4& get_translation_matrix() const override;

		// Setters

		/// @brief Resets the translation state change flag.
		void reset_state() override;

		/// @brief Sets the object position.
		///
		/// @param position New world-space position.
		void set_position(const math::Vec3& position) override;

		/// @brief Applies a translation to the current position.
		///
		/// @param translation Translation offset.
		void translate(const math::Vec3& translation) override;

	protected:
		/// @brief Updates the cached translation matrix.
		void update_translation_matrix();

	private:
		/// @brief Indicates whether the translation state has changed.
		bool m_state_changed;

		/// @brief Current world-space position.
		math::Vec3 m_position;

		/// @brief Cached translation matrix.
		math::Mat4 m_translation_matrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP