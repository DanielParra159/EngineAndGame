#ifndef _ENGINE_GRAPHICS_SCENE_H_
#define _ENGINE_GRAPHICS_SCENE_H_

#include "Types.h"

namespace graphics
{
	class IScene
	{
		friend class SceneManager;
	public:
		virtual void									Update() = 0;
		virtual void									Render() = 0;

		virtual void									Release() = 0;

		IScene(int32 aId) : mId(aId) {}

	protected:
		int32											mId;
	};

} // namespace graphics
#endif // _ENGINE_GRAPHICS_SCENE_H_
