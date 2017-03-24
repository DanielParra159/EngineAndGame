#include "Graphics\Mesh.h"
#include "Graphics\RenderManager.h"
#include "Graphics\Material.h"

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

	void Mesh::Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation)
	{
		RenderManager::Instance()->RenderMesh(aPosition, aScale, aRotation, this);
	}


} // namespace graphics
