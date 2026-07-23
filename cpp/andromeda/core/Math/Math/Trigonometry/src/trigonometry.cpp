#include "../include/trigonometry.hpp"
#include "../../Constants/include/constants.hpp"


namespace andromeda::math
{
	float Trigonometry::deg2_rad(float deg)
	{
		return deg * (math::PI / 180.0f);
	}

	float Trigonometry::rad2_deg(float rad)
	{
		return rad * (180.0f / math::PI);
	}
}
