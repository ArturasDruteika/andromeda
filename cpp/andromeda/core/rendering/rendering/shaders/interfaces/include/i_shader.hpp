#ifndef RENDERING__SHADERS__INTERFACES__I_SHADER__HPP
#define RENDERING__SHADERS__INTERFACES__I_SHADER__HPP


namespace andromeda::rendering
{
	class IShader
	{
	public:
		virtual ~IShader();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}


#endif // RENDERING__SHADERS__INTERFACES__I_SHADER__HPP