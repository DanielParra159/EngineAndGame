#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include "Types.h"
#include "Logic\IGameObject.h"

namespace graphics
{
	class Mesh;
}

namespace game
{
	class Map : public logic::IGameObject
	{
	private:
		graphics::Mesh*									mGround;
		graphics::Mesh*									mWall;
	public:
		Map() : IGameObject() {}
		virtual ~Map() {}
	protected:
		virtual void									Init(BOOL aActive);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();
		

	
	}; // Map
} // namespace game
#endif // _GAME_MAP_H_
