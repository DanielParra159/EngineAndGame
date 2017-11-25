#include "AI/Waypoint.h"

#include <assert.h>

namespace ai
{
	void Waypoint::Init(const Vector3D<float32>& aPosition) 
	{
		ASSIGN_VECTOR3D(aPosition, mPosition);
	}

	void Waypoint::Release() 
	{
		mConectedWith.clear();
	}

	void Waypoint::ConectWith(const Waypoint* aWaypoint, float32 aWeight)
	{
		assert(mConectedWith.find(aWaypoint) == mConectedWith.end());

		mConectedWith[aWaypoint] = aWeight;
	}
	
} // namespace ai