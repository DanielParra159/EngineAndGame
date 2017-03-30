#include "Graphics\Material.h"
#include "Graphics\RenderManager.h"
#include "Graphics\Texture.h"
#include "Graphics\Shader.h"

#include <GL/glew.h>

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
	void Material::SetBool(const std::string& aAttribName, BOOL aValue) {
		UseMaterial();
		int32 lAttrib = glGetUniformLocation(mProgramShader, aAttribName.c_str());
		glUniform1i(lAttrib, aValue);
	}
	void Material::SetInteger(const std::string& aAttribName, int32 aValue) {
		UseMaterial();
		int32 lAttrib = glGetUniformLocation(mProgramShader, aAttribName.c_str());
		glUniform1i(lAttrib, aValue);
	}
	void Material::SetFloat(const std::string& aAttribName, float32 aValue) {
		UseMaterial();
		int32 lAttrib = glGetUniformLocation(mProgramShader, aAttribName.c_str());
		glUniform1f(lAttrib, aValue);
	}
	void Material::SetVector3(const std::string& aAttribName, const Vector3D<float32>& aValue)
	{
		UseMaterial();
		int32 lAttrib = glGetUniformLocation(mProgramShader, aAttribName.c_str());
		glUniform3f(lAttrib, EXPOSE_VECTOR3D(aValue));
	}
	void Material::SetColor(const std::string& aAttribName, const Color& aValue)
	{
		UseMaterial();
		int32 lAttrib = glGetUniformLocation(mProgramShader, aAttribName.c_str());
		glUniform4f(lAttrib, EXPOSE_COLOR_RGBA(aValue));
	}

	void Material::UseMaterial()
	{
		glUseProgram(mProgramShader);
	}

	void Material::PrepareToRender(const Matrix4* aModelMatrix, const Vector3D<float32>& aViewPos, const Vector3D<float32>& aLightColor, const Vector3D<float32>& aLightPosition)
	{
		UseMaterial();
		SetMatrix4("model", aModelMatrix);
		glUniform4f(mColorParam, EXPOSE_COLOR_RGBA(mColor));

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

	void Material::ActiveDiffuseTexture() {
		if (mDiffuseTexture != NULL)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mDiffuseTexture->mId);
			//glUniform1i(mMaterial->mTextureParam, 0);
		}
	}
	void Material::ActiveNormalTexture() {
		if (mNormalTexture != NULL)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mNormalTexture->mId);
			//glUniform1i(mMaterial->mTextureParam, 0);
		}
	}
} // namespace graphics
