#include "Graphics/Sprite.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"

#include "System/Time.h"

#include "Support/Math.h"

#include <GL/glew.h>

namespace graphics
{
	void Sprite::Init(const std::string& aName, uint32 aVBO, uint32 aEBO, const float32* aVertexData, uint32 aVertexDataLength,
		const uint32* aElementData, const float32* aTextureCoords, uint32 aNumVertex, BOOL aInstance)
	{
		Mesh::Init(aName, aVBO, aEBO, aVertexData, aVertexDataLength, aElementData, aTextureCoords, aNumVertex, aInstance);
		mMaterial = RenderManager::Instance()->LoadMaterial("SpriteDiffuse");
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

	void Sprite::PrepareToRender(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation)
	{
		RenderManager::Instance()->PrepareToRender(aPosition, aScale, aRotation, this);
	}
	void Sprite::Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation)  const
	{
		Matrix4 lModelMatrix;
		Matrix4x4::translate(&lModelMatrix, aPosition);
		Matrix4x4::rotate(&lModelMatrix, aRotation);
		Matrix4x4::scale(&lModelMatrix, aScale);


		Camera* mRenderCamera = RenderManager::Instance()->GetRenderCamera();

		mMaterial->PrepareToRender(&lModelMatrix, mRenderCamera->GetCameraPosition());
		mMaterial->SetVertexFloatAttribPointer("position", 3, FALSE, 8, 0, mVBO);
		mMaterial->SetVertexFloatAttribPointer("normal", 3, FALSE, 8, 3, mVBO);
		mMaterial->SetVertexFloatAttribPointer("texcoord", 2, FALSE, 8, 6, mVBO);
		//@TODO: if is the same material only need to asign these attrib. one time
		mMaterial->SetMatrix4("view", mRenderCamera->GetView());
		mMaterial->SetMatrix4("proj", mRenderCamera->GetProj());
		mMaterial->SetFloat("time", sys::Time::GetCurrentSec());
		mMaterial->ActiveDiffuseTexture();
		mMaterial->ActiveNormalTexture();


		glDrawArrays(GL_TRIANGLES, 0, mNumVertex);
	}

	void Sprite::SetFlipXY(BOOL aFlipX, BOOL aFlipY)
	{
		mFlipX = aFlipX;
		mMaterial->SetBool("flipX", mFlipX);
		mFlipY = aFlipY;
		mMaterial->SetBool("flipY", mFlipY);
	}
	void Sprite::SetFlipX(BOOL aFlipX)
	{
		mFlipX = aFlipX;
		mMaterial->SetBool("flipX", mFlipX);
	}
	void Sprite::SetFlipY(BOOL aFlipY)
	{
		mFlipY = aFlipY;
		mMaterial->SetBool("flipY", mFlipY);
	}
	
} // namespace graphics