#ifndef RENDERER__ILLUMINATION_CONTROL__HPP
#define RENDERER__ILLUMINATION_CONTROL__HPP


namespace andromeda::rendering
{
	class IlluminationControl
	{
	public:
		IlluminationControl();
		~IlluminationControl();

		// Getters
		bool is_illumination_mode() const;

		// Setters
		void set_illumination_mode(bool mode);

	protected:
		bool m_is_illumination_mode;
	};
}


#endif // RENDERER__ILLUMINATION_CONTROL__HPP