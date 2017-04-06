/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#include "Graphics/TextRenderer.h"
#include "Graphics/RenderManager.h"
#include "Graphics/Material.h"

#include "Support/Matrix4.h"

#include "IO/FileSystem.h"

#include "Core/Log.h"

#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace graphics
{
	BOOL TextRenderer::Init(uint32 aWindowWidth, uint32 aWindowHeight, const std::string& aFont, uint32 aFontSize)
	{
		// Load and configure shader
		mMaterial = RenderManager::Instance()->LoadMaterial("Text");
		mMaterial->SetMatrix4("projection", &Matrix4x4::Orthographic(0.0f, (float32)aWindowWidth, (float32)aWindowHeight, 0.0f));
		mMaterial->SetInteger("text", 0);
		// Configure VAO/VBO for texture quads
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float32) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float32), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return Load(aFont, aFontSize);
	}

	void TextRenderer::Release() 
	{
		RenderManager::Instance()->UnloadMaterial(mMaterial);
		glDeleteTextures(1, &mTexture);
		mCharacters.clear();
	}

	BOOL TextRenderer::Load(const std::string& aFont, uint32 aFontSize)
	{
		// First clear the previously loaded Characters
		mCharacters.clear();
		// Then initialize and load the FreeType library
		FT_Library lFT;
		if (FT_Init_FreeType(&lFT)) {// All functions return a value different than 0 whenever an error occurred
			core::LogString("ERROR::FREETYPE: Could not init FreeType Library");
			return FALSE;
		}
		// Load font as face
		FT_Face lFace;
		std::string lFontPath = io::FileSystem::Instance()->GetCurrentDir() + "\\" + aFont;
		if (FT_New_Face(lFT, lFontPath.c_str(), 0, &lFace)) {
			core::LogString("ERROR::FREETYPE: Failed to load font");
			return FALSE;
		}
		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(lFace, 0, aFontSize);
		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		// Then for the first 128 ASCII characters, pre-load/compile their characters and store them
		for (uint8 c = 0; c < 128; c++) // lol see what I did there 
		{
			// Load character glyph 
			if (FT_Load_Char(lFace, c, FT_LOAD_RENDER))
			{
				core::LogFormatString("ERROR::FREETYTPE: Failed to load Glyph %d char %c", c, (int8)c);
				continue;
			}
			// Generate texture
			glGenTextures(1, &mTexture);
			glBindTexture(GL_TEXTURE_2D, mTexture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				lFace->glyph->bitmap.width,
				lFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				lFace->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Now store character for later use
			Character lCharacter = {
				mTexture,
				Vector2D<int32>(lFace->glyph->bitmap.width, lFace->glyph->bitmap.rows),
				Vector2D<int32>(lFace->glyph->bitmap_left, lFace->glyph->bitmap_top),
				lFace->glyph->advance.x
			};
			mCharacters.insert(std::pair<int8, Character>(c, lCharacter));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		// Destroy FreeType once we're finished
		FT_Done_Face(lFace);
		FT_Done_FreeType(lFT);
	}

	void TextRenderer::Render(const std::string& aText, float32 aX, float32 aY, float32 aScale, const Color32& aColor)
	{
		// Activate corresponding render state	
		mMaterial->UseMaterial();
		mMaterial->SetColor("textColor", aColor);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(mVAO);

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = aText.begin(); c != aText.end(); c++)
		{
			Character lChar = mCharacters[*c];

			float32 lPosX = aX + lChar.Bearing.mX * aScale;
			float32 lPosY = aY + (mCharacters['H'].Bearing.mY - lChar.Bearing.mY) * aScale;

			float32 lWidth = lChar.Size.mX * aScale;
			float32 lHeight = lChar.Size.mY * aScale;
			// Update VBO for each character
			float32 lVertices[6][4] = {
				{ lPosX,     lPosY + lHeight,   0.0, 1.0 },
				{ lPosX + lWidth, lPosY,       1.0, 0.0 },
				{ lPosX,     lPosY,       0.0, 0.0 },

				{ lPosX,     lPosY + lHeight,   0.0, 1.0 },
				{ lPosX + lWidth, lPosY + lHeight,   1.0, 1.0 },
				{ lPosX + lWidth, lPosY,       1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, lChar.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lVertices), lVertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph
			aX += (lChar.Advance >> 6) * aScale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Vector2D<float32> TextRenderer::TextSize(const std::string& aText, float32 aScale) {
		Vector2D<float32> lResult;
		std::string::const_iterator c;
		float32 aX = 0.0f;
		float32 aY = 0.0f;

		GLfloat lPosX;
		GLfloat lPosY;

		GLfloat lWidth;
		GLfloat lHeight;
		for (c = aText.begin(); c != aText.end(); c++)
		{
			Character lChar = mCharacters[*c];

			lPosX = aX + lChar.Bearing.mX * aScale;
			lPosY = aY + (mCharacters['H'].Bearing.mY - lChar.Bearing.mY) * aScale;

			lWidth = lChar.Size.mX * aScale;
			lHeight = lChar.Size.mY * aScale;

			aX += (lChar.Advance >> 6) * aScale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
		}

		lResult.mX = lPosX + lWidth;
		lResult.mY = lPosY + lHeight;

		return lResult;
	}
}