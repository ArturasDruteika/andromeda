#ifndef API__SCENE__I_UPDATE_HOOKS__HPP
#define API__SCENE__I_UPDATE_HOOKS__HPP


#include <cstdint>
#include <functional>


namespace Andromeda
{
	class IUpdateHooks
	{
	public:
		using Callback = std::function<void(float)>;

		struct Handle
		{
			std::uint64_t id = 0;
		};

	public:
		virtual ~IUpdateHooks() = default;

		virtual Handle add(Callback callback) = 0;
		virtual void remove(Handle handle) = 0;
		virtual void clear() = 0;
		virtual void run(float delta_time) = 0;
	};
}


#endif // API__SCENE__I_UPDATE_HOOKS__HPP