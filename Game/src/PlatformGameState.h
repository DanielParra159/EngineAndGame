#ifndef _GAME_PLATFORMGAMESTATE_H_
#define _GAME_PLATFORMGAMESTATE_H_

#include "Types.h"

#include "Core/IGameState.h"
#include "Support/Vector2D.h"

namespace audio
{
	class Sound2D;
}

namespace game
{
	enum EPltatformmerInputActions
	{
		ePltatformmerExit,
		ePltatformmerUp, ePltatformmerDown, ePltatformmerLeft, ePltatformmerRight,
		ePltatformmerJump,
		ePltatformmerShoot,
		ePltatformmerNum1, ePltatformmerNum2
	};

	class Map;

	class PlatformGameState : public core::IGameState
	{
	private:
		audio::Sound2D*									mMusic;
	public:
		static const									Vector2D<float32> sMapSize;
	public:
		PlatformGameState() {}
		~PlatformGameState() {}
	protected:
		virtual BOOL 									Init();
		virtual void 									Release();

		virtual BOOL									Update();
		virtual void									FixedUpdate();
		virtual void									Render();

		virtual const int8*								GetStateName() const { return "Platformmer"; }
	}; // PlatformGameState
} // namespace game
#endif // _GAME_PLATFORMGAMESTATE_H_
