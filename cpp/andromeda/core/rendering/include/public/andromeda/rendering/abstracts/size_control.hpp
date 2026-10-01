#pragma once


namespace andromeda::rendering
{
	/// @brief Stores renderer output dimensions.
	///
	/// Provides access to the current rendering width and height and allows
	/// resizing the render target.
	class SizeControl
	{
	public:
		/// @brief Constructs a size controller.
		///
		/// @param width Initial render width in pixels.
		/// @param height Initial render height in pixels.
		SizeControl(int width = 800, int height = 600);

		/// @brief Destroys the size controller.
		~SizeControl();

		// Getters

		/// @brief Retrieves the current render width.
		///
		/// @return Render width in pixels.
		int get_width() const;

		/// @brief Retrieves the current render height.
		///
		/// @return Render height in pixels.
		int get_height() const;

		/// @brief Updates the render dimensions.
		///
		/// @param width New render width in pixels.
		/// @param height New render height in pixels.
		void resize(int width, int height);

	protected:
		/// @brief Current render width in pixels.
		int m_width;

		/// @brief Current render height in pixels.
		int m_height;
	};
}
