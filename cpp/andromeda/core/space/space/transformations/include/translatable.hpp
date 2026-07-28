#ifndef SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP
#define SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_translatable.hpp"


namespace andromeda
{
	class SPACE_API Translatable
		: public virtual ITranslatable
	{
	public:
		Translatable();
		Translatable(const math::Vec3& position);
		~Translatable() override;

		// Getters
		bool state_changed() const override;
		const math::Vec3& get_position() const override;
		const math::Mat4& get_translation_matrix() const override;
		// Setters
		void reset_state() override;
		void set_position(const math::Vec3& position) override;

		void translate(const math::Vec3& translation) override;

	protected:
		void update_translation_matrix();

	private:
		bool m_state_changed;
		math::Vec3 m_position;
		math::Mat4 m_translation_matrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP