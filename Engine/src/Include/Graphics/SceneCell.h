#ifndef _ENGINE_GRAPHICS_SCENECELL_H_
#define _ENGINE_GRAPHICS_SCENECELL_H_

#include "Types.h"

namespace graphics
{
	class SceneCell
	{
		friend class MatrixScene;
	private:
		uint32  mType;
	private:
		SceneCell() : mType(0) {}
	};

} // namespace graphics
#endif // _ENGINE_GRAPHICS_SCENECELL_H_
