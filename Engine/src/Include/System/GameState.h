#ifndef _SYS_GAMESTATE_H_
#define _SYS_GAMESTATE_H_

#include "Types.h"

namespace sys
{
	class Game;
	class IGameState {
		friend class Game;
	protected:
		virtual BOOL 								Init(void) = 0;
		virtual void								Update(float elapsedTime) = 0;
		virtual void								Render(void) = 0;
		virtual void 								Release(void) = 0;

		virtual void 								OnPause(void) = 0;
		virtual void 								OnResume(void) = 0;

		virtual const int8*						GetStateName(void) const = 0;
	}; // IGameState
} // namespace sys
#endif // _SYS_GAMESTATE_H_
