#ifndef _CORE_GAMESDESCRIPTION_H_
#define _CORE_GAMESDESCRIPTION_H_

#include "Types.h"
#include "Types\Color.h"
#include "Types\Vector2D.h"

namespace core
{
	class GameDescription {
	friend class Game;
	public:
		GameDescription() : mScreenSize(500,500), mScreenPosition(50,50), mRenderDrawColor(), mFullScreen(FALSE) {}
		void SetScreenSize(uint32 aX, uint32 aY);
		void SetScreenPosition(uint32 aX, uint32 aY);
		void SetRenderDrawColor(const Color &aColor);
		void SetRenderDrawColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA);
		void SetFullScreen(BOOL aFullScreen);

	protected:
		Vector2D<uint32> mScreenSize;
		Vector2D<uint32> mScreenPosition;
		Color mRenderDrawColor;
		BOOL mFullScreen;
			
	}; // GameDescription
} // namespace core
#endif // _CORE_GAMESDESCRIPTION_H_
