#ifndef API__RENDERER__I_ILLUMINATION_CONTROL__HPP
#define API__RENDERER__I_ILLUMINATION_CONTROL__HPP


namespace andromeda
{
	class IIlluminationControl
	{
	public:
		virtual ~IIlluminationControl() = default;

		// Getters
		virtual bool is_illumination_mode() const = 0;
		// Setters
		virtual void set_illumination_mode(bool mode) = 0;
	};
}


#endif // API__RENDERER__I_ILLUMINATION_CONTROL__HPP