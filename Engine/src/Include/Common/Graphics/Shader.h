#ifndef _ENGINE_GRAPHICS_SHADER_H_
#define _ENGINE_GRAPHICS_SHADER_H_

#include "Types.h"

#include <string>

namespace graphics
{
	enum EShaderTypes
	{
		eVertex,
		eFragment
	};

	/**
	
	*/
	class Shader {
	friend class RenderManager;
	protected:
		std::string										mName;
		uint32											mId;
		uint32											mReferencesCount;
		EShaderTypes									mType;
	public:
		const std::string&								GetName() const { return mName; }
		int32											GetId() const { return mId; }
		EShaderTypes									GetType() const { return mType; }

		void											AddReference();
		uint32											RemoveReference();
	protected:
		Shader() : mReferencesCount(0) {}
		virtual ~Shader() {}
		virtual BOOL									Init(const std::string& aName, EShaderTypes aType, const int8* aSource);
		virtual void									Release();

	}; // Shader
} // namespace graphics
#endif // _ENGINE_GRAPHICS_SHADER_H_
