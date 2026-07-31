#ifndef RENDERING__SHADERS__INTERFACES__I_SHADER__HPP
#define RENDERING__SHADERS__INTERFACES__I_SHADER__HPP


namespace andromeda::rendering
{
	/// @brief Defines the interface for a shader.
	///
	/// Provides operations for binding and unbinding a shader during rendering.
	class IShader
	{
	public:
		/// @brief Virtual destructor.
		virtual ~IShader();

		/// @brief Binds the shader.
		virtual void bind() const = 0;

		/// @brief Unbinds the shader.
		virtual void unbind() const = 0;
	};
}


#endif // RENDERING__SHADERS__INTERFACES__I_SHADER__HPP