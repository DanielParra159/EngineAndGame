#ifndef _ENGINE_MATH_H_
#define _ENGINE_MATH_H_

#include "Types.h"

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Math
{
public:
	static float32 Radians(float32 aAngle)
	{
		return aAngle * 0.01745329251994329576923690768489f;
	}

	static float32 Degrees(float32 aAngle)
	{
		return aAngle * 57.295779513082320876798154814105f;
	}

	static int32 Random(int32 aMin, int32 aMax)
	{
		return rand() % (aMax - aMin) + aMin;
	}

	static float32 Random(float32 aMax, float32 aMin)
	{
		return aMin + rand() / (RAND_MAX / (aMax - aMin));
	}

	static float32 Abs(float32 aValue)
	{
		return abs(aValue);
	}
	static int32 Abs(int32 aValue)
	{
		return abs(aValue);
	}

	static float32 Sinf(float32 aValue)
	{
		return sinf(aValue);
	}

	static float32 Cosf(float32 aValue)
	{
		return cosf(aValue);
	}

	static float32 Atan2f(float32 aValue1, float32 aValue2)
	{
		return atan2f(aValue1, aValue2);
	}

	static float32 Max(float32 aValue1, float32 aValue2)
	{
		return aValue1 > aValue2 ? aValue1 : aValue2;
	}
	static float32 Min(float32 aValue1, float32 aValue2)
	{
		return aValue1 < aValue2 ? aValue1 : aValue2;
	}

	static float32 Clamp(float32 aValue, float32 aMinValue, float32 aMaxValue)
	{
		return Max(Min(aValue, aMaxValue), aMinValue);
	}
};
#endif // _ENGINE_MATH_H_