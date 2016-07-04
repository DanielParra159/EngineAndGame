#ifndef _ENGINE_RECT_H_
#define _ENGINE_RECT_H_

#include<math.h>
template <typename T = int32>
class Rect
{
private:
	T mX, mY;
	T mW, mH;

public:
	Rect() { mX = 0; mY = 0; mW = 0; mH = 0; };
	Rect(T aX, T aY, T aW, T aH) : mX(aX), mY(aY), mW(aW), mH(aH) {}
	Rect(const Rect<T>& aR2) : mX(aR2.mX), mY(aR2.mY), mW(aR2.aW), mH(aR2.aH) {};
	T GetX() const { return mX; }
	T GetY() const { return mY; }
	T GetW() const { return mW; }
	T GetH() const { return mH; }
	void SetX(T aX) { mX = aX; }
	void SetY(T aY) { mY = aY; }
	void SetW(T aW) { mW = aW; }
	void SetH(T aH) { mH = aH; }
};
#endif // _ENGINE_RECT_H_