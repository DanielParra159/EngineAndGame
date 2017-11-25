#ifndef _ENGINE_AI_DISTANCESQRT_CALCULATOR_H_
#define _ENGINE_AI_DISTANCESQRT_CALCULATOR_H_

#include "Types.h"
#include "IWaypointDistanceCalculator.h"

namespace ai
{
	class Waypoint;
	class WaypointDistanceSqrtCalculator : public IWaypointDistanceCalculator
	{
	public:
		WaypointDistanceSqrtCalculator() : IWaypointDistanceCalculator() {}
		virtual ~WaypointDistanceSqrtCalculator() {}

		virtual float32									CalculateDistance(const Waypoint* aOrigenWaypoint, const Waypoint* aDestinationWaypoint) const;
		virtual float32									CalculateDistance(const Waypoint* aOrigenWaypoint, const Vector3D<float32>& aPosition) const;
	}; // WaypointDistanceSqrtCalculator
} // namespace ai
#endif // _ENGINE_AI_DISTANCESQRT_CALCULATOR_H_
