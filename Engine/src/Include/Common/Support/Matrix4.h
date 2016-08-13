#ifndef _ENGINE_MATRIX4_H_
#define _ENGINE_MATRIX4_H_

#include "Types.h"
#include "Vector3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef glm::mat4 Matrix4;
//template <typename T = float32>
class Matrix4x4 //: public glm::mat4
{
public:
	static const float32* value_ptr(const Matrix4* aM)
	{
		return glm::value_ptr(*aM);
	}
	static Matrix4 translate(const Matrix4* aM, const Vector3D<float32>* aV)
	{
		return glm::translate(*aM, glm::tvec3<float>(aV->mX, aV->mY, aV->mZ));
	}
	static Matrix4 lookAt(const Vector3D<float32>* aEye, const Vector3D<float32>* aPosition, const Vector3D<float32>* aUp)
	{
		return glm::lookAt(
			glm::vec3(aEye->mX, aEye->mY, aEye->mZ),
			glm::vec3(aPosition->mX, aPosition->mY, aPosition->mZ),
			glm::vec3(aUp->mX, aUp->mY, aUp->mZ));
	}
	static Matrix4 Perspective(float32 aFov, float32 aAspect, float32 aZNear, float32 aZFar)
	{
		return glm::perspective(glm::radians(aFov), aAspect, aZNear, aZFar);
	}
};
#endif // _ENGINE_MATRIX4_H_