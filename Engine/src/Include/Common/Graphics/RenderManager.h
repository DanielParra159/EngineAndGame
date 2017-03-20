#ifndef _ENGINE_GRAPHICS_RENDERERMANAGER_H_
#define _ENGINE_GRAPHICS_RENDERERMANAGER_H_

#include "Defs.h"
#include "Types.h"
#include "Support\Rect.h"
#include "Support\Color.h"
#include "Support\Vector2D.h"
#include "Support\Vector3D.h"
#include "Support\IdReferences.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

struct  SDL_Renderer;
struct  SDL_Window;
struct  SDL_Texture;
struct  SDL_Surface;
class Color;

namespace core
{
	class Game;
}

namespace graphics
{
	class Texture;
	class Sprite;
	class Material;
	class Mesh;
	class MeshComponent;
	class Camera;
	class Shader;


	typedef std::unordered_map<std::string, Texture*>			TTexturesIds;
	//typedef std::unordered_set<Texture*>						TLoadedTextures;
	typedef std::unordered_set<Material*>						TLoadedMaterials;
	typedef std::unordered_map<std::string, Shader*>			TShaderIds;
	typedef std::unordered_map<std::string, IdReferences*>		TMeshesIds;
	typedef std::vector<Mesh*>									TLoadedMeshes;
	/**
	This manager is responsible for painting in screen.
	*/
	class RenderManager
	{
		friend class core::Game;
		SINGLETON_HEAD(RenderManager);
	private:
		Color											mClearColor;
		TTexturesIds									mLoadedTextures;
		//TLoadedTextures									mLoadedTexturesOLD;
		uint32											mNumLoadedTextures;
		TLoadedMaterials								mLoadedMaterials;
		TShaderIds										mLoadedVertexShaders;
		TShaderIds										mLoadedFragmentShaders;
		TMeshesIds										mMeshesIds;
		TLoadedMeshes									mLoadedMeshes;
		uint32											mNumLoadedMeshes;
		SDL_Renderer*									mRenderer;
		void *											mContext;
		SDL_Window*										mWindow;
		Camera*											mRenderCamera;
	public:
		void											BeginRender();
		void											EndRender();
		
		void											SetClearColor(const Color& aColor) { mClearColor = aColor; }

		/**
		Allow to render a texture on screen
		@param aTexture, texture
		@param aSrcRect, the rect in source texture to render
		@param aPosition, position on screen
		@param aSize, size on screen
		@param aAgnel, rotation on screen
		*/
		void											RenderTexture(const Texture* aTexture, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, const Vector2D<int32> &aSize, float64 aAngle);
		/**
		Allow to render a texture on screen
		@param aTexture, texture
		@param aSrcRect, the rect in source texture to render
		@param aX, aY, position on screen
		@param aW, aH, size on screen
		@param aAgnel, rotation on screen
		*/
		void											RenderTexture(const Texture* aTexture, const Rect<int32> &aSrcRect, int32 aX, int32 aY, int32 aW, int32 aH, float64 aAngle);
		
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
		void											UnloadTexture(const Texture* aTexture);
		/**
		Load a texture from file
		@param aFileName, file name
		@return aId, id of the texture loaded
		*/
		const Texture*									LoadTexture(const std::string& aFileName);


		//-----------------------------------------MATERIALS-----------------------------------------

		/**
		Load material from file
		@param aFileName, file name
		*/
		Material*										LoadMaterial(const std::string& aFileName);
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
		Mesh*											LoadMeshFromFile(const std::string& aFileName);
		MeshComponent*									LoadMeshComponentFromFile(const std::string& aFileName);
		/**
		Load mesh from vertex data
		@param aMeshName, mesh name
		@param aVertexData, vertex data
		@param aVertexDataLength, vertex date length
		@param aNumVertex, number of vertex
		*/
		Mesh*											LoadMeshFromVertexArray(const std::string& aMeshName, const float32* aVertexData, uint32 aVertexDataLength, uint32 aNumVertex);
		MeshComponent*									LoadMeshComponentFromVertexArray(const std::string& aMeshName, const float32* aVertexData, uint32 aVertexDataLength, uint32 aNumVertex);
		/**
		Unload mesh
		@param aMesh, mesh to Unload
		*/
		void											UnloadMesh(Mesh* aMesh, BOOL aPermanent);

		void											RenderMesh(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation, const Mesh* aMesh, Material* mMaterial);
		//-----------------------------------------END MESHES-----------------------------------------

		Camera*											CreatePerspectiveCamera(const Vector3D<float32>& aEye, const Vector3D<float32>& aPosition, const Vector3D<float32>& aUp,
																				float32 aFov, float32 aAspect, float32 aNear, float32 aFar);
		Camera*											CreateOrthographicCamera(float32 aLeft, float32 aRight, float32 aBottom, float32 aUp, float32 aZNear, float32 aZFar);
		void											SetRenderCamera(Camera* aCamera);
		Camera*											GetRenderCamera();

	private:
		RenderManager() : mLoadedTextures(), mNumLoadedTextures(0), //mLoadedTexturesOLD(),
			mLoadedMaterials(),
			mLoadedVertexShaders(),
			mLoadedFragmentShaders(),
			mMeshesIds(), mLoadedMeshes(), mNumLoadedMeshes(0),
			mRenderer(0), mWindow(0){}
		~RenderManager(){}
		BOOL											Init(const int8* aWindowsTitle, const Vector2D<uint32> &aWindowsSize,
															 const Vector2D<uint32> &aWindowsPosition, const Color& aClearColor,
															 BOOL aFullscreen);
		void											Release();

		/**
		Load mesh from vertex data
		@param aMeshName, mesh name
		@param aVertexData, vertex data
		@param aVertexDataLength, vertex date length
		@param aNumVertex, number of vertex
		*/
		Mesh*											LoadMesh(const std::string& aMeshName, const float32* aVertexData, uint32 aVertexDataLength, uint32 aNumVertex);
		/**
		Auxiliar function to parse material from file
		@param aFileName, file name
		@param aMaterialName, materia name (output param)
		@param aTextureName, texture name (output param)
		@param aVertexShaderName, vertex shader name (output param)
		@param aFragmentShaderName, fragment shader name (output param)
		@return TRUE if all is well
		*/
		BOOL											ParseMaterial(const std::string& aFileName, std::string& aMaterialName, std::string& aTextureName, std::string& aVertexShaderName, std::string& aFragmentShaderName);
		/**
		Auxiliar function to load vertex shader from file
		@param aMaterialFileName, material file name
		@param aVertexShaderName, vertex sahder name
		@return 
		*/
		const Shader*									LoadVertexShader(const std::string& aMaterialFileName, const std::string& aVertexShaderName);
		/**
		Auxiliar function to load fragment shader from file
		@param aMaterialFileName, material file name
		@param aFragmentShaderName, fragment sahder name
		@return 
		*/
		const Shader*									LoadFragmentShader(const std::string& aMaterialFileName, const std::string& aFragmentShaderName);
		/**
		Auxiliar function to create material
		@param aMaterialName, materia name
		@param aTextureName, texture name
		@param aVertexShader, vertex shader to be used
		@param aFragmentShader, fragment shader to be used
		*/
		Material*										CreateMaterial(const std::string& aMaterialName, const std::string& aTextureName, const Shader* aVertexShader, const Shader* aFragmentShader);
	}; // RendererManager
} // namespace graphics
#endif // _ENGINE_GRAPHICS_RENDERERMANAGER_H_
