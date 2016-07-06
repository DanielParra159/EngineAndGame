#ifndef _ENGINE_RECT_H_
#define _ENGINE_RECT_H_

#include<math.h>
template <typename T = int32>
class Rect
{
public:
	T mX, mY;
	T mW, mH;
public:
	Rect() { mX = 0; mY = 0; mW = 0; mH = 0; };
	Rect(T aX, T aY, T aW, T aH) : mX(aX), mY(aY), mW(aW), mH(aH) {}
	Rect(const Rect<T>& aR2) : mX(aR2.mX), mY(aR2.mY), mW(aR2.mW), mH(aR2.mH) {};
};
#endif // _ENGINE_RECT_H_