#include "Graphics\Texture.h"
#include "Graphics\RenderManager.h"

#include <GL/glew.h>
#include <SDL_opengl.h>

#include <SOIL.h>

namespace graphics
{
	BOOL Texture::Init(const std::string& aName, eTextureFormats aFormat)
	{
		mName = aName;	
		mReferencesCount = 1;
		mFormat = aFormat;


		glGenTextures(1, &mId);
		glBindTexture(GL_TEXTURE_2D, mId);

		std::string lTexturePath = aName;
		uint8* aData = SOIL_load_image(aName.c_str(), &mWidth, &mHeight, 0, mFormat == eRGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
		if (aData != NULL)
		{
			if (mFormat == eRGBA)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, aData);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, aData);
			SOIL_free_image_data(aData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);

			return TRUE;
		}

		return FALSE;
	}

	void Texture::Release()
	{
		glDeleteTextures(1, &mId);
	}

	void Texture::AddReference() {
		++mReferencesCount;
	}

	uint32 Texture::RemoveReference() {
		return --mReferencesCount;
	}
} // namespace graphics
