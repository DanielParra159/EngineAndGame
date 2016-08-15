#ifndef _ENGINE_GRAPHICS_MATERIAL_H_
#define _ENGINE_GRAPHICS_MATERIAL_H_

#include "Types.h"
#include "Support\Color.h"
#include "Support\Vector3D.h"
#include "Support\Matrix4.h"

#include <string>
#include <unordered_map>

namespace graphics
{

	typedef std::unordered_map<std::string, int32>		TParameters;
	//typedef std::unordered_map<int32, float32>			TParameterValues;
	//typedef std::unordered_map<std::string, int32>		TAttrib;

	class Material {
	friend class RenderManager;
	protected:
		TParameters										mParameters;
		int32											mShaderProgram;
		int32											mVertexShaderId;
		int32											mFragmentShaderId;
		int32											mColorParam;
		Color											mColor;
		int32											mTextureParam;
		int32											mTextureId;
		std::string										mName;
		int32											mId;
	public:
		void											SetMatrix4(const std::string& aParamName, const Matrix4* aParamValue);
		void											SetMatrix4(int32 aParamId, const Matrix4* aParamValue);
		//TODO: get/generate paramId
		//void											SetVector3(const std::string& aParamName, const Vector3D<float32>* aParamValue);
		//void											SetVector3(int32 aParamId, const Vector3D<float32>* aParamValue);
		void											SetColor(const Color* aParamValue);
		const Color*									GetColor() const { return &mColor; }
		void											SetTextureId(int32 aTextureId) { mTextureId = aTextureId; }
		int32											GetTextureId() const { return mTextureId; }

		void											SetVertexFloatAttribPointer(const std::string& aAttribName, int32 aNumberValues, BOOL aNormalize, uint32 aStride, uint32 aOffset, uint32 aVBO);
		void											SetVertexFloatAttribPointer(int32 aAttribId, int32 aNumberValues, BOOL aNormalize, uint32 aStride, uint32 aOffset, uint32 aVBO);

		const std::string&								GetName() const { return mName; }
		int32											GetId() const { return mId; }
	protected:
		Material() : mParameters(0) {}
		virtual ~Material() {}
		virtual void									Init(const std::string& aName, int32 aVertexShaderId, int32 aFragmentShaderId, int32 aShaderPorgram);
		virtual void									Release();
		virtual void									PrepareToRender(const Matrix4* aModelMatrix);
		virtual Material*								CreateInstance();

	}; // Material
} // namespace graphics
#endif // _ENGINE_GRAPHICS_MATERIAL_H_
