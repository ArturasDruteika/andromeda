#ifndef API__OBJECTS__I_OBJECT__HPP
#define API__OBJECTS__I_OBJECT__HPP


#include <string>


namespace andromeda
{
	class IObject
	{
	public:
		virtual ~IObject() = default;
		
		// Getters
		virtual bool is_active() const = 0;
		virtual int get_id() const = 0;
        virtual const std::string& get_name() const = 0;
        // Setters
		virtual void active(bool active) = 0;
        virtual void set_name(const std::string& name) = 0;
		virtual void set_id(int id) = 0;
	};
}


#endif // API__OBJECTS__I_OBJECT__HPP