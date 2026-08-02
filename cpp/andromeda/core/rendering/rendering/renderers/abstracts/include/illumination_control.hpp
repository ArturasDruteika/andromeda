#pragma once


namespace andromeda::rendering
{
	/// @brief Controls renderer illumination mode.
	///
	/// Stores whether illumination (lighting) is enabled during rendering.
	class IlluminationControl
	{
	public:
		/// @brief Constructs an illumination controller.
		IlluminationControl();

		/// @brief Destroys the illumination controller.
		~IlluminationControl();

		// Getters

		/// @brief Checks whether illumination mode is enabled.
		///
		/// @return `true` if illumination mode is enabled; otherwise, `false`.
		bool is_illumination_mode() const;

		// Setters

		/// @brief Enables or disables illumination mode.
		///
		/// @param mode `true` to enable illumination mode; otherwise, `false`.
		void set_illumination_mode(bool mode);

	protected:
		/// @brief Indicates whether illumination mode is enabled.
		bool m_is_illumination_mode;
	};
}
