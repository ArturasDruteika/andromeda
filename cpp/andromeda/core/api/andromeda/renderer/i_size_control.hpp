#ifndef API__RENDERER__I_SIZE__HPP
#define API__RENDERER__I_SIZE__HPP


namespace andromeda
{
	class ISizeControl
	{
	public:
		virtual ~ISizeControl() = default;

		// Getters
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;

		virtual void resize(int width, int height) = 0;
	};
}


#endif // API__RENDERER__I_SIZE__HPP