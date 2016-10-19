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
	private:
		graphics::Mesh*									mMesh;
	public:
		Box() : IGameObject(){}
		virtual ~Box() {}
	
		virtual void									Init(BOOL aActive, const Vector3D<float> aPosition);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();
	
	}; // Box
} // namespace game
#endif // _GAME_BOX_H_
