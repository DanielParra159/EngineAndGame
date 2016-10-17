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


	void GameDescription::SetClearColor(const Color &aColor)
	{
		mClearColor = Color(aColor);
	}
	void GameDescription::SetClearColor(float32 aR, float32 aG, float32 aB, float32 aA)
	{
		mClearColor = Color(aR, aG, aB, aA);
	}
	void GameDescription::SetClearColor(uint8 aR, uint8 aG, uint8 aB, uint8 aA)
	{
		mClearColor = Color(aR, aG, aB, aA);
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