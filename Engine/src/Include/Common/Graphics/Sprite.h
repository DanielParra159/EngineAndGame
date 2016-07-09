#ifndef _ENGINE_GRAPHICS_SPRITE_H_
#define _ENGINE_GRAPHICS_SPRITE_H_

#include "Types.h"
#include "Types\Rect.h"
#include "Renderable.h"

#include <string>

namespace graphics
{
	class Sprite : public IRenderable
	{
		friend class RenderManager;
	protected:
		Rect<int32>										mTextureSize;
		float64											mAngle;
		int32											mTextureId;
	public:

		virtual void									Render(const Vector2D<>* aPosition);
		virtual void									Render(const Vector2D<>* aPosition, const Vector2D<>* aSize);
		virtual void									Render(int32 aX, int32 aY);
		virtual void									Render(int32 aX, int32 aY, int32 aW, int32 aH);

		void											SetTextureSize(const Rect<int32>& aTextureSize);
		void											SetTextureSize(uint32 aX, uint32 aY, uint32 aW, uint32 aH);
		const Rect<int32>*								GetTextureSize() const	{ return &mTextureSize; }

		void											SetAngle(float64 aAngle);
		float64											GetAngle() const { return mAngle; }

	protected:
		Sprite() : mTextureSize(), mTextureId(-1), mAngle(0) {}
		virtual ~Sprite() {}

		virtual void									Init(int32 mTextureId);
		virtual void									Release();

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITE_H_
