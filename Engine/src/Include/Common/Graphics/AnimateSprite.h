#ifndef _ENGINE_GRAPHICS_ANIMATESPRITE_H_
#define _ENGINE_GRAPHICS_ANIMATESPRITE_H_

#include "Types.h"
#include "Graphics\Sprite.h"

namespace graphics
{
	/**
	
	*/
	class AnimateSprite : public Sprite
	{
	protected:
		float32											mSpeed;
	public:

		virtual void									Render(const Vector3D<float32>* aPosition);
		virtual void									Render(float32 aX, float32 aY, float32 aZ);

		virtual void									Update();

		void											SetSpeed(float32 aSpeed);
		float32											GetSpeed() const { return mSpeed; };

	protected:
		AnimateSprite() : Sprite(), mSpeed(0.0f) {}
		virtual ~AnimateSprite(){}

	}; // AnimateSprite
} // namespace graphics
#endif // _ENGINE_GRAPHICS_ANIMATESPRITE_H_
