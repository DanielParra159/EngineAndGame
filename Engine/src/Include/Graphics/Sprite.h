#ifndef _ENGINE_GRAPHICS_SPRITE_H_
#define _ENGINE_GRAPHICS_SPRITE_H_

#include "Types.h"
#include "Types\Rect.h"
#include "Renderable.h"
#include "Graphics\Texture.h"

#include <string>

namespace graphics
{
	class Sprite : public IRenderable
	{
		friend class TextureManager;
	protected:
		Rect<int32>										mSize;
		float64											mAngle;
		Texture*										mTexture;
	public:
		virtual void									Init(Texture *aTexture);
		virtual void									Release();

		virtual void									Render(const Vector2D<>* aPosition);
		virtual void									Render(int32 aX, int32 aY);

		void											SetSize(const Rect<int32>& aSize);
		void											SetSize(uint32 aX, uint32 aY, uint32 aW, uint32 aH);
		const Rect<int32>*								GetSize();

		void											SetAngle(float64 aAngle);
		float64											GetAngle();

	protected:
		Sprite() : mSize(), mTexture(0), mAngle(0) {}
		virtual ~Sprite() {}

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITE_H_
