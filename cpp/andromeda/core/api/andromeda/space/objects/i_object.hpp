#ifndef API__OBJECTS__I_OBJECT__HPP
#define API__OBJECTS__I_OBJECT__HPP


#include <string>


namespace andromeda
{
    /// @brief Defines the common interface for all scene objects.
    ///
    /// Provides basic object properties such as an identifier, name, and
    /// active state.
    class IObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IObject() = default;

        // Getters

        /// @brief Checks whether the object is active.
        ///
        /// @return `true` if the object is active; otherwise, `false`.
        virtual bool is_active() const = 0;

        /// @brief Retrieves the object identifier.
        ///
        /// @return Unique object identifier.
        virtual int get_id() const = 0;

        /// @brief Retrieves the object name.
        ///
        /// @return Reference to the object name.
        virtual const std::string& get_name() const = 0;

        // Setters

        /// @brief Sets the object's active state.
        ///
        /// @param active `true` to activate the object; `false` to deactivate it.
        virtual void active(bool active) = 0;

        /// @brief Sets the object name.
        ///
        /// @param name Object name.
        virtual void set_name(const std::string& name) = 0;

        /// @brief Sets the object identifier.
        ///
        /// @param id Unique object identifier.
        virtual void set_id(int id) = 0;
    };
}


#endif // API__OBJECTS__I_OBJECT__HPP