#ifndef API__CAMERA__I_PERSPECTIVE_CONTROL__HPP
#define API__CAMERA__I_PERSPECTIVE_CONTROL__HPP


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
	class IPerspectiveControl
    {
    public:
        virtual ~IPerspectiveControl() = default;

		// Getters
		virtual float get_field_of_view_degrees() const = 0;
		virtual float get_near_plane() const = 0;
		virtual float get_far_plane() const = 0;
		virtual float get_aspect() const = 0;
		virtual const math::Mat4& get_projection() const = 0;
		// Setters
		virtual void set_field_of_view_degrees(float fov_deg, bool update_projection = true) = 0;
		virtual void set_near_plane(float near_plane, bool update_projection = true) = 0;
		virtual void set_far_plane(float far_plane, bool update_projection = true) = 0;
		virtual void set_aspect(float aspect, bool update_projection = true) = 0;

		// update projection matrix
		virtual void update_projection() = 0;
    };
}


#endif // API__CAMERA__I_PERSPECTIVE_CONTROL__HPP