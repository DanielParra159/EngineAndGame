#ifndef _ENGINE_LOGIC_SCENECELL_H_
#define _ENGINE_LOGIC_SCENECELL_H_

#include "Types.h"

namespace logic
{
	class WorldCell
	{
		friend class World;
	private:
		uint32											mType;
		float32											mLife;
	private:
		WorldCell() : mType(0), mLife(0.0f) {}
	};

} // namespace logic
#endif // _ENGINE_LOGIC_SCENECELL_H_
