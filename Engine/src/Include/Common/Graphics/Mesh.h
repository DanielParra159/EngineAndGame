#ifndef _ENGINE_GRAPHICS_MESH_H_
#define _ENGINE_GRAPHICS_MESH_H_

#include "Types.h"
#include "Support\Vector3D.h"
#include "IRenderable.h"

#include <string>

namespace graphics
{
	class Material;

	/**
	This class allow to render meshes using a material and texture
	*/
	class Mesh : public IRenderable
	{
	friend class RenderManager;
	protected:
		Material*										mMaterial;
		uint32*											mElementData;
		float32*										mVertexData;
		float32*										mTextureCoords;
		uint32											mVBO;
		uint32											mEBO;
		std::string										mName;
		int32											mId;
	public:
		virtual void									Render(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale = &Vector3D<float32>::one, const Vector3D<float32>* aRotation = &Vector3D<float32>::zero);
		virtual void									Render(float32 aX, float32 aY, float32 aZ);

		const std::string&								GetName() const { return mName; }
		int32											GetId() const { return mId; }
		Material*										GetMaterial() { return mMaterial; }

	protected:
		Mesh() : mMaterial(0), mVertexData(0) {}
		virtual ~Mesh() {}

		virtual void									Init(const std::string& aName, uint32 aVBO, uint32 aEBO, float32* aVertexData, uint32* aElementData, float32* aTextureCoords);
		virtual void									Release();

		virtual Mesh*									CreateInstance();
		void											SetId(int32 aId);

	}; // Mesh
} // namespace graphics
#endif // _ENGINE_GRAPHICS_MESH_H_
