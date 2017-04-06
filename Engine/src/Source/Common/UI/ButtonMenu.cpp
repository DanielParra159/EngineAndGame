#include "UI/ButtonMenu.h"

#include "Graphics/Sprite.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Material.h"
#include "Graphics/TextRenderer.h"

#include "Support/Color.h"

namespace ui
{
	void ButtonMenu::Init(const Rect<int32>& aButtonRect, CallbackFunction aCallback)
	{
		if (mCallback == NULL) {
			mCallback = aCallback;
			mButtonRect.mX = aButtonRect.mX;
			mButtonRect.mY = aButtonRect.mY;
			mButtonRect.mW = aButtonRect.mW;
			mButtonRect.mH = aButtonRect.mH;
		}
	}

	void ButtonMenu::Init(const Rect<int32>& aButtonRect, CallbackFunction aCallback, float32 aTextScale, const Color32& aTextColor, const std::string& aText, const char* aImage)
	{
		Init(aButtonRect, aCallback);
		if (aImage)
		{
			InitWithImage(aButtonRect, aCallback, aImage);
		}
		if (aText.size() > 0) 
		{
			InitWithText(aButtonRect, aCallback, aText, aTextScale, aTextColor);
		}
	}

	void ButtonMenu::InitWithImage(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const char* aImage)
	{
		Init(aButtonRect, aCallback);

		mSprite = graphics::RenderManager::Instance()->CreateSprite(aImage, graphics::eRGBA);
		graphics::Material* lMaterial = graphics::RenderManager::Instance()->LoadMaterial("SpriteUnlit");
		lMaterial->SetDiffuseTexture(graphics::RenderManager::Instance()->LoadTexture(aImage, graphics::eRGBA));
		mSprite->SetMaterial(lMaterial);
		mSprite->SetUseUICamera(TRUE);
	}

	void ButtonMenu::InitWithText(const Rect<int32>& aButtonRect, CallbackFunction aCallback, const std::string& aText, float32 aScale, const Color32& aColor)
	{
		Init(aButtonRect, aCallback);

		mTextRenderer = graphics::RenderManager::Instance()->LoadTextRenderer("PerfectPixel.ttf", 24);
		mTextScale = aScale;
		mTextColor = aColor;
		mText = aText;
	}

	void ButtonMenu::OnMouseClick()
	{
		mCallback();
	}
	void ButtonMenu::OnFocusEnter(const Vector2D<>& aPos)
	{

	}
	void ButtonMenu::OnFocusExit(const Vector2D<>& aPos)
	{

	}

	BOOL ButtonMenu::CheckInside(const Vector2D<>& aPos)
	{
		return (aPos.mX < (mButtonRect.mX + mButtonRect.mW * 0.5f)
			&& aPos.mX > mButtonRect.mX - mButtonRect.mW * 0.5f
			&& aPos.mY < (mButtonRect.mY + mButtonRect.mH * 0.5f)
			&& aPos.mY > mButtonRect.mY - mButtonRect.mH * 0.5f);
	}

	void ButtonMenu::Update(const Vector2D<>& aPos)
	{
		BOOL wasFocused = mFocused;
		mFocused = CheckInside(aPos);
		if (mFocused) 
		{
			mTextScale = 2.0f;
		}
		else 
		{
			mTextScale = 1.0f;
		}
	}

	void ButtonMenu::Render()
	{
		if (mSprite)
		{
			mSprite->PrepareToRender(&Vector3D<float32>(mButtonRect.mX, mButtonRect.mY, 0.0f),
				&Vector3D<float32>(mButtonRect.mW, mButtonRect.mH, 1.0f));
		}
		if (mText.size() > 0) 
		{
			graphics::RenderManager::Instance()->RenderText(mText, mButtonRect.mX, mButtonRect.mY, mTextScale, mTextColor, mTextRenderer);
		}
	}

	void ButtonMenu::Release()
	{
		if (mSprite)
		{
			graphics::RenderManager::Instance()->DeleteSprite(mSprite);
			mSprite = NULL;
		}
		if (mTextRenderer) 
		{
			graphics::RenderManager::Instance()->UnloadTextRenderer(mTextRenderer);
			mTextRenderer = NULL;
		}
	}

} // namespace ui
