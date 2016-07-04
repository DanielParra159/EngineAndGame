#ifndef _ENGINE_GRAPHICS_MATRIXSCENE_H_
#define _ENGINE_GRAPHICS_MATRIXSCENE_H_

#include "Graphics\Scene.h"
#include "Types.h"

namespace graphics
{
	class SceneCell;
	class AnimateSprite;

	class MatrixScene : public IScene
	{
		friend class SceneManager;
	private:
		uint32											mWidth;
		uint32											mHeight;
		SceneCell**										mSceneCells;

		const uint32									mSpriteCellTypes = 4;
		AnimateSprite**									mSpriteCells;

	public:
		virtual void									Init(uint32 aWidth, uint32 aHeight);
		virtual void									Release();

		virtual void									Update();
		virtual void									Render();

		uint32											GetWith();
		uint32											GetHeight();
	private:
		MatrixScene(int32 aId);
		~MatrixScene() {}

	};

} // namespace graphics
#endif // _ENGINE_GRAPHICS_MATRIXSCENE_H_
