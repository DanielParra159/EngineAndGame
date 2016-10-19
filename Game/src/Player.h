#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

#include "Types.h"
#include "Logic/IGameObject.h"

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
		struct TTailState {
			Vector3D<float32>							mPosition;
			Vector3D<float32>							mRotation;
			uint32										mLife;
			TTailState() : mPosition(), mRotation(), mLife(0)
			{}
		};
		EDirections										mDirection;
		float64											mTimeNextMovement;
		float32											mDelayBetweenMovements;
		int32											mLastAction;
		graphics::Mesh*									mHead;
		graphics::Mesh*									mTail;
		static const int32								mMaxTailLength = 10;
		TTailState*										mTailStates[mMaxTailLength];
		uint32											mSnakeLenght;
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
