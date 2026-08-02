#pragma once


namespace andromeda::Space
{
	/// @brief Represents a point in two-dimensional space.
	struct Point2D
	{
		/// @brief X-coordinate.
		float x;

		/// @brief Y-coordinate.
		float y;

		/// @brief Constructs a point at the origin.
		Point2D() : x(0.0f), y(0.0f) {}

		/// @brief Constructs a point with the specified coordinates.
		///
		/// @param x X-coordinate.
		/// @param y Y-coordinate.
		Point2D(float x, float y) : x(x), y(y) {}

		/// @brief Compares two points for equality.
		///
		/// @param other Point to compare against.
		/// @return `true` if both coordinates are equal; otherwise, `false`.
		bool operator==(const Point2D& other) const
		{
			return x == other.x && y == other.y;
		}

		/// @brief Retrieves the number of floating-point components.
		///
		/// @return Number of float components in the point.
		static constexpr int Size()
		{
			return sizeof(Point2D) / sizeof(float);
		}
	};

	/// @brief Represents a point in three-dimensional space.
	struct Point3D
	{
		/// @brief X-coordinate.
		float x;

		/// @brief Y-coordinate.
		float y;

		/// @brief Z-coordinate.
		float z;

		/// @brief Constructs a point at the origin.
		Point3D() : x(0.0f), y(0.0f), z(0.0f) {}

		/// @brief Constructs a point with the specified coordinates.
		///
		/// @param x X-coordinate.
		/// @param y Y-coordinate.
		/// @param z Z-coordinate.
		Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

		/// @brief Compares two points for equality.
		///
		/// @param other Point to compare against.
		/// @return `true` if all coordinates are equal; otherwise, `false`.
		bool operator==(const Point3D& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		/// @brief Retrieves the number of floating-point components.
		///
		/// @return Number of float components in the point.
		static constexpr int Size()
		{
			return sizeof(Point3D) / sizeof(float);
		}
	};
}
