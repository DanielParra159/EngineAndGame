#ifndef _ENGINE_CORE_DEFINES_H_
#define _ENGINE_CORE_DEFINES_H_

#define GET_RENDER_MANAGER	graphics::RendererManager* lRenderManager = graphics::RendererManager::Instance();
#define GET_APPLICATION		core::Application* lApplication = core::Application::Instance();
#define GET_TIME			sys::Time* lTime = sys::Time::Instance();

#endif // _ENGINE_CORE_DEFINES_H_
