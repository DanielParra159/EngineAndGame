#ifndef _ENGINE_AI_WAYPOINT_CALCULATOR_H_
#define _ENGINE_AI_WAYPOINT_CALCULATOR_H_

#include "Types.h"
#include "Support/Vector3D.h"

namespace ai
{
	class Waypoint;
	class IWaypointDistanceCalculator
	{
	public:
		IWaypointDistanceCalculator() {}
		virtual ~IWaypointDistanceCalculator() {}

		virtual float32									CalculateDistance(const Waypoint* aOrigenWaypoint, const Waypoint* aDestinationWaypoint) const = 0;
		virtual float32									CalculateDistance(const Waypoint* aOrigenWaypoint, const Vector3D<float32>& aPosition) const = 0;
		

	}; // IWaypointDistanceCalculator
} // namespace ai
#endif // _ENGINE_AI_WAYPOINT_CALCULATOR_H_
