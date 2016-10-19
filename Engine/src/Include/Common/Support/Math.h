#ifndef _ENGINE_MATH_H_
#define _ENGINE_MATH_H_

#include "Types.h"

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
};
#endif // _ENGINE_MATH_H_