#ifndef _GAME_PLATFORMMERGRASS_H_
#define _GAME_PLATFORMMERGRASS_H_

#include "Types.h"
#include "Logic/IGameObject.h"


namespace graphics
{
	class SpriteComponent;
}

namespace game
{

	class PlatformerGrass : public logic::IGameObject
	{
	private:
		graphics::SpriteComponent*						mSprite;
	public:
		PlatformerGrass() : IGameObject(){}
		virtual ~PlatformerGrass() {}
	
		virtual void									Init(BOOL aActive, float32 aX, float32 aY);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();


	
	}; // PlatformerGrass
} // namespace game
#endif // _GAME_PLATFORMMERGRASS_H_
