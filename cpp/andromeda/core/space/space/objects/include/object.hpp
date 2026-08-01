#ifndef SPACE__OBJECTS__OBJECT__HPP
#define SPACE__OBJECTS__OBJECT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/objects/i_object.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    /// @brief Base class for all scene objects.
    ///
    /// Provides common object properties including a unique identifier, name,
    /// and active state.
    class SPACE_API Object
        : public virtual IObject
    {
    public:
        /// @brief Constructs an object.
        Object();

        /// @brief Destroys the object.
        ~Object() override;

        // Getters

        /// @brief Checks whether the object is active.
        ///
        /// @return `true` if the object is active; otherwise, `false`.
        bool is_active() const override;

        /// @brief Retrieves the object's unique identifier.
        ///
        /// @return Object identifier.
        int get_id() const override;

        /// @brief Retrieves the object's name.
        ///
        /// @return Object name.
        const std::string& get_name() const override;

        // Setters

        /// @brief Sets whether the object is active.
        ///
        /// @param active `true` to activate the object; otherwise, `false`.
        void active(bool active) override;

        /// @brief Sets the object's name.
        ///
        /// @param name New object name.
        void set_name(const std::string& name) override;

        /// @brief Sets the object's identifier.
        ///
        /// @param id New object identifier.
        void set_id(int id) override;

    private:
        /// @brief Indicates whether the object is active.
        bool m_is_active;

        /// @brief Unique identifier of the object.
        int m_id;

        /// @brief Human-readable object name.
        std::string m_name;

        /// @brief Counter used to generate unique object identifiers.
        static std::atomic<int> s_next_id;
    };
}


#endif // SPACE__OBJECTS__OBJECT__HPP