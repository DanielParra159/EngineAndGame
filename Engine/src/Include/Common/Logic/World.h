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

		const uint32									mSpriteCellTypes = 6;
		graphics::Sprite**								mSpriteCells;

	public:
		static World*									Instance();
		virtual void									Init(uint32 aWidth, uint32 aHeight);
		virtual void									Release();

		virtual void									Update();
		virtual void									Render();

		uint32											GetWith() const { return mWidth; }
		uint32											GetHeight() const { return mHeight; }
		const WorldCell*								GetCell(uint32 aX, uint32 aY) { return mWorldCells[(aY*mWidth) + aX]; }
		void											SetCell(uint32 aX, uint32 aY, float32 aLife);
		void											SetCell(uint32 aX, uint32 aY, uint32 aType);
		void											SetCell(uint32 aX, uint32 aY, float32 aLife, uint32 aType);
		void											SetCellAngle(uint32 aX, uint32 aY, float64 aAngle);
	private:
		World() {}
		~World() {}

	}; // World

} // namespace logic
#endif // _ENGINE_LOGIC_MATRIXSCENE_H_
