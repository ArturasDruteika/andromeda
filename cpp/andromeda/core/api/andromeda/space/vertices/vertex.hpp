#ifndef API__SPACE__VERTICES__VERTEX__HPP
#define API__SPACE__VERTICES__VERTEX__HPP


#include "../colors/colors.hpp"
#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
	struct Vertex
	{
		Math::Vec3 position;
		Color color;
		Math::Vec3 normal;

		Vertex() = default;

		Vertex(const Math::Vec3& pos, const Color& col)
			: position{ pos }
			, color{ col }
			, normal{ 0.0f, 0.0f, 0.0f }
		{
		}

		Vertex(const Math::Vec3& pos, const Color& col, const Math::Vec3& normal)
			: position{ pos }
			, color{ col }
			, normal{ normal }
		{
		}

		bool operator==(const Vertex& other) const
		{
			return position == other.position &&
				color == other.color &&
				normal == other.normal;
		}
	};
}

#endif // API__SPACE__VERTICES__VERTEX__HPP