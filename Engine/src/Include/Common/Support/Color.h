#ifndef _ENGINE_COLOR_H_
#define _ENGINE_COLOR_H_

#include "Types.h"

class Color {
public:
	uint8 mR, mG, mB, mA;
public:
	Color() : mR(0), mG(0), mB(0), mA(0) {}
	Color(const Color& aColor) : Color(aColor.mR, aColor.mG, aColor.mB, aColor.mA) {}
	Color(uint8 aR, uint8 aG, uint8 aB, uint8 aA) : mR(aR), mG(aG), mB(aB), mA(aA) {}
	Color(float32 aR, float32 aG, float32 aB, float32 aA) : mR((uint32)(aR * 255)), mG((uint32)(aG * 255)), mB((uint32)(aB * 255)), mA((uint32)(aA * 255)) {}
	~Color() {}

}; // Color

#endif // _ENGINE_SUPPORT_COLOR_H_
