#ifndef _ENGINE_GRAPHICS_RENDERER_H_
#define _ENGINE_GRAPHICS_RENDERER_H_

#include "Types.h"
#include "Support\Rect.h"
#include "Support\Vector2D.h"
#include "Support\Vector3D.h"
#include "Support\IdReferences.h"

#include <string>
#include <unordered_map>
#include <vector>

struct  SDL_Renderer;
struct  SDL_Window;
struct  SDL_Texture;
struct  SDL_Surface;
class Color;

namespace graphics
{
	class Texture;
	class Sprite;
	class Material;
	class Mesh;
	class Camera;


	typedef std::unordered_map<std::string, IdReferences*>		TTexturesIds;
	typedef std::vector<uint32>									TLoadedTextures;
	typedef std::unordered_map<std::string, IdReferences*>		TMaterialsIds;
	typedef std::vector<Material*>								TLoadedMaterials;
	typedef std::unordered_map<std::string, IdReferences*>		TMeshesIds;
	typedef std::vector<Mesh*>									TLoadedMeshes;
	/**
	This manager is responsible for painting in screen.
	*/
	class RenderManager
	{
	private:
		static RenderManager*							sInstance;
		TTexturesIds									mTexturesIds;
		TLoadedTextures									mLoadedTextures;
		uint32											mNumLoadedTextures;
		TMaterialsIds									mMaterialsIds;
		TLoadedMaterials								mLoadedMaterials;
		uint32											mNumLoadedMaterials;
		TMeshesIds										mMeshesIds;
		TLoadedMeshes									mLoadedMeshes;
		uint32											mNumLoadedMeshes;
		SDL_Renderer*									mRenderer;
		void *											mContext;
		SDL_Window*										mWindow;
		const Camera*									mRenderCamera;
	public:
		static RenderManager*							Instance();
		BOOL											Init(const int8* aWindowsTitle, const Vector2D<uint32> &aWindowsSize, 
															 const Vector2D<uint32> &aWindowsPosition, const Color& aRenderDrawColor,  
															 BOOL aFullscreen);
		void											Release();

		void											BeginRender();
		void											EndRender();

		/**
		Allow to render a texture on screen
		@param aId, texture ID
		@param aSrcRect, the rect in source texture to render
		@param aPosition, position on screen
		@param aSize, size on screen
		@param aAgnel, rotation on screen
		*/
		void											RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, const Vector2D<int32> &aSize, float64 aAngle);
		/**
		Allow to render a texture on screen
		@param aId, texture ID
		@param aSrcRect, the rect in source texture to render
		@param aX, aY, position on screen
		@param aW, aH, size on screen
		@param aAgnel, rotation on screen
		*/
		void											RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, int32 aX, int32 aY, int32 aW, int32 aH, float64 aAngle);
		
		/**
		Create a sprite from file
		@param aFileName, file name
		@return the sprite created or null
		*/
		Sprite*											CreateSprite(const std::string& aFileName);
		/**
		Delete a sprite previously created
		@param aSprite, the sprite to delete
		*/
		void											DeleteSprite(Sprite* aSprite);
		/**
		Unload a texture
		@param aId, id of the texture
		*/
		void											UnloadTexture(int32 aId);
		/**
		Load a texture from file
		@param aFileName, file name
		@return aId, id of the texture loaded
		*/
		int32											LoadTexture(const std::string& aFileName);


		//-----------------------------------------MATERIALS-----------------------------------------

		/**
		Load material from file
		@param aFileName, file name
		*/
		Material*										LoadMaterial(const std::string& aFileName, const int8* tempSourceVertex, const int8* tempSourceFragment);
		/**
		Unload a material
		@param aMaterial, material to unload
		*/
		void											UnloadMaterial(Material* aMaterial);

		//----------------------------------------END MATERIALS---------------------------------------

		//-----------------------------------------MESHES-----------------------------------------
		/**
		Load mesh from file
		@param aFileName, file name
		*/
		Mesh*											LoadMesh(const std::string& aFileName);
		/**
		Unload mesh
		@param aMesh, mesh to Unload
		*/
		void											UnloadMesh(Mesh* aMesh);

		void											RenderMesh(const Vector3D<float32>* aPosition, const Mesh* aMesh, Material* mMaterial);
		//-----------------------------------------END MESHES-----------------------------------------

		Camera*											CreatePerspectiveCamera(const Vector3D<float32>* aEye, const Vector3D<float32>* aPosition, const Vector3D<float32>* aUp,
																				float32 aFov, float32 aAspect, float32 aNear, float32 aFar);
		void											SetRenderCamera(const Camera* aCamera);

	private:
		RenderManager() : mTexturesIds(50), mLoadedTextures(50), mNumLoadedTextures(0),
			mMaterialsIds(50), mLoadedMaterials(50), mNumLoadedMaterials(0),
			mMeshesIds(50), mLoadedMeshes(50), mNumLoadedMeshes(0),
			mRenderer(0), mWindow(0){}
		~RenderManager(){}
	}; // Renderer
} // namespace graphics
#endif // _ENGINE_GRAPHICS_RENDERER_H_
