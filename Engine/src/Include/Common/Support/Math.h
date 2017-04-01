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
		return glm::radians(aAngle);
	}

	static float32 Degrees(float32 aAngle)
	{
		return glm::degrees(aAngle);
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
};
#endif // _ENGINE_MATH_H_