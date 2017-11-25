#ifndef _ENGINE_AI_WAYPOINTPATH_H_
#define _ENGINE_AI_WAYPOINTPATH_H_

#include "Types.h"
#include "Support\Vector3D.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace ai
{
	class Waypoint;
	class IWaypointDistanceCalculator;

	typedef std::vector<const Waypoint*>						TPathOfWaypoints;


	class WaypointPath
	{
		typedef std::unordered_set<Waypoint*>					TWaypoints;
	private:
		TWaypoints									mWaypoints;
		IWaypointDistanceCalculator*				mWaypointDistanceCalculator;

	public:
		WaypointPath() : mWaypoints(), mWaypointDistanceCalculator() {}
		~WaypointPath() {}
		void										Init(IWaypointDistanceCalculator *aWaypointDistanceCalculator);
		void										Release();

		const Waypoint*								AddWaypoint(const Vector3D<float32>& aPosition);
		void										AddConectionWithWaypoints(const Waypoint* aOrigenWaypoint, const Waypoint* aDestinationnWaypoint);
		void										FindPathToNearWaypoint(const Waypoint* aInitialWaypoint, const Waypoint* aTargetWaypoint, TPathOfWaypoints& aOutputPath) const;
		void										FindPathToNearWaypoint(const Vector3D<float32>& aOrigenPosition, const Waypoint* aTargetWaypoint, TPathOfWaypoints& aOutputPath) const;
		void										FindPathToNearWaypoint(const Vector3D<float32>& aOrigenPosition, const Vector3D<float32>& aTargetPosition, TPathOfWaypoints& aOutputPath) const;
		const Waypoint*								GetNearestWaypoint(const Vector3D<float32>& aOrigenPosition) const;

	private:
		void										GeneratePath(std::unordered_map<const Waypoint*, const Waypoint*> aPreviousWaypoint, const Waypoint* aTargetWaypoint, TPathOfWaypoints& aOutputPath) const;


	}; // WaypointPath
} // namespace ai
#endif // _ENGINE_AI_WAYPOINTPATH_H_
