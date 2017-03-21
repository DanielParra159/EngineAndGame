#ifndef _GAME_NORMALMALSTATE_H_
#define _GAME_NORMALMALSTATE_H_

#include "Types.h"

#include "Core/IGameState.h"
#include "Support/Vector2D.h"

namespace audio
{
	class Sound2D;
}

namespace graphics
{
	class Mesh;
}

namespace game
{
	class Map;

	enum ENormalMapInputActions
	{
		eNormalMapExit
	};

	class NormalMapState : public core::IGameState
	{
	private:
		audio::Sound2D*									mMusic;
		graphics::Mesh*									mMesh;
		graphics::Mesh*									mMeshNormal;
	public:
		NormalMapState() {}
		~NormalMapState() {}
	protected:
		virtual BOOL 									Init();
		virtual void 									Release();

		virtual BOOL									Update();
		virtual void									FixedUpdate();
		virtual void									Render();

		virtual const int8*								GetStateName() const { return "NormalMap"; }
	}; // NormalMapState
} // namespace game
#endif // _GAME_NORMALMALSTATE_H_
