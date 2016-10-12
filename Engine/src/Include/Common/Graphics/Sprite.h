#ifndef _ENGINE_GRAPHICS_SPRITE_H_
#define _ENGINE_GRAPHICS_SPRITE_H_

#include "Types.h"
#include "Support\Rect.h"
#include "Support\Vector2D.h"
#include "Support\Vector3D.h"
#include "IRenderable.h"

#include <string>

namespace graphics
{
	/**
	This class allow to render a static sprite on screen
	*/
	class Sprite : public IRenderable
	{
		friend class RenderManager;
	protected:
		Rect<int32>										mTextureSize;
		float64											mAngle;
		int32											mTextureId;
	public:
		/**
		Render the sprite
		@param aPosition, position on screen
		@param aRotation, rotation on screen
		*/
		virtual void									Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero);
		/**
		Render the sprite
		@param aPosition, position on screen
		@param aSize, size on screen
		*/
		virtual void									Render(const Vector2D<int32>* aPosition, const Vector2D<int32>* aSize);
		/**
		Render the sprite
		@param aX, aY, position on screen, aZ is ignored
		*/
		virtual void									Render(float32 aX, float32 aY, float32 aZ);
		/**
		Render the sprite
		@param aX, aY, position on screen
		@param aW, aH, size on screen
		*/
		virtual void									Render(int32 aX, int32 aY, int32 aW, int32 aH);

		/**
		Sets the area occupied by the sprite in texture
		@param aTextureSize, area ocupied
		*/
		void											SetTextureSize(const Rect<int32>& aTextureSize);
		/**
		Sets the area occupied by the sprite in texture
		@param aX, aY, aW, aH, area ocupied
		*/
		void											SetTextureSize(uint32 aX, uint32 aY, uint32 aW, uint32 aH);
		/**
		Gets the area occupied by the sprite in texture
		@return area ocupied
		*/
		const Rect<int32>*								GetTextureSize() const	{ return &mTextureSize; }

		/**
		Sets the angle with which to paint on screen
		@param aAngle, angle
		*/
		void											SetAngle(float64 aAngle);
		/**
		Gets the angle with which to paint on screen
		@return angle
		*/
		float64											GetAngle() const { return mAngle; }

	protected:
		Sprite() : mTextureSize(), mTextureId(-1), mAngle(0) {}
		virtual ~Sprite() {}

		virtual void									Init(int32 aTextureId);
		virtual void									Release();

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITE_H_
