#ifndef _GAME_PLATFORMMERGRASS_H_
#define _GAME_PLATFORMMERGRASS_H_

#include "Types.h"
#include "Logic/IGameObject.h"

#include <vector>

namespace graphics
{
	class Sprite;
}

namespace game
{
	struct TSpriteData {
		graphics::Sprite* mSprite;
		Vector3D<float32> mPosition;
		Vector3D<float32> mScale;
	};
	class PlatformerGrass : public logic::IGameObject
	{
	private:
		std::vector<TSpriteData*>						mSprites;
	public:
		PlatformerGrass() : IGameObject(){}
		virtual ~PlatformerGrass() {}
	
		virtual void									Init(BOOL aActive, float32 aX, float32 aY);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();


	
	}; // PlatformerGrass
} // namespace game
#endif // _GAME_PLATFORMMERGRASS_H_
