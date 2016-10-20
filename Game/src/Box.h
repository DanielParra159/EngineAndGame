#ifndef _GAME_BOX_H_
#define _GAME_BOX_H_

#include "Types.h"
#include "Logic/IGameObject.h"

namespace graphics
{
	class Mesh;
}

namespace game
{

	class Box : public logic::IGameObject
	{
	public:
		enum eBoxType
		{
			eWall, eCoin
		};

	private:
		eBoxType										mBoxType;
	public:
		Box() : IGameObject(){}
		virtual ~Box() {}
	
		virtual void									Init(eBoxType aBoxType, BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aBoxSize, const Vector3D<float32> aRotationOffset, const float32 lWallVertexData[], uint32 aSize);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();

	private:
		void											OnTriggerEnter(physics::Collider* aOther);
	
	}; // Box
} // namespace game
#endif // _GAME_BOX_H_
