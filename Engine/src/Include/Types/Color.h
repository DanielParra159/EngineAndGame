#ifndef _ENGINE_CORE_COLOR_H_
#define _ENGINE_CORE_COLOR_H_

#include "Types.h"

class Color {
private:
	uint8 mR, mG, mB, mA;
public:
	Color();
	Color(const Color& aColor);
	Color(uint8 aR, uint8 aG, uint8 aB, uint8 aA);
	Color(float32 aR, float32 aG, float32 aB, float32 aA);
	~Color();

	uint8 GetR() const;
	uint8 GetG() const;
	uint8 GetB() const;
	uint8 GetA() const;
	void SetR(uint8 aR);
	void SetG(uint8 aG);
	void SetB(uint8 aB);
	void SetA(uint8 aA);

}; // Color

#endif // _ENGINE_CORE_COLOR_H_
