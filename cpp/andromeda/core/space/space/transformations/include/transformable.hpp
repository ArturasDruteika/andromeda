#ifndef SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP
#define SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP


#include "rotatable.hpp"
#include "scalable.hpp"
#include "translatable.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"


namespace andromeda
{
	class SPACE_API Transformable
		: public virtual ITransformable
		, public Rotatable
		, public Scalable
		, public Translatable
	{
	public:
		Transformable();
		Transformable(const math::Vec3& position);
		~Transformable() override;

		// Getters
		bool state_changed() const override;
		math::Mat4 get_model_matrix() override;
		// Setters
		void set_model_matrix(const math::Mat4& model_matrix) override;

		void update_model_matrix() override;
		void reset_state() override;

	private:
		bool m_state_changed;
		math::Mat4 m_model_matrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__TRANSFORMABLE__HPP