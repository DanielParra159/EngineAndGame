#include "Graphics\Mesh.h"
#include "Graphics\RenderManager.h"
#include "Graphics\Material.h"

#include <GL/glew.h>

namespace graphics
{
	void Mesh::Init(const std::string& aName, uint32 aVBO, uint32 aEBO, const float32* aVertexData, const uint32* aElementData, const float32* aTextureCoords, uint32 aNumVertex)
	{
		mName = aName;
		mVBO = aVBO;
		mEBO = aEBO;
		mElementData = aElementData;
		mVertexData = aVertexData;
		mNumVertex = aNumVertex;
		mTextureCoords = aTextureCoords;

		mMaterial = RenderManager::Instance()->LoadMaterial("Test01");

		mMaterial->SetVertexFloatAttribPointer("position", 3, FALSE, 8, 0, mVBO);
		//mMaterial->SetVertexFloatAttribPointer("color", 3, FALSE, 8, 3, mVBO);
		mMaterial->SetVertexFloatAttribPointer("texcoord", 2, FALSE, 8, 6, mVBO);
	}

	void Mesh::Release()
	{
		RenderManager::Instance()->UnloadMaterial(mMaterial);
	}

	void Mesh::SetId(int32 aId) {
		mId = aId; 
	}

	Mesh* Mesh::CreateInstance()
	{
		Mesh* lMesh = new Mesh();
		lMesh->Init(mName, mVBO, mEBO, mVertexData, mElementData, mTextureCoords, mNumVertex);
		lMesh->mId = mId;
		return lMesh;
	}

	void Mesh::Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation)
	{
		RenderManager::Instance()->RenderMesh(aPosition, aScale, aRotation, this, mMaterial);
	}


	void Mesh::Render(float32 aX, float32 aY, float32 aZ)
	{

	}

} // namespace graphics
