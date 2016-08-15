#include "Graphics\RenderManager.h"
#include "Graphics\Sprite.h"
#include "Graphics\Material.h"
#include "Graphics\Mesh.h"
#include "Graphics\Camera.h"

#include "Support\Color.h"
#include "Support\Matrix4.h"

#include "Core\Log.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include "SDL.h"
#include <SDL_opengl.h>
#include <SOIL.h>

namespace graphics
{
	RenderManager* RenderManager::sInstance = 0;

	RenderManager* RenderManager::Instance()
	{
		if (RenderManager::sInstance == 0)
		{
			RenderManager::sInstance = new RenderManager();
			return RenderManager::sInstance;
		}
		return RenderManager::sInstance;
	}

	BOOL RenderManager::Init(const int8* aWindowsTitle, const Vector2D<uint32> &aWindowsSize, const Vector2D<uint32> &aWindowsPosition, const Color& aRenderDrawColor, BOOL aFullscreen)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return FALSE;

		mWindow = SDL_CreateWindow(aWindowsTitle,
								   aWindowsPosition.mX, aWindowsPosition.mY,
								   aWindowsSize.mX, aWindowsSize.mY,
								   SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
								   //aFullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN); @TODO

		if (mWindow == 0)
			return FALSE;

		int oglIdx = -1;
		int nRD = SDL_GetNumRenderDrivers();
		for (int i = 0; i<nRD; i++)
		{
			SDL_RendererInfo info;
			if (!SDL_GetRenderDriverInfo(i, &info))
			{
				if (!strcmp(info.name, "opengl"))
				{
					oglIdx = i;
				}
			}
		}

		mContext = SDL_GL_CreateContext(mWindow);

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			// Problem: glewInit failed, something is seriously wrong.
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}

		glEnable(GL_DEPTH_TEST);

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

		if (mRenderer == 0)
			return FALSE;

		SDL_SetRenderDrawColor(mRenderer,
							   (uint32)(aRenderDrawColor.mR * 255),
							   (uint32)(aRenderDrawColor.mG * 255),
							   (uint32)(aRenderDrawColor.mB * 255),
							   (uint32)(aRenderDrawColor.mA * 255));

