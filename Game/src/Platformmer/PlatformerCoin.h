#ifndef _GAME_PLATFORMMERCOIN_H_
#define _GAME_PLATFORMMERCOIN_H_

#include "Types.h"
#include "Logic/IGameObject.h"

#include "Support/Vector2D.h"

namespace graphics
{
	class SpriteComponent;
	class Sprite;
}

namespace audio
{
	class Sound2D;
}

namespace game
{

	class PlatformerCoin : public logic::IGameObject
	{
	private:
		audio::Sound2D*									mSound;
	public:
		PlatformerCoin() : IGameObject(){}
		virtual ~PlatformerCoin() {}
	
		void											LuaInit(float32 aX, float32 aY, int32 aType);
		virtual void									Init(BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aSize, int32 aType);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();

		void											OnTriggerEnter(physics::Collider* other);
	
	}; // PlatformerCoin
} // namespace game
#endif // _GAME_PLATFORMMERCOIN_H_
