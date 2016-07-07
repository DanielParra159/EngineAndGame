#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

#include "Types.h"
#include "Types\Vector2D.h"

namespace game
{
	class Player
	{
	private:
		enum EDirections
		{
			eUp, eDown, eLeft, eRight
		};
		Vector2D<uint32>								mPosition;
		EDirections										mDirection;
		uint32											mSnakeLenght;
		float64											mTimeNextMovement;
		float32											mDelayBetweenMovements;
		int32											mLastAction;
	public:
		Player() : mPosition(), mSnakeLenght(), mDirection(), mTimeNextMovement(), 
			mLastAction(), mDelayBetweenMovements(){}
		~Player() {}
	
		BOOL											Init(uint32 aX, uint32 aY, uint32 aSnakeLenght);
		void 											Release();

		void											Update();

	private:
		void											ChangePos(uint32 aNextX, uint32 aNextY);

	
	}; // Player
} // namespace game
#endif // _GAME_PLAYER_H_
