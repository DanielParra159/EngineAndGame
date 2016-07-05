#ifndef _ENGINE_CORE_APPLICATION_H_
#define _ENGINE_CORE_APPLICATION_H_

#include "Types.h"
#include "Types\Vector2D.h"

struct SDL_Window;

namespace core
{
	class Application
	{
	private:
		static Application*								sInstance;
	public:
		static Application*								Instance();

		BOOL											Init();
		void											Release();

		BOOL											HandleEvents();
	private:
		Application() {}
		~Application() {}
	};

} // namespace core
#endif // _ENGINE_CORE_APPLICATION_H_
