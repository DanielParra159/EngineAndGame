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

	class PlatformerWall : public logic::IGameObject
	{
	public:

	public:
		PlatformerWall() : IGameObject(){}
		virtual ~PlatformerWall() {}
	
		void											LuaInit(float32 aX, float32 aY, float32 aSizeX, float32 aSizeY, int32 aType);
		virtual void									Init(BOOL aActive, const Vector3D<float32> aPosition, const Vector3D<float32> aSize, int32 aType);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();
	
	}; // PlatformmerWall
} // namespace game
#endif // _GAME_PLATFORMMERWALL_H_
