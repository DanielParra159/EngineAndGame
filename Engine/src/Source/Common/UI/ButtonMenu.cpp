#include "UI\ButtonMenu.h"

#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"
#include "Graphics\Material.h"

#include "Support/Color.h"

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
			graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("SpriteUnlit");
			lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture(aImage, graphics::eRGBA));
			mSprite->SetMaterial(lMaterial);
		}
	}

	void ButtonMenu::OnMouseClick(const Vector2D<>& aPos)
	{
		if (aPos.mX < (mButtonRect.mX + mButtonRect.mW * 0.5f)
			&& aPos.mX > mButtonRect.mX - mButtonRect.mW * 0.5f
			&& aPos.mY < (mButtonRect.mY + mButtonRect.mH * 0.5f)
			&& aPos.mY > mButtonRect.mY - mButtonRect.mH * 0.5f)
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
