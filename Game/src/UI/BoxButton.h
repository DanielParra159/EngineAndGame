#ifndef _GAME_BOXBUTTON_H_
#define _GAME_BOXBUTTON_H_

#include "Types.h"
#include "Logic/IGameObject.h"

namespace graphics
{
	class Mesh;
}

namespace game
{

	class BoxButton : public logic::IGameObject
	{
	public:
		BoxButton() : IGameObject(){}
		virtual ~BoxButton() {}
	
		virtual void									Init(const Vector3D<float32> aPosition, int32 aId);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();
	
	}; // BoxButton
} // namespace game
#endif // _GAME_BOXBUTTON_H_
