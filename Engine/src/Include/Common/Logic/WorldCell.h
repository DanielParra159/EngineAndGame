#ifndef _ENGINE_LOGIC_WORLDCELL_H_
#define _ENGINE_LOGIC_WORLDCELL_H_

#include "Types.h"

namespace logic
{
	class WorldCell
	{
		friend class World;
	private:
		uint32											mType;
		float32											mLife;
		float64											mAngle;
	private:
		WorldCell() : mType(0), mLife(0.0f), mAngle(0.0f) {}
	public:
		uint32											GetType() const { return mType; }
		float32											GetLife() const { return mLife; }
		float64											GetAngle() const { return mAngle; }
		float64											SetAngle(float32 aAngle) { mAngle = aAngle; }
	};

} // namespace logic
#endif // _ENGINE_LOGIC_WORLDCELL_H_
