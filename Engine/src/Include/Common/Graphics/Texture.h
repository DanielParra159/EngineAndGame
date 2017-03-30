#ifndef _ENGINE_GRAPHICS_TEXTURE_H_
#define _ENGINE_GRAPHICS_TEXTURE_H_

#include "Types.h"

#include <string>

namespace graphics
{
	enum eTextureFormats {
		eRGB,
		eRGBA
	};
	/**
	
	*/
	class Texture {
	friend class RenderManager;
	friend class Material;
	protected:
		std::string										mName;
		uint32											mId;
		int32											mWidth;
		int32											mHeight;
		uint32											mReferencesCount;
		eTextureFormats									mFormat;
	public:
		const std::string&								GetName() const { return mName; }
		int32											GetId() const { return mId; }
		int32											GetWidth() const { return mWidth; }
		int32											GetHeight() const { return mHeight; }
		eTextureFormats									GetFormat() const { return mFormat; }

		void											AddReference();
		uint32											RemoveReference();
	protected:
		Texture() : mId(0), mWidth(0), mHeight(0), mReferencesCount(0) {}
		virtual ~Texture() {}
		virtual BOOL									Init(const std::string& aName, eTextureFormats aFormat);
		virtual void									Release();

	}; // Texture
} // namespace graphics
#endif // _ENGINE_GRAPHICS_TEXTURE_H_
