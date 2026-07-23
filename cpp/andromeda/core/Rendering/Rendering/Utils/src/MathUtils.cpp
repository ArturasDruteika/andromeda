#include "../include/mathUtils.hpp"

namespace andromeda::Rendering
{
	glm::vec2 mathUtils::ToGLM(const math::Vec2& vec)
	{
		return glm::vec2(vec[0], vec[1]);
	}

	math::Vec2 mathUtils::FromGLM(const glm::vec2& glmVec)
	{
		return math::Vec2{ glmVec.x, glmVec.y };
	}

	glm::vec3 mathUtils::ToGLM(const math::Vec3& vec)
	{
		return glm::vec3(vec[0], vec[1], vec[2]);
	}

	math::Vec3 mathUtils::FromGLM(const glm::vec3& glmVec)
	{
		return math::Vec3{ glmVec.x, glmVec.y, glmVec.z };
	}

	glm::vec4 mathUtils::ToGLM(const math::Vec4& vec)
	{
		return glm::vec4(vec[0], vec[1], vec[2], vec[3]);
	}

	math::Vec4 mathUtils::FromGLM(const glm::vec4& glmVec)
	{
		return math::Vec4{ glmVec.x, glmVec.y, glmVec.z, glmVec.w };
	}

	glm::mat2 mathUtils::ToGLM(const math::Mat2& mat)
	{
		glm::mat2 glmMat;
		for (int col = 0; col < 2; ++col)
		{
			for (int row = 0; row < 2; ++row)
			{
				glmMat[col][row] = mat[row][col];
			}
		}
		return glmMat;
	}

	math::Mat2 mathUtils::FromGLM(const glm::mat2& glmMat)
	{
		math::Mat2 mat;
		for (int col = 0; col < 2; ++col)
		{
			for (int row = 0; row < 2; ++row)
			{
				mat[row][col] = glmMat[col][row];
			}
		}
		return mat;
	}

	glm::mat3 mathUtils::ToGLM(const math::Mat3& mat)
	{
		glm::mat3 glmMat{};
		for (int col = 0; col < 3; ++col)
		{
			for (int row = 0; row < 3; ++row)
			{
				glmMat[col][row] = mat[row][col];
			}
		}
		return glmMat;
	}

	math::Mat3 mathUtils::FromGLM(const glm::mat3& glmMat)
	{
		math::Mat3 mat;
		for (int col = 0; col < 3; ++col)
		{
			for (int row = 0; row < 3; ++row)
			{
				mat[row][col] = glmMat[col][row];
			}
		}
		return mat;
	}

	glm::mat4 mathUtils::ToGLM(const math::Mat4& mat)
	{
		glm::mat4 glmMat;
		for (int col = 0; col < 4; ++col)
		{
			for (int row = 0; row < 4; ++row)
			{
				glmMat[col][row] = mat[row][col];
			}
		}
		return glmMat;
	}

	math::Mat4 mathUtils::FromGLM(const glm::mat4& glmMat)
	{
		math::Mat4 mat;
		for (int col = 0; col < 4; ++col)
		{
			for (int row = 0; row < 4; ++row)
			{
				mat[row][col] = glmMat[col][row];
			}
		}
		return mat;
	}
}
