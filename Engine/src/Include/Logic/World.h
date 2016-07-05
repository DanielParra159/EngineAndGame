#ifndef _ENGINE_LOGIC_MATRIXSCENE_H_
#define _ENGINE_LOGIC_MATRIXSCENE_H_

#include "Types.h"

namespace graphics
{
	class Sprite;
}

namespace logic
{
	class WorldCell;

	class World
	{
	private:
		static World*									sInstance;

		uint32											mWidth;
		uint32											mHeight;
		WorldCell**										mWorldCells;

		const uint32									mSpriteCellTypes = 1;
		graphics::Sprite**								mSpriteCells;

	public:
		static World*									Instance();
		virtual void									Init(uint32 aWidth, uint32 aHeight);
		virtual void									Release();

		virtual void									Update();
		virtual void									Render();

		uint32											GetWith() { return mWidth; }
		uint32											GetHeight() { return mHeight; }
	private:
		World() {}
		~World() {}

	}; // World

} // namespace logic
#endif // _ENGINE_LOGIC_MATRIXSCENE_H_
