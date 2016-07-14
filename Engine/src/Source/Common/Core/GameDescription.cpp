#include "Core\GameDescription.h"

#include "Support\Color.h"

namespace core
{
	/** Assigns screen size
	@param aX width
	@param aY height
	*/
	void GameDescription::SetScreenSize(uint32 aX, uint32 aY)
	{
		mScreenSize.mX = aX;
		mScreenSize.mY = aY;
	}

	/** Assigns screen position
	@param aX X pos
	@param aY Y pos
	*/
	void GameDescription::SetScreenPosition(uint32 aX, uint32 aY)
	{
		mScreenPosition.mX = aX;
		mScreenPosition.mY = aY;
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

} // namespace core