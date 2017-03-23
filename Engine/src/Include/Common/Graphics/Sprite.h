#ifndef _ENGINE_GRAPHICS_SPRITE_H_
#define _ENGINE_GRAPHICS_SPRITE_H_

#include "Types.h"
#include "Support\Rect.h"
#include "Support\Vector2D.h"
#include "Support\Vector3D.h"
#include "Mesh.h"

#include <string>

namespace graphics
{
	class Texture;
	/**
	This class allow to render a static sprite on screen
	*/
	class Sprite : public Mesh
	{
		friend class RenderManager;
	private:
		BOOL											mFlipX;
		BOOL											mFlipY;
	public:
		virtual void									Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero);
		void											SetFlipXY(BOOL aFlipX, BOOL aFlipY);
		void											SetFlipX(BOOL aFlipX);
		BOOL											GetFlipX() const { return mFlipX; }
		void											SetFlipY(BOOL aFlipY);
		BOOL											GetFlipY() const { return mFlipY; }

	protected:
		Sprite() : Mesh(), mFlipX(FALSE), mFlipY(FALSE){}
		virtual ~Sprite() {}

		virtual void									Init(const std::string& aName, uint32 aVBO, uint32 aEBO, const float32* aVertexData, uint32 aVertexDataLength, const uint32* aElementData, const float32* aTextureCoords, uint32 aNumVertex, BOOL aInstance);
		virtual void									Release();

		virtual IRenderable*							CreateInstance();

	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SPRITE_H_
