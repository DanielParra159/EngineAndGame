#include "Graphics\Mesh.h"
#include "Graphics\RenderManager.h"
#include "Graphics\Material.h"

#include <GL/glew.h>

namespace graphics
{
	void Mesh::Init(const std::string& aName, uint32 aVBO, float32* aVertexData, float32* aTextureCoords)
	{
		// Shader sources
		const int8* lTempVertexSource =
			"#version 150 core\n"
			""
			"in vec3 position;"
			"in vec2 texcoord;"
			""
			"out vec4 Color;"
			"out vec2 Texcoord;"
			""
			"uniform mat4 model;"
			"uniform mat4 view;"
			"uniform mat4 proj;"
			"uniform vec4 color;"
			""
			"void main()"
			"{"
			"    Color = color * vec4(1.0, 1.0, 1.0, 1.0);"
			"    Texcoord = texcoord;"
			"    gl_Position = proj * view * model * vec4(position, 1.0);"
			"}";
		const int8* lTempFragmentSource =
			"#version 150 core\n"
			""
			"in vec4 Color;"
			"in vec2 Texcoord;"
			""
			"out vec4 outColor;"
			""
			"uniform sampler2D texSample;"
			""
			"void main()"
			"{"
			"    outColor = Color * texture(texSample, Texcoord);"
			//"    outColor = vec4(Color, 1.0) * texture(texSample, Texcoord);"
			"}";

		mName = aName;
		mVBO = aVBO;
		mVertexData = aVertexData;
		mTextureCoords = aTextureCoords;

		mMaterial = RenderManager::Instance()->LoadMaterial("Test01", lTempVertexSource, lTempFragmentSource);

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
		lMesh->Init(mName, mVBO, mVertexData, mTextureCoords);
		lMesh->mId = mId;
		return lMesh;
	}

	void Mesh::Render(const Vector3D<float32>* aPosition)
	{
		RenderManager::Instance()->RenderMesh(aPosition, this, mMaterial);
	}


	void Mesh::Render(float32 aX, float32 aY, float32 aZ)
	{

	}

} // namespace graphics
