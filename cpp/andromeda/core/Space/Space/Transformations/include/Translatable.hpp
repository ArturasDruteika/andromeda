#ifndef SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP
#define SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
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
		bool StateChanged() const override;
		const math::Vec3& GetPosition() const override;
		const math::Mat4& GetTranslationMatrix() const override;
		// Setters
		void ResetState() override;
		void SetPosition(const math::Vec3& position) override;

		void Translate(const math::Vec3& translation) override;

	protected:
		void UpdateTranslationMatrix();

	private:
		bool m_stateChanged;
		math::Vec3 m_position;
		math::Mat4 m_translationMatrix;
	};
}


#endif // SPACE__TRANSFORMATIONS__TRANSLATABLE__HPP