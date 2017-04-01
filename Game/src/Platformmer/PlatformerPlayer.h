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
	class SpriteAnimatorComponent;
	class TextRenderer;
}

namespace game
{

	class PlatformerPlayer : public logic::IGameObject
	{
		enum eAnims {
			eIdle, eRun, eKunai, eJumpKunai, eStartJump, eEndJump, eMelee, eJumpMelee
		};
	private:
		physics::CapsuleController*						mCapsuleController;
		graphics::SpriteAnimatorComponent*				mSprite;
		graphics::TextRenderer*							mTextRenderer;
		BOOL											mJumping;
		float32											mTimeEndJump;
		float32											mNextTimeKunaiAllowed;
		float32											mDelayBetweenKunais;
		float32											mNextTimeMeleeAllowed;
		float32											mDelayBetweenMelee;
	public:
		PlatformerPlayer() : IGameObject(){}
		virtual ~PlatformerPlayer() {}
	
		void											LuaInit(float32 aX, float32 aY);
		virtual void									Init(BOOL aActive, float32 aX, float32 aY);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();


	
	}; // PlatformmerPlayer
} // namespace game
#endif // _GAME_PLATFORMMERPLAYER_H_
