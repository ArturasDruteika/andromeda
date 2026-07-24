#ifndef SPACE__TRANSFORMATIONS__SCALABLE__HPP
#define SPACE__TRANSFORMATIONS__SCALABLE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
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
		bool StateChanged() const override;
		const math::Vec3& GetScale() const override;
		const math::Mat4& GetScaleMatrix() const override;
		// Setters
		void ResetState() override;
		void SetScale(const math::Vec3& scale) override;

		void Scale(const math::Vec3& scale) override;
		void Scale(float uniformScale) override;

	protected:
		void UpdateScaleMatrix();

	private:
		bool m_stateChanged;
		math::Vec3 m_scale;
		math::Mat4 m_scaleMatrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__SCALABLE__HPP