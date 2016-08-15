#ifndef _ENGINE_COLOR_H_
#define _ENGINE_COLOR_H_

#include "Types.h"

class Color {
public:
	float32 mR, mG, mB, mA;
public:
	Color() : mR(0.0f), mG(0.0f), mB(0.0f), mA(0.0f) {}
	Color(const Color& aColor) : Color(aColor.mR, aColor.mG, aColor.mB, aColor.mA) {}
	Color(uint8 aR, uint8 aG, uint8 aB, uint8 aA) : mR(aR / 255.0f), mG(aG / 255.0f), mB(aB / 255.0f), mA(aA / 255.0f) {}
	Color(float32 aR, float32 aG, float32 aB, float32 aA) : mR(aR), mG(aG), mB(aB), mA(aA) {}
	~Color() {}

}; // Color

#endif // _ENGINE_SUPPORT_COLOR_H_
