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
		graphics::Mesh*									mTail;
		static const int32								mMaxTailLength = 255;
		TTailState*										mTailStates[mMaxTailLength];
		uint32											mSnakeLenght;
		uint32											mCoins;
	public:
		Player() : IGameObject(), mSnakeLenght(), mDirection(), mTimeNextMovement(), mDelayBetweenMovements(){}
		virtual ~Player() {}
	
		virtual void									Init(BOOL aActive);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();

		void											AddCoin();

	private:
		void											ChangePos(float32 aNextX, float32 aNextZ);
		void											OnCollisionEnter(physics::Collider* other);


	
	}; // Player
} // namespace game
#endif // _GAME_PLAYER_H_
