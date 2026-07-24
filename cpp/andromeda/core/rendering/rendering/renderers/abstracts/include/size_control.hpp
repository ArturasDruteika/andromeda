#ifndef RENDERING__RENDERERS__ABSTRACTS__SIZE_CONTROL__HPP
#define RENDERING__RENDERERS__ABSTRACTS__SIZE_CONTROL__HPP


namespace andromeda::rendering
{
	class SizeControl
	{
	public:
		SizeControl(int width = 800, int height = 600);
		~SizeControl();

		// Getters
		int get_width() const;
		int get_height() const;

		void resize(int width, int height);

	protected:
		int m_width;
		int m_height;
	};
}


#endif // RENDERING__RENDERERS__ABSTRACTS__SIZE_CONTROL__HPP