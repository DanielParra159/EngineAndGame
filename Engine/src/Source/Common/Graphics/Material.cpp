#include "Graphics\Material.h"
#include "Graphics\RenderManager.h"

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace graphics
{
	void Material::Init(const std::string& aName, int32 aVertexShaderId, int32 aFragmentShaderId, int32 aShaderPorgram)
	{
		mName = aName;

		mVertexShaderId = aVertexShaderId;
		mFragmentShaderId = aFragmentShaderId;
		mShaderPorgram = aShaderPorgram;
	}

	void Material::Release()
	{

	}

	void Material::SetId(int32 aId)
	{
		mId = aId;
	}

	Material* Material::CreateInstance() {
		Material* lMaterial = new Material();
		lMaterial->Init(mName, mVertexShaderId, mFragmentShaderId, mShaderPorgram);
		lMaterial->mId = mId;
		return lMaterial;
	}

	void Material::SetMatrix4(const std::string& aParamName, const Matrix4* aParamValue)
	{
		TParameters::const_iterator lParameterIterator = mParameters.find(aParamName);
		int32 lUniParam = -1;
		if (lParameterIterator != mParameters.end())
		{
			lUniParam = lParameterIterator->second;
		}
		else
		{
			lUniParam = glGetUniformLocation(mShaderPorgram, aParamName.c_str());
			mParameters[aParamName] = lUniParam;
		}

		SetMatrix4(lUniParam, aParamValue);
	}

	void Material::SetMatrix4(int32 aParamId, const Matrix4* aParamValue)
	{
		glUniformMatrix4fv(aParamId, 1, GL_FALSE, Matrix4x4::value_ptr(aParamValue));
	}

	void Material::SetVector3(const std::string& aParamName, const Vector3D<float32>* aParamValue)
	{

	}

	void Material::SetVector3(int32 aParamId, const Vector3D<float32>* aParamValue)
	{

	}

	void Material::SetVertexFloatAttribPointer(const std::string& aAttribName, int32 aNumberValues, BOOL aNormalize, uint32 aStride, uint32 aOffset, uint32 aVBO)
	{
		TParameters::const_iterator lParameterIterator = mParameters.find(aAttribName);
		int32 lAttrib = -1;
		if (lParameterIterator != mParameters.end())
		{
			lAttrib = lParameterIterator->second;
		}
		else
		{
			lAttrib = glGetUniformLocation(mShaderPorgram, aAttribName.c_str());
			mParameters[aAttribName] = lAttrib;
		}

		SetVertexFloatAttribPointer(lAttrib, aNumberValues, aNormalize, aStride, aOffset, aVBO);
	}

	void Material::SetVertexFloatAttribPointer(int32 aAttribId, int32 aNumberValues, BOOL aNormalize, uint32 aStride, uint32 aOffset, uint32 aVBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, aVBO);
		glEnableVertexAttribArray(aAttribId);
		glVertexAttribPointer(aAttribId, aNumberValues, GL_FLOAT, aNormalize ? GL_TRUE : GL_FALSE, aStride * sizeof(float32), (void*)(aOffset * sizeof(float32)));
		glBindVertexArray(0);
	}

} // namespace graphics
