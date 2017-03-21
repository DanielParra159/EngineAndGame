#include "Graphics\Material.h"
#include "Graphics\RenderManager.h"
#include "Graphics\Texture.h"
#include "Graphics\Shader.h"

#include <GL/glew.h>
#include <SDL_opengl.h>

#include <SOIL.h>

namespace graphics
{
	void Material::Init(const std::string& aName, const Shader* aVertexShader, const Shader* aFragmentShader, int32 aProgramShader)
	{
		mName = aName;

		mVertexShader = aVertexShader;
		mFragmentShader = aFragmentShader;
		mProgramShader = aProgramShader;

		mDiffuseTexture = NULL;
		mNormalTexture = NULL;

		mColorParam = glGetUniformLocation(mProgramShader, "color");
		mViewPos = glGetUniformLocation(mProgramShader, "viewPos");
		mTextureParam = glGetUniformLocation(mProgramShader, "texSample");
		mLightColorParam = glGetUniformLocation(mProgramShader, "lightColor");
		mLightPosParam = glGetUniformLocation(mProgramShader, "lightPos");
		mUseNormalMapping = glGetUniformLocation(mProgramShader, "useNormalMapping");

		mColor.mR = 1.0f;
		mColor.mG = 1.0f;
		mColor.mB = 1.0f;
		mColor.mA = 1.0f;
	}

	void Material::Release()
	{
		mParameters.clear();
		RenderManager::Instance()->UnloadTexture(mDiffuseTexture);
	}

	/*Material* Material::CreateInstance() {
		Material* lMaterial = new Material();
		lMaterial->Init(mName, mVertexShaderId, mFragmentShaderId, mProgramShader);
		lMaterial->mId = mId;
		lMaterial->mTextureId = mTextureId;
		return lMaterial;
	}*/

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
			lUniParam = glGetUniformLocation(mProgramShader, aParamName.c_str());
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
			lAttrib = glGetAttribLocation(mProgramShader, aAttribName.c_str());
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

	void Material::PrepareToRender(const Matrix4* aModelMatrix, const Vector3D<float32>& aViewPos, const Vector3D<float32>& aLightColor, const Vector3D<float32>& aLightPosition)
	{
		glUseProgram(mProgramShader);
		SetMatrix4("model", aModelMatrix);
		glUniform4f(mColorParam, mColor.mR, mColor.mG, mColor.mB, mColor.mA);

		glUniform1i(mUseNormalMapping, mNormalTexture != NULL);

		if (mViewPos > 0)
		{
			glUniform3f(mViewPos, EXPOSE_VECTOR3D(aViewPos));
		}
		
		if (mLightPosParam > 0)
		{
			glUniform3f(mLightColorParam, EXPOSE_VECTOR3D(aLightColor));
			glUniform3f(mLightPosParam, EXPOSE_VECTOR3D(aLightPosition));
		}
	}
} // namespace graphics
