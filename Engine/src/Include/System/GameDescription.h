#ifndef _SYS_GAMESDESCRIPTION_H_
#define _SYS_GAMESDESCRIPTION_H_

#include "Types.h"
#include "Core\Color.h"

namespace sys
{
	class GameDescription {
	friend class Game;
	public:
		GameDescription();
		void SetScreenSize(uint32 aX, uint32 aY);
		void SetScreenPosition(uint32 aX, uint32 aY);
		void SetRenderDrawColor(const core::Color &aColor);
		void SetRenderDrawColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA);
		void SetFullScreen(BOOL aFullScreen);

	protected:
		uint32 mScreenSizeX, mScreenSizeY;
		uint32 mScreenPositionX, mScreenPositionY;
		core::Color mRenderDrawColor;
		BOOL mFullScreen;
			
	}; // GameDescription
} // namespace sys
#endif // _SYS_GAMESDESCRIPTION_H_
