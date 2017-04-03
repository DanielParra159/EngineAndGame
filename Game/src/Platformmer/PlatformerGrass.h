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
		Vector3D<float32> mRotation;
	};
	class PlatformerGrass : public logic::IGameObject
	{
	public:
		static PlatformerGrass* Instance;
	private:
		std::vector<TSpriteData*>						mSprites;
	public:
		PlatformerGrass() : IGameObject() { Instance = this; }
		virtual ~PlatformerGrass() {}
	
		virtual void									Init(BOOL aActive, float32 aX, float32 aY);
		void											AddElement(float32 aX, float32 aY, float32 aZ, int32 aType);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();


	
	}; // PlatformerGrass
} // namespace game
#endif // _GAME_PLATFORMMERGRASS_H_
