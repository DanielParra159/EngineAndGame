#include "Graphics\Material.h"
#include "Graphics\RenderManager.h"

#include <GL/glew.h>
#include <SDL_opengl.h>

#include <SOIL.h>

namespace graphics
{
	void Material::Init(const std::string& aName, int32 aVertexShaderId, int32 aFragmentShaderId, int32 aShaderPorgram)
	{
		mName = aName;

		mVertexShaderId = aVertexShaderId;
		mFragmentShaderId = aFragmentShaderId;
		mShaderProgram = aShaderPorgram;

		mTextureId = -1;
		mColorParam = glGetUniformLocation(mShaderProgram, "color");
		mTextureParam = glGetUniformLocation(mShaderProgram, "texSample");
	}

	void Material::Release()
	{

	}

	Material* Material::CreateInstance() {
		Material* lMaterial = new Material();
		lMaterial->Init(mName, mVertexShaderId, mFragmentShaderId, mShaderProgram);
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
			lUniParam = glGetUniformLocation(mShaderProgram, aParamName.c_str());
			mParameters[aParamName] = lUniParam;
		}

		SetMatrix4(lUniParam, aParamValue);
	}

	void Material::SetMatrix4(int32 aParamId, const Matrix4* aParamValue)
	{
		glUniformMatrix4fv(aParamId, 1, GL_FALSE, Matrix4x4::value_ptr(aParamValue));
	}

	/*void Material::SetVector3(const std::string& aParamName, const Vector3D<float32>* aParamValue)
	{
		TParameters::const_iterator lParameterIterator = mParameters.find(aParamName);
		int32 lParam = -1;
		if (lParameterIterator != mParameters.end())
		{
			lParam = lParameterIterator->second;
		}
		else
		{
			lParam = glGetUniformLocation(mShaderProgram, aParamName.c_str());
			mParameters[aParamName] = lParam;
		}

		SetVector3(lParam, aParamValue);
	}

	void Material::SetVector3(int32 aParamId, const Vector3D<float32>* aParamValue)
	{
		glUniform3f(aParamId, aParamValue->mX, aParamValue->mY, aParamValue->mZ);
	}*/

	void Material::SetColor(const Color* aParamValue)
	{
		mColor.mR = aParamValue->mR;
		mColor.mG = aParamValue->mG;
		mColor.mB = aParamValue->mB;
		mColor.mA = aParamValue->mA;
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
			lAttrib = glGetAttribLocation(mShaderProgram, aAttribName.c_str());
			mParameters[aAttribName] = lAttrib;
		}

		SetVertexFloatAttribPointer(lAttrib, aNumberValues, aNormalize, aStride, aOffset, aVBO);
	}

	void Material::SetVertexFloatAttribPointer(int32 aAttribId, int32 aNumberValues, BOOL aNormalize, uint32 aStride, uint32 aOffset, uint32 aVBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, aVBO);
		glEnableVertexAttribArray(aAttribId);
		glVertexAttribPointer(aAttribId, aNumberValues, GL_FLOAT, aNormalize ? GL_TRUE : GL_FALSE, aStride * sizeof(float32), (void*)(aOffset * sizeof(float32)));
		//glBindVertexArray(0);
	}

	void Material::PrepareToRender(const Matrix4* aModelMatrix)
	{
		glUseProgram(mShaderProgram);
		SetMatrix4("model", aModelMatrix);
		glUniform4f(mColorParam, mColor.mR / 255.0f, mColor.mG / 255.0f, mColor.mB / 255.0f, mColor.mA / 255.0f);
	}
} // namespace graphics
