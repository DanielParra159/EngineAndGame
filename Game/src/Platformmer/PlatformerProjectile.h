#ifndef _GAME_PLATFORMMERPROJECTILE_H_
#define _GAME_PLATFORMMERPROJECTILE_H_

#include "Types.h"
#include "Logic/IGameObject.h"

#include "Support/Vector2D.h"

namespace physics
{
	class Collider;
}

namespace graphics
{
	class Mesh;
}

namespace game
{

	class PlatformerProjectile : public logic::IGameObject
	{
	private:
		float64											mLifeTime;
	public:
		PlatformerProjectile() : IGameObject(){}
		virtual ~PlatformerProjectile() {}
	
		virtual void									Init(const Vector3D<float32> aPosition, const Vector3D<float32> aDirection, BOOL aPlayerProjectile);
		virtual void									Update();
		virtual void									PrepareToRender();
		virtual void									Release();

	private:
		void											OnCollisionEnter(physics::Collider* other);
	
	}; // PlatformerProjectile
} // namespace game
#endif // _GAME_PLATFORMMERPROJECTILE_H_
