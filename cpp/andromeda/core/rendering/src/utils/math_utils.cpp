#include "../include/math_utils.hpp"


namespace andromeda::rendering
{
	glm::vec2 MathUtils::to_glm(const math::Vec2& vec)
	{
		return glm::vec2(vec[0], vec[1]);
	}

	math::Vec2 MathUtils::from_glm(const glm::vec2& glm_vec)
	{
		return math::Vec2{ glm_vec.x, glm_vec.y };
	}

	glm::vec3 MathUtils::to_glm(const math::Vec3& vec)
	{
		return glm::vec3(vec[0], vec[1], vec[2]);
	}

	math::Vec3 MathUtils::from_glm(const glm::vec3& glm_vec)
	{
		return math::Vec3{ glm_vec.x, glm_vec.y, glm_vec.z };
	}

	glm::vec4 MathUtils::to_glm(const math::Vec4& vec)
	{
		return glm::vec4(vec[0], vec[1], vec[2], vec[3]);
	}

	math::Vec4 MathUtils::from_glm(const glm::vec4& glm_vec)
	{
		return math::Vec4{ glm_vec.x, glm_vec.y, glm_vec.z, glm_vec.w };
	}

	glm::mat2 MathUtils::to_glm(const math::Mat2& mat)
	{
		glm::mat2 glm_mat;
		for (int col = 0; col < 2; ++col)
		{
			for (int row = 0; row < 2; ++row)
			{
				glm_mat[col][row] = mat[row][col];
			}
		}
		return glm_mat;
	}

	math::Mat2 MathUtils::from_glm(const glm::mat2& glm_mat)
	{
		math::Mat2 mat;
		for (int col = 0; col < 2; ++col)
		{
			for (int row = 0; row < 2; ++row)
			{
				mat[row][col] = glm_mat[col][row];
			}
		}
		return mat;
	}

	glm::mat3 MathUtils::to_glm(const math::Mat3& mat)
	{
		glm::mat3 glm_mat{};
		for (int col = 0; col < 3; ++col)
		{
			for (int row = 0; row < 3; ++row)
			{
				glm_mat[col][row] = mat[row][col];
			}
		}
		return glm_mat;
	}

	math::Mat3 MathUtils::from_glm(const glm::mat3& glm_mat)
	{
		math::Mat3 mat;
		for (int col = 0; col < 3; ++col)
		{
			for (int row = 0; row < 3; ++row)
			{
				mat[row][col] = glm_mat[col][row];
			}
		}
		return mat;
	}

	glm::mat4 MathUtils::to_glm(const math::Mat4& mat)
	{
		glm::mat4 glm_mat;
		for (int col = 0; col < 4; ++col)
		{
			for (int row = 0; row < 4; ++row)
			{
				glm_mat[col][row] = mat[row][col];
			}
		}
		return glm_mat;
	}

	math::Mat4 MathUtils::from_glm(const glm::mat4& glm_mat)
	{
		math::Mat4 mat;
		for (int col = 0; col < 4; ++col)
		{
			for (int row = 0; row < 4; ++row)
			{
				mat[row][col] = glm_mat[col][row];
			}
		}
		return mat;
	}
}