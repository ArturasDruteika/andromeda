#ifndef API__SPACE__TRANSFORMATIONS__I_TRANSFORMABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_TRANSFORMABLE__HPP


#include "i_rotatable.hpp"
#include "i_scalable.hpp"
#include "i_translatable.hpp"
#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace Andromeda
{
    class ITransformable
        : public virtual IRotatable
        , public virtual IScalable
        , public virtual ITranslatable
    {
    public:
        virtual ~ITransformable() = default;

        // Getters
		virtual bool state_changed() const = 0;
        virtual Math::Mat4 get_model_matrix() = 0;
		// Setters
        virtual void set_model_matrix(const Math::Mat4& model_matrix) = 0;

        virtual void update_model_matrix() = 0;
		virtual void reset_state() = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_TRANSFORMABLE__HPP