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
};
#endif // _ENGINE_MATRIX4_H_