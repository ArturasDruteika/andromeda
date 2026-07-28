#include "../include/geometric_object.hpp"


namespace andromeda::space
{
	GeometricObject::GeometricObject() = default;

	GeometricObject::GeometricObject(const Color& color)
		: m_color{ color }
	{
	}

	GeometricObject::~GeometricObject() = default;

	const Mesh& GeometricObject::get_mesh() const
	{
		return m_mesh;
	}

	const Color& GeometricObject::get_color() const
	{
		return m_color;
	}

	void GeometricObject::set_mesh(const Mesh& mesh)
	{
		m_mesh = mesh;
	}

	void GeometricObject::set_color(const Color& color)
	{
		m_color = color;
	}
}