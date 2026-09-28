#pragma once


namespace andromeda
{
    /// @brief Defines the interface for controlling renderer illumination mode.
    ///
    /// This interface provides access to the renderer's illumination state,
    /// allowing lighting calculations to be enabled or disabled.
    class IIlluminationControl
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IIlluminationControl() = default;

        // Getters

        /// @brief Checks whether illumination mode is enabled.
        ///
        /// @return `true` if illumination mode is enabled; otherwise, `false`.
        virtual bool is_illumination_mode() const = 0;

        // Setters

        /// @brief Enables or disables illumination mode.
        ///
        /// @param mode `true` to enable illumination mode; `false` to disable it.
        virtual void set_illumination_mode(bool mode) = 0;
    };
}
