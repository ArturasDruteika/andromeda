#include "../include/object.hpp"


namespace andromeda::space
{
	std::atomic<int> Object::s_next_id{ 0 };

	Object::Object()
		: m_is_active{ false }
		, m_id{ s_next_id++ }
		, m_name{}
	{
	}

	Object::~Object() = default;

	bool Object::is_active() const
	{
		return m_is_active;
	}

	int Object::get_id() const
	{
		return m_id;
	}

	const std::string& Object::get_name() const
	{
		return m_name;
	}

	void Object::active(bool active)
	{
		m_is_active = active;
	}

	void Object::set_name(const std::string& name)
	{
		m_name = name;
	}

	void Object::set_id(int id)
	{
		m_id = id;
	}
}