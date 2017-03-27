/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Types.h"
#include "Support/Vector3D.h"
#include "Support/Vector2D.h"
#include "Support/Color.h"

#include <map>


namespace graphics
{
	class Material;

	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		uint32 TextureID;   // ID handle of the glyph texture
		Vector2D<int32> Size;    // Size of glyph
		Vector2D<int32> Bearing; // Offset from baseline to left/top of glyph
		uint32 Advance;     // Horizontal offset to advance to next glyph
	};


	// A renderer class for rendering text displayed by a font loaded using the 
	// FreeType library. A single font is loaded, processed into a list of Character
	// items for later rendering.
	class TextRenderer
	{
		friend class RenderManager;
	private:
		// Render state
		uint32 mVAO, mVBO;
		// Holds a list of pre-compiled Characters
		std::map<int8, Character> mCharacters;
		// Shader used for text rendering
		Material* mMaterial;
		uint32 mTexture;
	public:
		Vector2D<float32>								TextSize(const std::string& aText, float32 aScale);
	private:
		TextRenderer(){}
		virtual ~TextRenderer(){}
		BOOL Init(uint32 aWindowWidth, uint32 aWindowHeight, const std::string& aFont, uint32 aFontSize);
		void Release();
		BOOL Load(const std::string& aFont, uint32 aFontSize);

		// Renders a string of text using the precompiled list of characters
		void Render(const std::string& aText, float32 aX, float32 aY, float32 aScale, const Color& aColor);
	}; //TextRender
} // graphics
#endif 