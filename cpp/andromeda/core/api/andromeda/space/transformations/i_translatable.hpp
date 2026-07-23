#ifndef API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP


#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    class ITranslatable
    {
    public:
        virtual ~ITranslatable() = default;

        // Getters
        virtual bool state_changed() const = 0;
        virtual const Math::Vec3& get_position() const = 0;
		virtual const Math::Mat4& get_translation_matrix() const = 0;
        // Setters
        virtual void reset_state() = 0;
        virtual void set_position(const Math::Vec3& position) = 0;

        virtual void translate(const Math::Vec3& translation) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP