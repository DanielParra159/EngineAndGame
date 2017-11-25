#ifndef _ENGINE_AI_WAYPOINT_H_
#define _ENGINE_AI_WAYPOINT_H_

#include "Types.h"
#include "Support\Vector3D.h"

#include <unordered_map>


namespace ai
{
	class Waypoint;
	typedef std::pair<const Waypoint*, float32>				TWaypointVertex;
	typedef std::unordered_map<const Waypoint*, float32>	TConectedWaypoints;

	struct VertexDistanceLessThan {
		bool operator() (const TWaypointVertex &aVertex1, const TWaypointVertex &aVertex2) {
			return aVertex1.second > aVertex2.second;
		}
	};

	class Waypoint
	{
		friend class WaypointPath;
	private:
		Vector3D<float32>							mPosition;
		TConectedWaypoints							mConectedWith;

	public:
		const Vector3D<float32>*						GetPosition() const { return &mPosition; }
	private:
		Waypoint() : mPosition(), mConectedWith() {}
		~Waypoint() {}
		
		void											Init(const Vector3D<float32>& aPosition);
		void											Release();

		void											ConectWith(const Waypoint* aWaypoint, float32 aWeight);
		const TConectedWaypoints*						GetConectedWaypoints() const { return &mConectedWith; }

	

	}; // Waypoint
} // namespace ai
#endif // _ENGINE_AI_WAYPOINT_H_
