#include "Graphics\Sprite.h"
#include "Graphics\RenderManager.h"
#include "Graphics\Texture.h"

#include "SDL.h"

namespace graphics
{
	void Sprite::Init(const std::string& aName, uint32 aVBO, uint32 aEBO, const float32* aVertexData, uint32 aVertexDataLength,
		const uint32* aElementData, const float32* aTextureCoords, uint32 aNumVertex, BOOL aInstance)
	{
		Mesh::Init(aName, aVBO, aEBO, aVertexData, aVertexDataLength, aElementData, aTextureCoords, aNumVertex, aInstance);
	}

	void Sprite::Release()
	{
		Mesh::Release();
	}

	IRenderable* Sprite::CreateInstance()
	{
		Sprite* lSprite = new Sprite();
		lSprite->Init(mName, mVBO, mEBO, mVertexData, mVertexDataLength, mElementData, mTextureCoords, mNumVertex, TRUE);
		return lSprite;
	}

	void Sprite::Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation)
	{
		RenderManager::Instance()->RenderSprite(aPosition, aScale, aRotation, this);
	}
	
} // namespace graphics