#include "System\GameDescription.h"

#include "Types\Color.h"

namespace sys
{
	/**Constructor
	*/
	GameDescription::GameDescription() : mRenderDrawColor(),
		mScreenSizeX(500), mScreenSizeY(500), mScreenPositionX(50), mScreenPositionY(50),
		mFullScreen(FALSE)
	{

	}

	/** Assigns screen size
	@param aX width
	@param aY height
	*/
	void GameDescription::SetScreenSize(uint32 aX, uint32 aY)
	{
		mScreenSizeX = aX;
		mScreenSizeY = aY;
	}

	/** Assigns screen position
	@param aX X pos
	@param aY Y pos
	*/
	void GameDescription::SetScreenPosition(uint32 aX, uint32 aY)
	{
		mScreenPositionX = aX;
		mScreenPositionY = aY;
	}

	/** Assigns draw color
	@param aColor Color to assign
	*/
	void GameDescription::SetRenderDrawColor(const Color &aColor)
	{
		mRenderDrawColor = Color(aColor);
	}

	/** Assigns draw color
	@param aR Red component to assign
	@param aG Green component to assign
	@param aB Blue component to assign
	@param aA Alpha component to assign
	*/
	void GameDescription::SetRenderDrawColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA)
	{
		mRenderDrawColor = Color(aR, aG, aB, aA);
	}

	/** Start windows in full screen
	@param aFullScreen
	*/
	void GameDescription::SetFullScreen(BOOL aFullScreen)
	{
		mFullScreen = aFullScreen;
	}

} // namespace sys