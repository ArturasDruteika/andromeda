// Myliu savo spoonchik spoonchik


#ifndef MATH__TRIGONOMETRY__HPP
#define MATH__TRIGONOMETRY__HPP


#include "../../macro_exports/include/macro_exports.hpp"


namespace andromeda::math
{
	/// @brief Provides common trigonometric conversion functions.
	///
	/// Contains utility functions for converting angles between degrees
	/// and radians.
	class MATH_API Trigonometry
	{
	public:
		/// @brief Converts an angle from degrees to radians.
		///
		/// @param deg Angle in degrees.
		/// @return Equivalent angle in radians.
		static float deg_2_rad(float deg);

		/// @brief Converts an angle from radians to degrees.
		///
		/// @param rad Angle in radians.
		/// @return Equivalent angle in degrees.
		static float rad_2_deg(float rad);
	};
}


#endif // MATH__TRIGONOMETRY__HPP