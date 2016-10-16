#include "Core\GameDescription.h"

#include "Support\Color.h"

namespace core
{

	void GameDescription::SetScreenSize(uint32 aX, uint32 aY)
	{
		mScreenSize.mX = aX;
		mScreenSize.mY = aY;
	}

	void GameDescription::SetScreenPosition(uint32 aX, uint32 aY)
	{
		mScreenPosition.mX = aX;
		mScreenPosition.mY = aY;
	}


	void GameDescription::SetRenderDrawColor(const Color &aColor)
	{
		mRenderDrawColor = Color(aColor);
	}

	void GameDescription::SetRenderDrawColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA)
	{
		mRenderDrawColor = Color(aR, aG, aB, aA);
	}

	void GameDescription::SetFullScreen(BOOL aFullScreen)
	{
		mFullScreen = aFullScreen;
	}

	void GameDescription::SetRootDir(const std::string& aDirectory)
	{
		mRootDir = aDirectory;
	}

	void GameDescription::SetPhysicsGravity(float32 aPhysicsGravity)
	{
		mPhysicsGravity = aPhysicsGravity;
	}

} // namespace core