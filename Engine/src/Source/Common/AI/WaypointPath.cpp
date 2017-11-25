#include "AI/WaypointPath.h"
#include "AI/Waypoint.h"
#include "AI/IWaypointDistanceCalculator.h"
#include "Defs.h"

#include <assert.h>
#include <queue>
#include <limits.h>

namespace ai
{
	void WaypointPath::Init(IWaypointDistanceCalculator *aWaypointDistanceCalculator) {
		mWaypointDistanceCalculator = aWaypointDistanceCalculator;
	}
	void WaypointPath::Release() {
		delete mWaypointDistanceCalculator;
	}

	const Waypoint* WaypointPath::AddWaypoint(const Vector3D<float32>& aPosition)
	{
		Waypoint* lWaypoint = new Waypoint();
		lWaypoint->Init(aPosition);
		mWaypoints.insert(lWaypoint);
		return lWaypoint;
	}

	void WaypointPath::AddConectionWithWaypoints(const Waypoint* aOrigenWaypoint, const Waypoint* aDestinationnWaypoint)
	{
		float32 lDistance = mWaypointDistanceCalculator->CalculateDistance(aOrigenWaypoint, aDestinationnWaypoint);

		TWaypoints::const_iterator lWaypointsIterator = mWaypoints.find((Waypoint*)aOrigenWaypoint);
		assert(lWaypointsIterator != mWaypoints.end());
		(*lWaypointsIterator)->ConectWith(aDestinationnWaypoint, lDistance);

		lWaypointsIterator = mWaypoints.find((Waypoint*)aDestinationnWaypoint);
		assert(lWaypointsIterator != mWaypoints.end());
		(*lWaypointsIterator)->ConectWith(aOrigenWaypoint, lDistance);
	}

	void WaypointPath::GeneratePath(std::unordered_map<const Waypoint*, const Waypoint*> aPreviousWaypoint, const Waypoint* aTargetWaypoint, TPathOfWaypoints& aOutputPath) const 
	{
		if (aPreviousWaypoint.find(aTargetWaypoint) != aPreviousWaypoint.end())
			GeneratePath(aPreviousWaypoint, aPreviousWaypoint[aTargetWaypoint], aOutputPath);
		aOutputPath.push_back(aTargetWaypoint);
	}

	const Waypoint* WaypointPath::GetNearestWaypoint(const Vector3D<float32>& aOrigenPosition) const
	{
		const Waypoint* lResult;
		float32 lMinDistance = std::numeric_limits<float32>::max();

		LOOP_ITERATOR(TWaypoints::const_iterator, mWaypoints, lIterator, lEndElement) {
			float32 lDistance = mWaypointDistanceCalculator->CalculateDistance(*lIterator, aOrigenPosition);
			if (lDistance < lMinDistance) {
				lResult = *lIterator;
				lMinDistance = lDistance;
			}
		}
		
		return lResult;
	}

	void WaypointPath::FindPathToNearWaypoint(const Waypoint* aInitialWaypoint, const Waypoint* aTargetWaypoint, TPathOfWaypoints& aOutputPath) const
	{
		aOutputPath.clear();

		const Waypoint* lCurrentWaypoint;
		const TConectedWaypoints* lConectedWith = aInitialWaypoint->GetConectedWaypoints();

		TConectedWaypoints lDistancesBetweenWaypoints = TConectedWaypoints();
		std::unordered_set<const Waypoint*> lWaypointsVisited;
		std::priority_queue<TWaypointVertex, std::vector<TWaypointVertex>, VertexDistanceLessThan> lWaypointsToCheck;
		std::unordered_map<const Waypoint*, const Waypoint*> lPreviousWaypoint = std::unordered_map<const Waypoint*, const Waypoint*>();

		lWaypointsToCheck.push(TWaypointVertex(aInitialWaypoint, 0));
		lDistancesBetweenWaypoints[aInitialWaypoint] = 0;

		while (!lWaypointsToCheck.empty()) {
			lCurrentWaypoint = lWaypointsToCheck.top().first;
			lWaypointsToCheck.pop();
			if (lDistancesBetweenWaypoints.find(lCurrentWaypoint) == lDistancesBetweenWaypoints.end()) {
				lDistancesBetweenWaypoints[lCurrentWaypoint] = std::numeric_limits<float32>::max();
			}

			if (lCurrentWaypoint == aTargetWaypoint)
			{
				GeneratePath(lPreviousWaypoint, aTargetWaypoint, aOutputPath);
				break;
			}
			if (lWaypointsVisited.find(lCurrentWaypoint) != lWaypointsVisited.end())
				continue;
			lWaypointsVisited.insert(lCurrentWaypoint);

			const TConectedWaypoints* lConectedWith = lCurrentWaypoint->GetConectedWaypoints();

			LOOP_ITERATOR_WITH_POINTER(TConectedWaypoints::const_iterator, lConectedWith, lIterator, lEndElement) {
				const Waypoint* lAdyacent = (*lIterator).first;
				float32 lWeight = (*lIterator).second;
				if (lWaypointsVisited.find(lAdyacent) == lWaypointsVisited.end()) {
					if (lDistancesBetweenWaypoints.find(lAdyacent) == lDistancesBetweenWaypoints.end()
						|| lDistancesBetweenWaypoints[lCurrentWaypoint] + lWeight < lDistancesBetweenWaypoints[lAdyacent]) {
						lDistancesBetweenWaypoints[lAdyacent] = lDistancesBetweenWaypoints[lCurrentWaypoint] + lWeight;
						lPreviousWaypoint[lAdyacent] = lCurrentWaypoint;
						lWaypointsToCheck.push(TWaypointVertex(lAdyacent, lDistancesBetweenWaypoints[lAdyacent]));
					}
				}
			}
		}
	}
	void WaypointPath::FindPathToNearWaypoint(const Vector3D<float32>& aOrigenPosition, const Waypoint* aTargetWaypoint, TPathOfWaypoints& aOutputPath) const
	{
		FindPathToNearWaypoint(GetNearestWaypoint(aOrigenPosition), aTargetWaypoint, aOutputPath);
	}
	void WaypointPath::FindPathToNearWaypoint(const Vector3D<float32>& aOrigenPosition, const Vector3D<float32>& aTargetPosition, TPathOfWaypoints& aOutputPath) const
	{
		FindPathToNearWaypoint(aOrigenPosition, GetNearestWaypoint(aTargetPosition), aOutputPath);
	}
} // namespace ai