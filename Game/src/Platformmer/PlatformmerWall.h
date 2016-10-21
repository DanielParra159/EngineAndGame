#ifndef _GAME_PLATFORMMERWALL_H_
#define _GAME_PLATFORMMERWALL_H_

#include "Types.h"
#include "Logic/IGameObject.h"

#include "Support/Vector2D.h"

namespace graphics
{
	class Mesh;
}

namespace game
{

	class PlatformmerWall : public logic::IGameObject
	{
	public:

	public:
		PlatformmerWall() : IGameObject(){}
		virtual ~PlatformmerWall() {}
	
		void											LuaInit(float32 aX, float32 aY, float32 aSizeX, float32 aSizeY);
		virtual void									Init(BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aSize);
		virtual void									Update();
		virtual void									Render();
		virtual void									Release();
	
	}; // PlatformmerWall
} // namespace game
#endif // _GAME_PLATFORMMERWALL_H_