		return TRUE;
	}

	void RenderManager::Release()
	{
		TLoadedMeshes::const_iterator lMeshesIterator;
		TLoadedMeshes::const_iterator lMeshesEndElement = mLoadedMeshes.end();
		for (lMeshesIterator = mLoadedMeshes.begin(); lMeshesIterator != lMeshesEndElement; ++lMeshesIterator)
		{
			Mesh* lMesh = *lMeshesIterator;
			lMesh->Release();
			glDeleteBuffers(1, &lMesh->mVBO);
		}
		mLoadedMeshes.clear();
		mMeshesIds.clear();


		TLoadedMaterials::const_iterator lMaterialsIterator;
		TLoadedMaterials::const_iterator lMaterialsEndElement = mLoadedMaterials.end();
		for (lMaterialsIterator = mLoadedMaterials.begin(); lMaterialsIterator != lMaterialsEndElement; ++lMaterialsIterator)
		{
			Material* lMaterial = *lMaterialsIterator;
			lMaterial->Release();
			
			glDetachShader(lMaterial->mShaderProgram, lMaterial->mVertexShaderId);
			glDetachShader(lMaterial->mShaderProgram, lMaterial->mFragmentShaderId);
			glDeleteShader(lMaterial->mVertexShaderId);
			glDeleteShader(lMaterial->mFragmentShaderId);
			glDeleteProgram(lMaterial->mShaderProgram);
		}
		mLoadedMaterials.clear();
		mMaterialsIds.clear();

		TLoadedTextures::const_iterator lTexturesIterator;
		TLoadedTextures::const_iterator lTexturesEndElement = mLoadedTextures.end();
		for (lTexturesIterator = mLoadedTextures.begin(); lTexturesIterator != lTexturesEndElement; ++lTexturesIterator)
		{
			uint32 lTexture = *lTexturesIterator;
			glDeleteTextures(1, &lTexture);
		}
		mLoadedTextures.clear();
		mTexturesIds.clear();

		SDL_GL_DeleteContext(mContext);
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
	}

	void RenderManager::BeginRender()
	{
		// Clear the screen to black
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//SDL_RenderClear(mRenderer);

		
	}

	void RenderManager::EndRender()
	{
		SDL_GL_SwapWindow(mWindow);
		//SDL_RenderPresent(mRenderer);
	}

	void RenderManager::RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, const Vector2D<int32> &aPosition, const Vector2D<int32> &aSize, float64 aAngle)
	{
		RenderTexture(aId, aSrcRect, aPosition.mX, aPosition.mY, aSize.mX, aSize.mY, aAngle);
	}
	void RenderManager::RenderTexture(uint32 aId, const Rect<int32> &aSrcRect, int32 aX, int32 aY, int32 aW, int32 aH, float64 aAngle)
	{
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = aSrcRect.mX;
		srcRect.y = aSrcRect.mY;
		srcRect.w = aSrcRect.mW;

		srcRect.h = aSrcRect.mH;
		destRect.x = aX;
		destRect.y = aY;
		destRect.w = aW;
		destRect.h = aH;
		
		//SDL_RenderCopyEx(mRenderer, mLoadedTextures[aId], &srcRect, &destRect, aAngle, 0, SDL_FLIP_NONE);
	}

	void RenderManager::UnloadTexture(int32 aId)
	{
		if (aId < 0) return;
		TTexturesIds::const_iterator lIterator = mTexturesIds.begin();
		TTexturesIds::const_iterator lIteratorEnd = mTexturesIds.end();
		while (lIterator != lIteratorEnd && lIterator->second->mId != aId)
		{
			++lIterator;
		}
		if (--lIterator->second->mReferences == 0)
		{
			uint32 lAux = mLoadedTextures[aId];
			glDeleteTextures(1, &lAux);
			mLoadedTextures[aId] = 0;

			delete lIterator->second;

			mTexturesIds.erase(lIterator);
			--mNumLoadedTextures;

		}
	}

	int32 RenderManager::LoadTexture(const std::string& aFileName)
	{
		int32 lResult = -1;
		TTexturesIds::const_iterator lTextureIterator = mTexturesIds.find(aFileName);

		if (lTextureIterator != mTexturesIds.end())
		{
			++lTextureIterator->second->mReferences;
			return lTextureIterator->second->mId;
		}

		uint32 lTextureId;
		glGenTextures(1, &lTextureId);

		int width, height;
		unsigned char* image;

		glBindTexture(GL_TEXTURE_2D, lTextureId);
		image = SOIL_load_image(aFileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

		if (image != 0)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			uint32 lCapacity = mLoadedTextures.capacity();
			lResult = 0;
			if (mNumLoadedTextures == lCapacity)
			{
				mLoadedTextures.push_back(lTextureId);
				lResult = ++lCapacity;
			} 
			else 
			{
				int32 lSize = mLoadedTextures.size();
				
				while (lResult < lSize && mLoadedTextures[lResult] != 0)
				{
					++lResult;
				}
					
				if (lResult < lSize)
				{
					mLoadedTextures[lResult] = lTextureId;
				}
				else
				{
					mLoadedTextures.push_back(lTextureId);
				}
			}

			mTexturesIds[aFileName] = new IdReferences(lResult, 1);
			++mNumLoadedTextures;
		}
		else
		{
			core::LogFormatString("Can't load image %s", aFileName.c_str());
		}

		return lResult;
	}

	Sprite* RenderManager::CreateSprite(const std::string& aFileName)
	{
		Sprite *lResult = 0;

		int32 lTextureId = LoadTexture(aFileName);
		if (lTextureId > -1)
		{
			lResult = new Sprite();
			lResult->Init(lTextureId);
		}

		return lResult;
	}

	void RenderManager::DeleteSprite(Sprite* aSprite)
	{
		aSprite->Release();
		delete aSprite;
		aSprite = 0;
	}


	//-----------------------------------------MATERIALS-----------------------------------------

	Material* RenderManager::LoadMaterial(const std::string& aFileName, const int8* tempSourceVertex, const int8* tempSourceFragment)
	{
		Material* lResult = 0;

		TMaterialsIds::const_iterator lMaterialIterator = mMaterialsIds.find(aFileName);

		if (lMaterialIterator != mMaterialsIds.end())
		{
			++lMaterialIterator->second->mReferences;
			return mLoadedMaterials[lMaterialIterator->second->mId]->CreateInstance();
		}

		//@TODO: load from file
		const int8* aVertexSource = tempSourceVertex;
		const int8* aFragmentSource = tempSourceFragment;

		if (aVertexSource != 0 && aFragmentSource != 0)
		{
			int32 lVertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(lVertexShader, 1, &aVertexSource, NULL);
			glCompileShader(lVertexShader);

			int32 lStatus;
			glGetShaderiv(lVertexShader, GL_COMPILE_STATUS, &lStatus);
			if (lStatus == FALSE)
			{
				int8 lBuffer[512];
				glGetShaderInfoLog(lVertexShader, 512, NULL, lBuffer);
				core::LogFormatString("%s", lBuffer);
				core::LogFormatString("Can't compile vertex shader %s", aFileName.c_str());
				return lResult;
			}

			int32 lFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(lFragmentShader, 1, &aFragmentSource, NULL);
			glCompileShader(lFragmentShader);

			glGetShaderiv(lFragmentShader, GL_COMPILE_STATUS, &lStatus);

			if (lStatus == FALSE)
			{
				int8 lBuffer[512];
				glGetShaderInfoLog(lFragmentShader, 512, NULL, lBuffer);
				core::LogFormatString("%s", lBuffer);
				core::LogFormatString("Can't compile fragment shader %s", aFileName.c_str());
				return lResult;
			}

			int32 lShaderPorgram = glCreateProgram();
			glAttachShader(lShaderPorgram, lVertexShader);
			glAttachShader(lShaderPorgram, lFragmentShader);
			glBindFragDataLocation(lShaderPorgram, 0, "outColor");
			glLinkProgram(lShaderPorgram);
			glUseProgram(lShaderPorgram);

			lResult = new Material();
			lResult->Init(aFileName, lVertexShader, lFragmentShader, lShaderPorgram);

			//@TODO: Read from file defaul params and assign it
			lResult->mTextureId = LoadTexture("sample.png");

			uint32 lIndex = 0;
			if (mNumLoadedMaterials == mLoadedMaterials.capacity())
			{
				mLoadedMaterials.push_back(lResult);
			}
			else
			{
				uint32 lSize = mLoadedMaterials.size();
				while (lIndex < lSize && mLoadedMaterials[lIndex] != 0)
				{
					++lIndex;
				}

				if (lIndex < lSize)
				{
					mLoadedMaterials[lIndex] = lResult;
				}
				else
				{
					mLoadedMaterials.push_back(lResult);
				}
			}

			mMaterialsIds[aFileName] = new IdReferences(lIndex, 1);
			++mNumLoadedMaterials;
		}
		else
		{
			core::LogFormatString("Can't load shader %s", aFileName.c_str());
		}
		return lResult;
	}
	void RenderManager::UnloadMaterial(Material* aMaterial)
	{
		TMaterialsIds::const_iterator lIterator = mMaterialsIds.begin();
		TMaterialsIds::const_iterator lIteratorEnd = mMaterialsIds.end();
		while (lIterator != lIteratorEnd && lIterator->second->mId != aMaterial->mId)
		{
			++lIterator;
		}
		if (--lIterator->second->mReferences == 0)
		{
			mLoadedMaterials[aMaterial->mId] = 0;

			mMaterialsIds.erase(lIterator);
			--mNumLoadedMaterials;


			glDetachShader(aMaterial->mShaderProgram, aMaterial->mVertexShaderId);
			glDetachShader(aMaterial->mShaderProgram, aMaterial->mFragmentShaderId);
			glDeleteShader(aMaterial->mVertexShaderId);
			glDeleteShader(aMaterial->mFragmentShaderId);
			glDeleteProgram(aMaterial->mShaderProgram);
		}
		aMaterial->Release();
		delete aMaterial;
	}
	//----------------------------------------END MATERIALS---------------------------------------

	//-----------------------------------------MESHES-----------------------------------------
	Mesh* RenderManager::LoadMesh(const std::string& aFileName)
	{
		Mesh* lResult;

		TMeshesIds::const_iterator lMeshIterator = mMeshesIds.find(aFileName);

		if (lMeshIterator != mMeshesIds.end())
		{
			++lMeshIterator->second->mReferences;
			return mLoadedMeshes[lMeshIterator->second->mId]->CreateInstance();
		}

		float32 lVertexData[] = {
			// X      Y     Z     R     G     B     U     V
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

			0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,



			-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		};;
		float32* lTextureCoords = 0;

		//TODO: load from file
		if (lVertexData != 0 /*&& lTextureCoords != 0*/)
		{

			lResult = new Mesh();

			uint32 mVBO;
			glGenBuffers(1, &mVBO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(lVertexData), lVertexData, GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, sizeof(lVertexData), lVertexData, GL_STATIC_DRAW);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(lTextureCoords), lTextureCoords, GL_STATIC_DRAW);

			lResult->Init(aFileName, mVBO, lVertexData, lTextureCoords);

			uint32 lIndex = 0;
			uint32 lCapacity = mLoadedMeshes.capacity();
			if (mNumLoadedMeshes == lCapacity)
			{
				mLoadedMeshes.push_back(lResult);
			}
			else
			{
				uint32 lSize = mLoadedMeshes.size();
				
				while (lIndex < lSize && mLoadedMeshes[lIndex] != 0)
				{
					++lIndex;
				}

				if (lIndex < lSize)
				{
					mLoadedMeshes[lIndex] = lResult;
				}
				else
				{
					mLoadedMeshes.push_back(lResult);
				}
			}

			mMeshesIds[aFileName] = new IdReferences(lIndex, 1);
			++mNumLoadedMeshes;
			
		}
		else
		{
			core::LogFormatString("Can't load mesh %s", aFileName.c_str());
		}

		return lResult;
	}

	void RenderManager::UnloadMesh(Mesh* aMesh)
	{
		TMeshesIds::const_iterator lIterator = mMeshesIds.begin();
		TMeshesIds::const_iterator lIteratorEnd = mMeshesIds.end();
		while (lIterator != lIteratorEnd && lIterator->second->mId != aMesh->mId)
		{
			++lIterator;
		}
		if (--lIterator->second->mReferences == 0)
		{
			mLoadedMeshes[aMesh->mId] = 0;
			glDeleteBuffers(1, &aMesh->mVBO);

			mMeshesIds.erase(lIterator);
			--mNumLoadedMeshes;
		}
		aMesh->Release();
		delete aMesh;
	}
	void RenderManager::RenderMesh(const Vector3D<float32>* aPosition, const Mesh* aMesh, Material* mMaterial)
	{
		Matrix4 lModelMatrix;
		lModelMatrix = Matrix4x4::translate(&lModelMatrix, aPosition);

		mMaterial->PrepareToRender(&lModelMatrix);
		//@TODO: if is the same material only need to asign these attrib. one time
		mMaterial->SetMatrix4("view", &mRenderCamera->mViewMatrix);
		mMaterial->SetMatrix4("proj", &mRenderCamera->mProjMatrix);
		if (mMaterial->mTextureId > -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mLoadedTextures[mMaterial->mTextureId]);
			glUniform1i(mMaterial->mTextureParam, 0);
		}

		glDrawArrays(GL_TRIANGLES, 0, 36);		
	}

	//-----------------------------------------END MESHES-----------------------------------------

	Camera* RenderManager::CreatePerspectiveCamera(const Vector3D<float32>* aEye, const Vector3D<float32>* aPosition, const Vector3D<float32>* aUp,
																			float32 aFov, float32 aAspect, float32 aNear, float32 aFar)
	{
		Camera* lResult = new Camera();
		lResult->Init(ePerspective);
		lResult->Perspective(aFov, aAspect, aNear, aFar);
		lResult->LookAt(aEye, aPosition, aUp);

		return lResult;
	}

	void RenderManager::SetRenderCamera(const Camera* aCamera)
	{
		mRenderCamera = aCamera;
	}

} // namespace graphics

