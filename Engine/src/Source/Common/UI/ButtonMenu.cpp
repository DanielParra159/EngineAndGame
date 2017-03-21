#include "UI\ButtonMenu.h"

#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"

namespace ui
{
	void ButtonMenu::Init(const Rect<int32>& aPositionRect, const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage)
	{
		mCallback = aCallback;
		mButtonImageRect.mX = aButtonRect.mX;
		mButtonImageRect.mY = aButtonRect.mY;
		mButtonImageRect.mW = aButtonRect.mW;
		mButtonImageRect.mH = aButtonRect.mH;
		mPositionRect.mX = aPositionRect.mX;
		mPositionRect.mY = aPositionRect.mY;
		mPositionRect.mW = aPositionRect.mW;
		mPositionRect.mH = aPositionRect.mH;
		if (aImage)
		{
			mImage = graphics::RenderManager::Instance()->CreateSprite(aImage, graphics::eRGBA);
		}
	}

	void ButtonMenu::OnMouseClick(const Vector2D<>& aPos)
	{
		if (aPos.mX < (mPositionRect.mX + mPositionRect.mW)
			&& aPos.mX > mPositionRect.mX
			&& aPos.mY < (mPositionRect.mY + mPositionRect.mH)
			&& aPos.mY > mPositionRect.mY)
			{
				mCallback();
			}
		
	}

	void ButtonMenu::Render()
	{
		//if (mImage)
		//	mImage->Render(EXPOSE_RECT(mPositionRect));
	}

	void ButtonMenu::Release()
	{
		if (mImage)
		{
			graphics::RenderManager::Instance()->DeleteSprite(mImage);
		}
	}

} // namespace ui
