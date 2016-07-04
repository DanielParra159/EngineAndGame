#ifndef _ENGINE_CORE_DEFINES_H_
#define _ENGINE_CORE_DEFINES_H_

#define VC_EXTRALEAN  // tells windows not include unnecessary stuff
#define _CRT_SECURE_NO_WARNINGS

#define GET_TEXTURE_MANAGER	TextureManager* lTextureManager = TextureManager::Instance();
#define GET_RENDER_MANAGER	RendererManager* lRenderManager = RendererManager::Instance();


#endif // _ENGINE_CORE_DEFINES_H_
