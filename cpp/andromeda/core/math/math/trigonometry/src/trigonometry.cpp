#include "../include/trigonometry.hpp"
#include "../../constants/include/constants.hpp"


namespace andromeda::math
{
	float Trigonometry::deg_2_rad(float deg)
	{
		return deg * (math::PI / 180.0f);
	}

	float Trigonometry::rad_2_deg(float rad)
	{
		return rad * (180.0f / math::PI);
	}
}
