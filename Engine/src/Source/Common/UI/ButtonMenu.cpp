#include "UI\ButtonMenu.h"

#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"

namespace ui
{
	void ButtonMenu::Init(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage)
	{
		mCallback = aCallback;
		mButtonRect.mX = aButtonRect.mX;
		mButtonRect.mY = aButtonRect.mY;
		mButtonRect.mW = aButtonRect.mW;
		mButtonRect.mH = aButtonRect.mH;
		if (aImage)
		{
			mSprite = graphics::RenderManager::Instance()->CreateSprite(aImage, graphics::eRGBA);
		}
	}

	void ButtonMenu::OnMouseClick(const Vector2D<>& aPos)
	{
		if (aPos.mX < (mButtonRect.mX + mButtonRect.mW)
			&& aPos.mX > mButtonRect.mX
			&& aPos.mY < (mButtonRect.mY + mButtonRect.mH)
			&& aPos.mY > mButtonRect.mY)
		{
			mCallback();
		}

	}

	void ButtonMenu::Render()
	{
		if (mSprite)
		{
			mSprite->PrepareToRender(&Vector3D<float32>(mButtonRect.mX, mButtonRect.mY, 0.0f),
				&Vector3D<float32>(mButtonRect.mW, mButtonRect.mH, 1.0f));
		}
	}

	void ButtonMenu::Release()
	{
		if (mSprite)
		{
			graphics::RenderManager::Instance()->DeleteSprite(mSprite);
		}
	}

} // namespace ui
