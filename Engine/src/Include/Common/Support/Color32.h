#ifndef _ENGINE_COLOR32_H_
#define _ENGINE_COLOR32_H_

#include "Types.h"

#define EXPOSE_COLOR32_RGB(color) ((color.mColor & 0x000000FF) / 255.0f), (((color.mColor & 0x0000FF00) >> 8) / 255.0f), (((color.mColor & 0x00FF0000) >> 16) / 255.0f)
#define EXPOSE_COLOR32_RGBA(color) EXPOSE_COLOR32_RGB(color), (((color.mColor & 0xFF000000) >> 24) / 255.0f)

class Color32 {
public:
	uint32 mColor;
	static const Color32 white;
	static const Color32 black;
	static const Color32 red;
	static const Color32 green;
	static const Color32 blue;
public:
	Color32() : mColor(0) {}
	~Color32() {}
	Color32(uint32 aColor) : mColor(aColor) {}
	Color32(const Color32& aColor) : Color32(mColor) {}
	Color32(uint8 aR, uint8 aG, uint8 aB, uint8 aA) : mColor(aR | (aG << 8) | (aB << 16) | (aA << 24)) {}
	Color32(float32 aR, float32 aG, float32 aB, float32 aA) : mColor((uint8)(aR * 255) | ((uint8)(aG * 255) << 8) | ((uint8)(aB * 255) << 16) | ((uint8)(aA * 255) << 24)) {}
	uint8 GetR() { return (mColor & 0x000000FF); }
	uint8 GetG() { return (mColor & 0x0000FF00) >> 8; }
	uint8 GetB() { return (mColor & 0x00FF0000) >> 16; }
	uint8 GetA() { return (mColor & 0xFF000000) >> 24; }
	float32 GetRf() { return (mColor & 0x000000FF) / 255.0f; }
	float32 GetGf() { return ((mColor & 0x0000FF00) >> 8) / 255.0f; }
	float32 GetBf() { return ((mColor & 0x00FF0000) >> 16) / 255.0f; }
	float32 GetAf() { return ((mColor & 0xFF000000) >> 24) / 255.0f; }
	void SetR(uint8 aR) { mColor = (mColor & 0xFFFFFF00) | aR; }
	void SetG(uint8 aG) { mColor = (mColor & 0xFFFF00FF) | aG << 8; }
	void SetB(uint8 aB) { mColor = (mColor & 0xFF00FFFF) | aB << 16; }
	void SetA(uint8 aA) { mColor = (mColor & 0x00FFFFFF) | aA << 24; }
	void SetR(float32 aR) { mColor = (mColor & 0xFFFFFF00) | (uint8)(aR * 255); }
	void SetG(float32 aG) { mColor = (mColor & 0xFFFF00FF) | (uint8)(aG * 255) << 8; }
	void SetB(float32 aB) { mColor = (mColor & 0xFF00FFFF) | (uint8)(aB * 255) << 16; }
	void SetA(float32 aA) { mColor = (mColor & 0x00FFFFFF) | (uint8)(aA * 255) << 24; }

}; // Color

#endif // _ENGINE_COLOR32_H_
