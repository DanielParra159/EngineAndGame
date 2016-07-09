#ifndef _CORE_IGAMESTATE_H_
#define _CORE_IGAMESTATE_H_

#include "Types.h"

namespace core
{
	class Game;
	/**
	Pure abstract class than defines a GameState
	The user must overwrite to implemers their states
	*/
	class IGameState {
		friend class Game;
	protected:
		virtual BOOL 									Init() = 0;
		virtual void 									Release() = 0;
		
		virtual BOOL									Update() = 0;
		virtual void									Render() = 0;

		virtual const int8*								GetStateName() const = 0;
	}; // IGameState
} // namespace core
#endif // _CORE_IGAMESTATE_H_
