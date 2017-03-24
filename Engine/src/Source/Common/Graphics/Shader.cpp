#include "Graphics/Shader.h"
#include "Graphics/RenderManager.h"

#include "Core/Log.h"

#include <GL/glew.h>

#include <SOIL.h>

namespace graphics
{
	BOOL Shader::Init(const std::string& aName, EShaderTypes aType, const int8* aSource)
	{
		mName = aName;	
		mReferencesCount = 1;
		mType = aType;

		if (mType == eVertex)
			mId = glCreateShader(GL_VERTEX_SHADER);
		else //if (mType == eFragment)
			mId = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(mId, 1, &aSource, NULL);
		glCompileShader(mId);

		int32 lStatus;
		glGetShaderiv(mId, GL_COMPILE_STATUS, &lStatus);

		return lStatus != 0;
	}

	void Shader::Release()
	{
		glDeleteShader(mId);
	}

	void Shader::AddReference() {
		++mReferencesCount;
	}

	uint32 Shader::RemoveReference() {
		return --mReferencesCount;
	}
} // namespace graphics
