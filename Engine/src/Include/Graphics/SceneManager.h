#ifndef _ENGINE_GRAPHICS_SCENEMANAGER_H_
#define _ENGINE_GRAPHICS_SCENEMANAGER_H_

#include "Types.h"
#include <list>

namespace graphics
{
	class IScene;
	class MatrixScene;

	class SceneManager
	{
	private:
		static SceneManager*							sInstance;

		IScene*											mCurrentScene;
	public:
		static SceneManager*							Instance();
		
		void											Update();
		void											Render();

		void											Init();
		void											Release();

		/**
		Create a new scene
		@return the scene created or null
		*/
		//IScene*											CreateScene();
		/**
		Create a new matrix scene
		@param width width of the matrix
		@param height height of the matrix
		@return the scene created or null
		*/
		MatrixScene*										CreateMatrixScene(uint32 aWidth, uint32 aHeight);
		/**
		Get the current scene
		@return the current scene
		*/
		IScene*											GetCurrentScene();
		/**
		Set the current scene
		@param aScene scene to assign
		*/
		void											SetScene(IScene* aScene);
		/**
		Remove and delete the current scene
		*/
		void											RemoveCurrentScene();
	private:
		SceneManager() : mCurrentScene(0) {}
		~SceneManager() {}
		
	};

} // namespace graphics
#endif // _ENGINE_GRAPHICS_SCENEMANAGER_H_
