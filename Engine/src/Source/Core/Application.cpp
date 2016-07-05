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
} // namespace core

