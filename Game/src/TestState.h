#ifndef _GAME_TESTSTATE_H_
#define _GAME_TESTSTATE_H_

#include "Types.h"

#include "Core\IGameState.h"

namespace ui
{
	class Menu;
}

namespace graphics
{
	class Mesh;
}

namespace game
{
	class TestState : public core::IGameState
	{
	private:
		ui::Menu*										mMenu;
		graphics::Mesh*						mMesh;
		graphics::Mesh*						mMesh2;
	public:
		TestState() {}
		~TestState() {}
	protected:
		virtual BOOL 									Init();
		virtual void 									Release();

		virtual BOOL									Update();
		virtual void									Render();

		virtual const int8*								GetStateName() const { return "Test"; }
	}; // TestState
} // namespace game
#endif // _GAME_TESTSTATE_H_
