#ifndef _ENGINE_PHYSICS_PHYSICSCONVERSIONS_H_
#define _ENGINE_PHYSICS_PHYSICSCONVERSIONS_H_

#include "Types.h"
#include "Support/Vector3D.h"

#include <foundation/PxVec3.h> 

namespace physics
{
	inline physx::PxVec3 Vector3DToPxVec3(const Vector3D<float32>& aVector)
	{
		return physx::PxVec3(EXPOSE_VECTOR3D(aVector));
	}

	inline Vector3D<float32> PxVec3ToVector3D(const physx::PxVec3& aVector)
	{
		return Vector3D<float32>(aVector.x, aVector.y, aVector.z);
	}
} // namespace physics
#endif // _ENGINE_PHYSICS_COLLIDER_H_
