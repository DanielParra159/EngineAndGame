#include "Core\Application.h"

#include <SDL.h>

namespace core
{
	Application* Application::sInstance = 0;

	Application* Application::Instance()
	{
		if (Application::sInstance == 0)
		{
			Application::sInstance = new Application();
			return Application::sInstance;
		}
		return Application::sInstance;
	}

	BOOL Application::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			return FALSE;
		return TRUE;
	}

	void Application::Release()
	{
		SDL_Quit();
	}

	BOOL Application::HandleEvents()
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					return FALSE;
					break;
				default:
					break;
			}
		}
		return TRUE;
	}
} // namespace core

