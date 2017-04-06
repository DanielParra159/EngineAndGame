#ifndef _ENGINE_COLOR_H_
#define _ENGINE_COLOR_H_

#include "Types.h"

#define EXPOSE_COLOR_RGB(color) color.mR, color.mG, color.mB
#define EXPOSE_COLOR_RGBA(color) EXPOSE_COLOR_RGB(color), color.mA

class Color {
public:
	float32 mR, mG, mB, mA;
	static const Color white;
	static const Color black;
	static const Color red;
	static const Color green;
	static const Color blue;
public:
	Color() : mR(0.0f), mG(0.0f), mB(0.0f), mA(0.0f) {}
	Color(const Color& aColor) : Color(aColor.mR, aColor.mG, aColor.mB, aColor.mA) {}
	Color(uint8 aR, uint8 aG, uint8 aB, uint8 aA) : mR(aR / 255.0f), mG(aG / 255.0f), mB(aB / 255.0f), mA(aA / 255.0f) {}
	Color(float32 aR, float32 aG, float32 aB, float32 aA) : mR(aR), mG(aG), mB(aB), mA(aA) {}
	~Color() {}

	static void Lerp(const Color& aColorSrc, const Color& aColorDst, Color& aColorResult, float32 aTime)
	{
		aTime = Math::Clamp(aTime, 0.0f, 1.0f);
		aColorResult.mR = (aColorSrc.mR * (1.0f - aTime) + aColorDst.mR * aTime);
		aColorResult.mG = (aColorSrc.mG * (1.0f - aTime) + aColorDst.mG * aTime);
		aColorResult.mB = (aColorSrc.mB * (1.0f - aTime) + aColorDst.mB * aTime);
		aColorResult.mA = (aColorSrc.mA * (1.0f - aTime) + aColorDst.mA * aTime);
	}
}; // Color

#endif // _ENGINE_SUPPORT_COLOR_H_
