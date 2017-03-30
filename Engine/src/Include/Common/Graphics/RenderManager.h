#ifndef _ENGINE_GRAPHICS_RENDERERMANAGER_H_
#define _ENGINE_GRAPHICS_RENDERERMANAGER_H_

#include "Defs.h"
#include "Types.h"
#include "Graphics\Texture.h"
#include "Support\Rect.h"
#include "Support\Color.h"
#include "Support\Color32.h"
#include "Support\Vector2D.h"
#include "Support\Vector3D.h"
#include "Support\IdReferences.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>

struct  SDL_Renderer;
struct  SDL_Window;
struct  SDL_Texture;
struct  SDL_Surface;
/*#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>*/

class Color;

namespace core
{
	class Game;
}

namespace graphics
{
	class SpriteAnimator;
	class SpriteAnimatorComponent;
	class Sprite;
	class SpriteComponent;
	class Material;
	class Mesh;
	class MeshComponent;
	class Camera;
	class Shader;
	class MeshReferences;
	class TextRenderer;
	class IRenderable;
	class Light;


	typedef std::unordered_map<std::string, Texture*>			TTexturesIds;
	//typedef std::unordered_set<Texture*>						TLoadedTextures;
	typedef std::unordered_set<Material*>						TLoadedMaterials;
	typedef std::unordered_map<std::string, Shader*>			TShaderIds;
	typedef std::unordered_map<std::string, MeshReferences*>	TMeshesIds;
	typedef std::unordered_set<Mesh*>							TLoadedMeshes;
	typedef std::unordered_set<TextRenderer*>					TLoadedTextRenderer;
	
	/**
	This manager is responsible for painting in screen.
	*/
	class RenderManager
	{
		class RenderData {
		public:
			const IRenderable*							mRenderable;
			Vector3D<float32>							mPosition;
			Vector3D<float32>							mScale;
			Vector3D<float32>							mRotation;
			float32										mDistanceFromCamera;
		};
		typedef std::vector<RenderData*>				TRenderManagerToRender;

		friend class core::Game;
		SINGLETON_HEAD(RenderManager);
	private:
		Vector2D<uint32>								mWindowSize;
		Vector2D<int32>									mWindowPosition;
		Color											mClearColor;
		TTexturesIds									mLoadedTextures;
		TLoadedMaterials								mLoadedMaterials;
		TShaderIds										mLoadedVertexShaders;
		TShaderIds										mLoadedFragmentShaders;
		TMeshesIds										mMeshesIds;
		TLoadedMeshes									mMeshInstances;
		TLoadedTextRenderer								mLoadedTextRenderers;
		SDL_Renderer*									mRenderer;
		void *											mContext;
		SDL_Window*										mWindow;
		Camera*											mRenderCamera;
		TRenderManagerToRender							mRenderablesToRender;
		Light*											mMainLight;
	public:
		void											BeginRender();
		void											EndRender();
		
		const Vector2D<uint32>&							GetWindowSize() const { return mWindowSize; }
		const Vector2D<int32>&							GetWindowPositionSize() const { return mWindowPosition; }

		void											SetClearColor(const Color& aColor) { mClearColor = aColor; }

		//-----------------------------------------SPRITES-----------------------------------------
		/**
		Create a sprite from file
		@param aFileName, file name
		@param aFormat, texture format (RGB/RGBA)
		@return the sprite created or null
		*/
		Sprite*											CreateSprite(const std::string& aFileName, eTextureFormats aFormat);
		SpriteComponent*								CreateSpriteComponent(const std::string& aFileName, eTextureFormats aFormat);
		
		/**
		Delete a sprite previously created
		@param aSprite, the sprite to delete
		*/
		void											DeleteSprite(Sprite* aSprite);

		//-----------------------------------------END SPRITES-----------------------------------------

		/**
		Unload a texture
		@param aId, id of the texture
		*/
		void											UnloadTexture(const Texture* aTexture);
		/**
		Load a texture from file
		@param aFileName, file name
		@param aFormat, texture format (RGB/RGBA)
		@return aId, id of the texture loaded
		*/
		const Texture*									LoadTexture(const std::string& aFileName, eTextureFormats aFormat);

		//-----------------------------------------SPRITE ANIMATOR-----------------------------------------
		/**
		Create a sprite animator from texture file
		@param aFileName, file name
		@param aFormat, texture format (RGB/RGBA)
		@param aRows, num. of rows
		@param aCols, num. of colums
		@return the sprite animator created or null
		*/
		SpriteAnimator*									CreateSpriteAnimator(const std::string& aFileName, eTextureFormats aFormat, uint32 aRows, uint32 aCols);
		SpriteAnimatorComponent*						CreateSpriteAnimatorComponent(const std::string& aFileName, eTextureFormats aFormat, uint32 aRows, uint32 aCols);

		void											DeleteSpriteAnimator(SpriteAnimator* mSpriteAnimator);
		void											DeleteSpriteAnimatorComponent(SpriteAnimatorComponent* mSpriteAnimatorComponent);
		//----------------------------------------END SPRITE ANIMATOR---------------------------------------

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
		//-----------------------------------------END MESHES-----------------------------------------

		//-----------------------------------------TEXT-----------------------------------------
		TextRenderer*									LoadTextRenderer(std::string aFont, uint32 aFontSize);
		void											UnloadTextRenderer(TextRenderer* aTextRenderer);
		void											RenderText(std::string text, float32 aX, float32 aY, float32 aScale, const Color& aColor, TextRenderer* textRenderer);
		//----------------------------------------END TEXT---------------------------------------


		Camera*											CreatePerspectiveCamera(const Vector3D<float32>& aEye, const Vector3D<float32>& aPosition, const Vector3D<float32>& aUp,
																				float32 aFov, float32 aAspect, float32 aNear, float32 aFar);
		Camera*											CreateOrthographicCamera(float32 aLeft, float32 aRight, float32 aBottom, float32 aUp, float32 aZNear, float32 aZFar);
		void											SetRenderCamera(Camera* aCamera);
		Camera*											GetRenderCamera();


		void											CreateMainLight(const Vector3D<float32>& aPosition, const Color32& aColor = Color32::white);
		Light*											GetMainLight();
		void											PrepareToRender(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation, const IRenderable* aRenderable);

	private:
		RenderManager() : mLoadedTextures(), //mLoadedTexturesOLD(),
			mLoadedMaterials(),
			mLoadedVertexShaders(),
			mLoadedFragmentShaders(),
			mMeshesIds(), mMeshInstances(),
			mLoadedTextRenderers(),
			mMainLight(NULL),
			mWindow(0){}
		~RenderManager(){}
		BOOL											Init(const int8* aWindowTitle, const Vector2D<uint32> &aWindowSize,
															 const Vector2D<int32> &aWindowPosition, const Color& aClearColor,
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
		Material*										CreateMaterial(const std::string& aMaterialName, const std::string& aTextureName, const Shader* aVertexShader, const Shader* aFragmentShader, BOOL aTransparency);
	}; // RendererManager
} // namespace graphics
#endif // _ENGINE_GRAPHICS_RENDERERMANAGER_H_
