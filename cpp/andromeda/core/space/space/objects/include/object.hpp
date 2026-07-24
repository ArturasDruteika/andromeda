#ifndef SPACE__OBJECTS__OBJECT__HPP
#define SPACE__OBJECTS__OBJECT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/objects/i_object.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    class SPACE_API Object
        : public virtual IObject
    {
    public:
        Object();
        ~Object() override;

        // Getters
        bool is_active() const override;
        int get_id() const override;
        const std::string& get_name() const override;
        // Setters
        void active(bool active) override;
        void set_name(const std::string& name) override;
        void set_id(int id) override;

    private:
        bool m_is_active;
        int m_id;
        std::string m_name;
        static std::atomic<int> s_next_id;
    };
}


#endif // SPACE__OBJECTS__OBJECT__HPP