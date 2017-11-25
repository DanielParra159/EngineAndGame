#include "AI/WaypointDistanceSqrtCalculator.h"
#include "AI/Waypoint.h"

#include <assert.h>

namespace ai
{
	float32 WaypointDistanceSqrtCalculator::CalculateDistance(const Waypoint* aOrigenWaypoint, const Waypoint* aDestinationWaypoint) const 
	{
		return aOrigenWaypoint->GetPosition()->GetDistanceSqrt(aDestinationWaypoint->GetPosition());
	}
	float32 WaypointDistanceSqrtCalculator::CalculateDistance(const Waypoint* aOrigenWaypoint, const Vector3D<float32>& aPosition) const
	{
		return aOrigenWaypoint->GetPosition()->GetDistanceSqrt(aPosition);
	}
	
} // namespace ai