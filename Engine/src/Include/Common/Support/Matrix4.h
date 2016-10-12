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
	static void translate(Matrix4* aM, const Vector3D<float32>* aV)
	{
		*aM = glm::translate(*aM, glm::tvec3<float>(aV->mX, aV->mY, aV->mZ));
	}
	static Matrix4 scale(const Matrix4* aM, const Vector3D<float32>* aV)
	{
		return glm::scale(*aM, glm::tvec3<float>(aV->mX, aV->mY, aV->mZ));
	}
	static void scale(Matrix4* aM, const Vector3D<float32>* aV)
	{
		*aM = glm::scale(*aM, glm::tvec3<float>(aV->mX, aV->mY, aV->mZ));
	}
	static Matrix4 rotate(const Matrix4* aM, const Vector3D<float32>* aV)
	{
		Matrix4 lM = glm::rotate(*aM, glm::radians(aV->mX), glm::tvec3<float>(1.0f, 0.0f, 0.0f));
		lM = glm::rotate(lM, glm::radians(aV->mY), glm::tvec3<float>(0.0f, 1.0f, 0.0f));
		return glm::rotate(lM, glm::radians(aV->mZ), glm::tvec3<float>(0.0f, 0.0f, 1.0f));
	}
	static void rotate(Matrix4* aM, const Vector3D<float32>* aV)
	{
		*aM = glm::rotate(*aM, glm::radians(aV->mX), glm::tvec3<float>(1.0f, 0.0f, 0.0f));
		*aM = glm::rotate(*aM, glm::radians(aV->mY), glm::tvec3<float>(0.0f, 1.0f, 0.0f));
		*aM = glm::rotate(*aM, glm::radians(aV->mZ), glm::tvec3<float>(0.0f, 0.0f, 1.0f));
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