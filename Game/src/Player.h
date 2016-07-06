#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

#include "Types.h"

namespace game
{
	class Player
	{
	public:
		Player() {}
		~Player() {}
	
		BOOL											Init();
		void 											Release();

		void											Update();
	}; // Player
} // namespace game
#endif // _GAME_PLAYER_H_
