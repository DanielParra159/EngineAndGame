#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

#include "Types.h"
#include "Logic\IGameObject.h"

namespace graphics
{
	class Mesh;
}

namespace game
{

	class Player : public logic::IGameObject
	{
	private:
		enum EDirections
		{
			eUp, eDown, eLeft, eRight
		};
		EDirections										mDirection;
		uint32											mSnakeLenght;
		float64											mTimeNextMovement;
		float32											mDelayBetweenMovements;
		int32											mLastAction;
		graphics::Mesh*									mMesh;
	public:
		Player() : IGameObject(), mSnakeLenght(), mDirection(), mTimeNextMovement(),
			mLastAction(), mDelayBetweenMovements(){}
		virtual ~Player() {}
	
		virtual void									Init(BOOL aActive);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();

	private:
		void											ChangePos(float32 aNextX, float32 aNextZ);


	
	}; // Player
} // namespace game
#endif // _GAME_PLAYER_H_
