#ifndef _GAME_PLATFORMMERPLAYER_H_
#define _GAME_PLATFORMMERPLAYER_H_

#include "Types.h"
#include "Logic/IGameObject.h"

namespace physics
{
	class CapsuleController;
}

namespace graphics
{
	class SpriteComponent;
}

namespace game
{

	class PlatformerPlayer : public logic::IGameObject
	{
	private:
		physics::CapsuleController*						mCapsuleController;
		graphics::SpriteComponent*						mSprite;
		BOOL											mJumping;
		float64											mTimeEndJump;
		float64											mNextShoot;
	public:
		PlatformerPlayer() : IGameObject(){}
		virtual ~PlatformerPlayer() {}
	
		void											LuaInit(float32 aX, float32 aY);
		virtual void									Init(BOOL aActive, float32 aX, float32 aY);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();


	
	}; // PlatformmerPlayer
} // namespace game
#endif // _GAME_PLATFORMMERPLAYER_H_
