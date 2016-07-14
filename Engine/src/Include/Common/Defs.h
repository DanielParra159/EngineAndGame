#ifndef _ENGINE_CORE_DEFINES_H_
#define _ENGINE_CORE_DEFINES_H_

#define GET_RENDER_MANAGER	graphics::RendererManager* lRenderManager = graphics::RendererManager::Instance();
#define GET_APPLICATION		core::Application* lApplication = core::Application::Instance();
#define GET_TIME			sys::Time* lTime = sys::Time::Instance();
#define GET_INPUT_MANAGER	input::InputManager* lInputManager = input::InputManager::Instance();
#define GET_WORLD			logic::World *lWorld = logic::World::Instance();
#define GET_MENU_MANAGER	ui::MenuManager *lMenuManager = ui::MenuManager::Instance();
#define GET_AUDIO_MANAGER	audio::AudioManager *lAudioManager = audio::AudioManager::Instance();

#endif // _ENGINE_CORE_DEFINES_H_
