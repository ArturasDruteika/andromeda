#include "../include/sphere.hpp"
#include "math/constants/include/constants.hpp"
#include "pch.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::space
{
	Sphere::Sphere(float radius, const Color& color)
		: GeometricObject{ color }
		, m_radius{ radius }
	{
        construct_sphere(m_radius, 36, 18, color);
	}

	Sphere::~Sphere()
	{
	}

	float Sphere::get_radius() const
	{
		return m_radius;
	}

	void Sphere::set_radius(float radius)
	{
        if (radius <= 0.0f)
        {
            spdlog::error("Sphere radius must be greater than zero. Given radius: {}", radius);
            return;
        }

        m_radius = radius;
        construct_sphere(m_radius, 36, 18, m_color);
	}

    void Sphere::construct_sphere(float radius, int sector_count, int stack_count, const Color& color)
    {
        validate_sphere_params(sector_count, stack_count);

        if (radius <= 0.0f)
        {
			spdlog::error("Sphere radius must be greater than zero. Given radius: {}", radius);
            return;
        }

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        vertices.reserve(static_cast<size_t>((stack_count + 1) * (sector_count + 1)));
        indices.reserve(static_cast<size_t>(stack_count * sector_count * 6));

        generate_sphere_vertices(radius, sector_count, stack_count, color, vertices);
        generate_sphere_indices(sector_count, stack_count, indices);

        Mesh mesh;
        mesh.set_data(vertices, indices);

        set_mesh(mesh);
    }

    void Sphere::validate_sphere_params(int& sector_count, int& stack_count) const
    {
        if (sector_count < 3)
        {
            sector_count = 3;
        }

        if (stack_count < 2)
        {
            stack_count = 2;
        }
    }

    void Sphere::generate_sphere_vertices(
        float radius,
        int sector_count,
        int stack_count,
        const Color& color,
        std::vector<Vertex>& out_vertices
    ) const
    {
        const float sector_step = 2.0f * math::PI / static_cast<float>(sector_count);
        const float stack_step = math::PI / static_cast<float>(stack_count);

        for (int i = 0; i <= stack_count; ++i)
        {
            const float stack_angle = (math::PI / 2.0f) - (static_cast<float>(i) * stack_step);
            const float xy = radius * std::cos(stack_angle);
            const float z = radius * std::sin(stack_angle);

            for (int j = 0; j <= sector_count; ++j)
            {
                const float sector_angle = static_cast<float>(j) * sector_step;

                const float x = xy * std::cos(sector_angle);
                const float y = xy * std::sin(sector_angle);

                const math::Vec3 normal = compute_sphere_normal(x, y, z);

                out_vertices.emplace_back(
                    math::Vec3(x, y, z),
                    color,
                    normal
                );
            }
        }
    }

    void Sphere::generate_sphere_indices(
        int sector_count,
        int stack_count,
        std::vector<unsigned int>& out_indices
    ) const
    {
        for (int i = 0; i < stack_count; ++i)
        {
            int k1 = i * (sector_count + 1);
            int k2 = k1 + (sector_count + 1);

            for (int j = 0; j < sector_count; ++j, ++k1, ++k2)
            {
                if (i != 0)
                {
                    out_indices.push_back(static_cast<unsigned int>(k1));
                    out_indices.push_back(static_cast<unsigned int>(k2));
                    out_indices.push_back(static_cast<unsigned int>(k1 + 1));
                }

                if (i != (stack_count - 1))
                {
                    out_indices.push_back(static_cast<unsigned int>(k1 + 1));
                    out_indices.push_back(static_cast<unsigned int>(k2));
                    out_indices.push_back(static_cast<unsigned int>(k2 + 1));
                }
            }
        }
    }

    math::Vec3 Sphere::compute_sphere_normal(float x, float y, float z)
    {
        const float len_sq = (x * x) + (y * y) + (z * z);

        if (len_sq <= 0.0f)
        {
            return math::Vec3(0.0f, 0.0f, 0.0f);
        }

        const float inv_len = 1.0f / std::sqrt(len_sq);
        return math::Vec3(x * inv_len, y * inv_len, z * inv_len);
    }
}