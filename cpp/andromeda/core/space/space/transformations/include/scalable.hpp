#ifndef SPACE__TRANSFORMATIONS__SCALABLE__HPP
#define SPACE__TRANSFORMATIONS__SCALABLE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_scalable.hpp"


namespace andromeda
{
	class SPACE_API Scalable
		: public virtual IScalable
	{
	public:
		Scalable();
		~Scalable() override;

		// Getters
		bool state_changed() const override;
		const math::Vec3& get_scale() const override;
		const math::Mat4& get_scale_matrix() const override;
		// Setters
		void reset_state() override;
		void set_scale(const math::Vec3& scale) override;

		void scale(const math::Vec3& scale) override;
		void scale(float uniform_scale) override;

	protected:
		void update_scale_matrix();

	private:
		bool m_state_changed;
		math::Vec3 m_scale;
		math::Mat4 m_scale_matrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__SCALABLE__HPP