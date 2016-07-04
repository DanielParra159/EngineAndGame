#include "System\GameDescription.h"

#include "Types\Color.h"

namespace sys
{
	/// <summary>Constructor
	/// </summary>
	GameDescription::GameDescription() : mRenderDrawColor(),
		mScreenSizeX(500), mScreenSizeY(500), mScreenPositionX(50), mScreenPositionY(50),
		mFullScreen(FALSE)
	{

	}

	/// <summary>Assign screen size
	/// <param name="aX">width</param>
	/// <param name="aY">height</param>
	/// </summary>
	void GameDescription::SetScreenSize(uint32 aX, uint32 aY)
	{
		mScreenSizeX = aX;
		mScreenSizeY = aY;
	}

	/// <summary>Assign screen position
	/// <param name="aX">X pos</param>
	/// <param name="aY">Y pos</param>
	/// </summary>
	void GameDescription::SetScreenPosition(uint32 aX, uint32 aY)
	{
		mScreenPositionX = aX;
		mScreenPositionY = aY;
	}

	/// <summary>Assign draw color
	/// <param name="aColor">Color to assign</param>
	/// </summary>
	void GameDescription::SetRenderDrawColor(const Color &aColor)
	{
		mRenderDrawColor = Color(aColor);
	}

	/// <summary>Assign draw color
	/// <param name="aR">Red component to assign</param>
	/// <param name="aG">Green component to assign</param>
	/// <param name="aB">Blue component to assign</param>
	/// <param name="aA">Alpha component to assign</param>
	/// </summary>
	void GameDescription::SetRenderDrawColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA)
	{
		mRenderDrawColor = Color(aR, aG, aB, aA);
	}

	/// <summary>Start windows in full screen
	/// <param name="aFullScreen"></param>
	/// </summary>
	void GameDescription::SetFullScreen(BOOL aFullScreen)
	{
		mFullScreen = aFullScreen;
	}

} // namespace sys