#include "Types\Color.h"


Color::Color() : mR(0), mG(0), mB(0), mA(0)
{

}

Color::Color(const Color& aColor) : Color(aColor.mR, aColor.mG, aColor.mB, aColor.mA)
{

}

Color::Color(uint8 aR, uint8 aG, uint8 aB, uint8 aA) : mR(aR), mG(aG), mB(aB), mA(aA)
{

}

Color::Color(float32 aR, float32 aG, float32 aB, float32 aA) : mR(aR*255), mG(aG * 255), mB(aB * 255), mA(aA * 255)
{

}

Color::~Color()
{

}

uint8 Color::GetR() const {
	return mR;
}
uint8 Color::GetG() const {
	return mG;
}
uint8 Color::GetB() const {
	return mB;
}
uint8 Color::GetA() const {
	return mA;
}
void Color::SetR(uint8 aR) {
	mR = aR;
}
void Color::SetG(uint8 aG) {
	mG = aG;
}
void Color::SetB(uint8 aB) {
	mB = aB;
}
void Color::SetA(uint8 aA) {
	mA = aA;
}
