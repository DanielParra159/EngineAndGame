#include "Graphics/Mesh.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Material.h"
#include "Graphics/Camera.h"

#include "System/Time.h"

#include "Support/Math.h"

#include <GL/glew.h>

#include <assert.h>

namespace graphics
{
	void Mesh::Init(const std::string& aName, uint32 aVBO, uint32 aEBO, const float32* aVertexData, uint32 aVertexDataLength, 
		const uint32* aElementData, const float32* aTextureCoords, uint32 aNumVertex, BOOL aInstance)
	{
		mName = aName;
		mVBO = aVBO;
		mEBO = aEBO;
		mElementData = aElementData;
		mInstance = aInstance;

		mVertexData = new float32[aVertexDataLength];
		memcpy(mVertexData, aVertexData, aVertexDataLength);
		mVertexDataLength = aVertexDataLength;

		mNumVertex = aNumVertex;
		mTextureCoords = aTextureCoords;

 		mMaterial = RenderManager::Instance()->LoadMaterial("Test01");
	}

	void Mesh::Release()
	{
		RenderManager::Instance()->UnloadMaterial(mMaterial);
		mMaterial = NULL;
		delete[] mVertexData;
	}

	void Mesh::SetMaterial(Material *aMaterial)
	{
		assert(aMaterial && "Mesh::SetMaterial, aMaterial == NULL");
		if (mMaterial != NULL)
			RenderManager::Instance()->UnloadMaterial(mMaterial);
		mMaterial = aMaterial;
	}


	IRenderable* Mesh::CreateInstance()
	{
		Mesh* lMesh = new Mesh();
		lMesh->Init(mName, mVBO, mEBO, mVertexData, mVertexDataLength, mElementData, mTextureCoords, mNumVertex, TRUE);
		return lMesh;
	}

	void Mesh::Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation) const
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

	void Mesh::PrepareToRender(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation)
	{
		RenderManager::Instance()->PrepareToRender(aPosition, aScale, aRotation, this);
	}


} // namespace graphics
