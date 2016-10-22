#include "Graphics/RenderManager.h"
#include "Graphics/Sprite.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/Camera.h"

#include "Support/Matrix4.h"

#include "IO/FileSystem.h"
#include "IO/File.h"

#include "Core/Log.h"
#include "Logic/ComponentFactory.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include "SDL.h"
#include <SDL_opengl.h>
#include <SOIL.h>

namespace graphics
{
	SINGLETON_BODY(RenderManager);


	BOOL RenderManager::Init(const int8* aWindowsTitle, const Vector2D<uint32> &aWindowsSize, const Vector2D<uint32> &aWindowsPosition, const Color& aClearColor, BOOL aFullscreen)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return FALSE;

		mWindow = SDL_CreateWindow(aWindowsTitle,
								   EXPOSE_VECTOR2D(aWindowsPosition),
								   EXPOSE_VECTOR2D(aWindowsSize),
								   SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
								   //aFullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN); @TODO

		if (mWindow == NULL)
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

		if (mRenderer == NULL)
			return FALSE;

		mClearColor = aClearColor;
		/*SDL_SetRenderDrawColor(mRenderer,
							   (uint32)(aClearColor.mR * 255),
							   (uint32)(aClearColor.mG * 255),
							   (uint32)(aClearColor.mB * 255),
							   (uint32)(aClearColor.mA * 255));*/


		mNumLoadedMeshes = 0;
		mNumLoadedFragmentShaders = 0;
		mNumLoadedVertexShaders = 0;
		mNumLoadedMaterials = 0;
		mNumLoadedMeshes = 0;

		return TRUE;
	}

	void RenderManager::Release()
	{
		int32 size = mLoadedMeshes.size();
		for (int i=0; i < size; ++i)
		{
			if (mLoadedMeshes[i] == NULL)
				continue;
			Mesh* lMesh = mLoadedMeshes[i];
			lMesh->Release();
			glDeleteBuffers(1, &lMesh->mVBO);
			delete lMesh;
		}
		mLoadedMeshes.clear();
		mMeshesIds.clear();
		mNumLoadedMeshes = 0;


		size = mLoadedMaterials.size();
		for (int i = 0; i < size; ++i)
		{
			if (mLoadedMaterials[i] == NULL)
				continue;
			Material* lMaterial = mLoadedMaterials[i];
			lMaterial->Release();
			
			glDetachShader(lMaterial->mProgramShader, mLoadedVertexShaders[lMaterial->mVertexShaderId]);
			glDetachShader(lMaterial->mProgramShader, mLoadedFragmentShaders[lMaterial->mFragmentShaderId]);
			glDeleteProgram(lMaterial->mProgramShader);
			delete lMaterial;
		}
		mLoadedMaterials.clear();
		mNumLoadedMaterials = 0;

		size = mLoadedVertexShaders.size();
		for (int i = 0; i < size; ++i)
		{
			glDeleteShader(mLoadedVertexShaders[i]);
		}
		mLoadedVertexShaders.clear();
		mVertexShaderIds.clear();
		mNumLoadedVertexShaders = 0;

		size = mLoadedFragmentShaders.size();
		for (int i = 0; i < size; ++i)
		{
			glDeleteShader(mLoadedFragmentShaders[i]);
		}
		mLoadedFragmentShaders.clear();
		mFragmentShaderIds.clear();
		mNumLoadedFragmentShaders = 0;

		TLoadedTextures::const_iterator lTexturesIterator;
		TLoadedTextures::const_iterator lTexturesEndElement = mLoadedTextures.end();
		for (lTexturesIterator = mLoadedTextures.begin(); lTexturesIterator != lTexturesEndElement; ++lTexturesIterator)
		{
			uint32 lTexture = *lTexturesIterator;
			glDeleteTextures(1, &lTexture);
		}
		mLoadedTextures.clear();
		mTexturesIds.clear();
		mNumLoadedTextures = 0;

		SDL_GL_DeleteContext(mContext);
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
	}

	void RenderManager::BeginRender()
	{
		// Clear the screen to black
		glClearColor(EXPOSE_COLOR_RGBA(mClearColor));
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
		RenderTexture(aId, aSrcRect, EXPOSE_VECTOR2D(aPosition), EXPOSE_VECTOR2D(aSize), aAngle);
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

		int32 lWidth, lHeight;
		uint8* lImage;

		glBindTexture(GL_TEXTURE_2D, lTextureId);
		lImage = SOIL_load_image((io::FileSystem::Instance()->GetCurrentDir() + "\\" + aFileName).c_str(), &lWidth, &lHeight, 0, SOIL_LOAD_RGB);

		if (lImage != NULL)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lWidth, lHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, lImage);
			SOIL_free_image_data(lImage);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			uint32 lCapacity = mLoadedTextures.capacity();
			lResult = NULL;
			if (mNumLoadedTextures == lCapacity)
			{
				mLoadedTextures.push_back(lTextureId);
				lResult = mNumLoadedTextures;
			} 
			else 
			{
				int32 lSize = mLoadedTextures.size();
				
				while (lResult < lSize && mLoadedTextures[lResult] != NULL)
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
		Sprite *lResult = NULL;

		int32 lTextureId = LoadTexture(aFileName);
		if (lTextureId > -1)
		{
			lResult = new Sprite();
			lResult->Init(lTextureId);
		}
		else {
			core::LogFormatString("Can\'t load texture %s\n", aFileName);
		}

		return lResult;
	}

	void RenderManager::DeleteSprite(Sprite* aSprite)
	{
		aSprite->Release();
		delete aSprite;
		aSprite = NULL;
	}


	//-----------------------------------------MATERIALS-----------------------------------------

	BOOL RenderManager::ParseMaterial(const std::string& aFileName, std::string& aMaterialName, 
									  std::string& aTextureName, std::string& aVertexShaderName, std::string& aFragmentShaderName)
	{
		io::File lFileAux = io::File();
		if (!lFileAux.Open(aFileName + ".material"))
		{
			core::LogFormatString("Can't open material %s", aFileName.c_str());
			return FALSE;
		}
		uint32 lFileSize = lFileAux.GetSize();
		std::string lBuffer(lFileSize, ' ');

		if (!lFileAux.Read(&lBuffer[0], sizeof(int8), lFileSize))
		{
			core::LogFormatString("Can't read material %s", aFileName.c_str());
			return FALSE;
		}
		lFileAux.Close();

		int32 lIndex = lBuffer.find("{");
		aMaterialName = lBuffer.substr(9, lIndex - 11).c_str();
		lIndex = lBuffer.find("texture");
		int32 lIndex2 = lBuffer.find(";", lIndex);
		aTextureName = lBuffer.substr(lIndex + 8, lIndex2 - (lIndex + 8)).c_str();
		lIndex = lBuffer.find("vertexShader");
		lIndex2 = lBuffer.find(";", lIndex);
		aVertexShaderName = lBuffer.substr(lIndex + 13, lIndex2 - (lIndex + 13)).c_str();
		lIndex = lBuffer.find("fragmentProgram");
		lIndex2 = lBuffer.find(";", lIndex);
		aFragmentShaderName = lBuffer.substr(lIndex + 16, lIndex2 - (lIndex + 16)).c_str();

		return TRUE;
	}

	BOOL RenderManager::LoadVertexShader(const std::string& aMaterialFileName, const std::string& aVertexShaderName, int32& aVertexShader, int32& aVertexShaderId)
	{
		TShaderIds::const_iterator lShaderIterator = mVertexShaderIds.find(aVertexShaderName);

		if (lShaderIterator != mVertexShaderIds.end())
		{
			aVertexShaderId = lShaderIterator->second->mId;
			aVertexShader = mLoadedVertexShaders[lShaderIterator->second->mId];
			++lShaderIterator->second->mReferences;
		}
		else {
			io::File lFileAux = io::File();
			if (!lFileAux.Open(aVertexShaderName + ".glvs"))
			{
				core::LogFormatString("Can't open vertex shader %s", (aVertexShaderName + ".glvs").c_str());
				return FALSE;
			}
			uint32 lFileSize = lFileAux.GetSize();

			std::string lBuffer = std::string(lFileSize, ' ');

			if (!lFileAux.Read(&lBuffer[0], sizeof(int8), lFileSize))
			{
				core::LogFormatString("Can't read vertex shader %s", (aVertexShaderName + ".glvs").c_str());
				return -1;
			}
			lFileAux.Close();
			const int8* aVertexSource = lBuffer.c_str();
			aVertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(aVertexShader, 1, &aVertexSource, NULL);
			glCompileShader(aVertexShader);

			int32 lStatus;
			glGetShaderiv(aVertexShader, GL_COMPILE_STATUS, &lStatus);
			if (lStatus == FALSE)
			{
				int8 lBuffer[512];
				glGetShaderInfoLog(aVertexShader, 512, NULL, lBuffer);
				core::LogFormatString("%s", lBuffer);
				core::LogFormatString("Can't compile vertex shader %s", aMaterialFileName.c_str());
				return FALSE;
			}

			uint32 lCapacity = mLoadedVertexShaders.capacity();
			if (mNumLoadedVertexShaders == lCapacity)
			{
				mLoadedVertexShaders.push_back(aVertexShader);
				aVertexShaderId = mNumLoadedVertexShaders;
			}
			else
			{
				int32 lSize = mLoadedVertexShaders.size();

				while (aVertexShaderId < lSize && mLoadedVertexShaders[aVertexShaderId] != NULL)
				{
					++aVertexShaderId;
				}

				if (aVertexShaderId < lSize)
				{
					mLoadedVertexShaders[aVertexShaderId] = aVertexShader;
				}
				else
				{
					mLoadedVertexShaders.push_back(aVertexShader);
				}
			}
			mVertexShaderIds[aVertexShaderName] = new IdReferences(aVertexShaderId, 1);
			++mNumLoadedVertexShaders;
		}
		return TRUE;
	}

	BOOL RenderManager::LoadFragmentShader(const std::string& aMaterialFileName, const std::string& aFragmentShaderName, int32& aFragmentShader, int32& aFragmentShaderId)
	{

		TShaderIds::const_iterator lShaderIterator = mFragmentShaderIds.find(aFragmentShaderName);
		if (lShaderIterator != mFragmentShaderIds.end())
		{
			aFragmentShaderId = lShaderIterator->second->mId;
			aFragmentShader = mLoadedFragmentShaders[lShaderIterator->second->mId];
			++lShaderIterator->second->mReferences;
		}
		else
		{
			io::File lFileAux = io::File();
			if (!lFileAux.Open(aFragmentShaderName + ".glfs"))
			{
				core::LogFormatString("Can't open fragment shader %s", (aFragmentShaderName + ".glfs").c_str());
				return FALSE;
			}
			uint32 lFileSize = lFileAux.GetSize();

			std::string lBuffer = std::string(lFileSize, ' ');

			if (!lFileAux.Read(&lBuffer[0], sizeof(int8), lFileSize))
			{
				core::LogFormatString("Can't read fragment shader %s", (aFragmentShaderName + ".glfs").c_str());
				return FALSE;
			}
			lFileAux.Close();

			const int8* aFragmentSource = lBuffer.c_str();
			aFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(aFragmentShader, 1, &aFragmentSource, NULL);
			glCompileShader(aFragmentShader);

			int32 lStatus;
			glGetShaderiv(aFragmentShader, GL_COMPILE_STATUS, &lStatus);

			if (lStatus == FALSE)
			{
				int8 lBuffer[512];
				glGetShaderInfoLog(aFragmentShader, 512, NULL, lBuffer);
				core::LogFormatString("%s", lBuffer);
				core::LogFormatString("Can't compile fragment shader %s", aFragmentShaderName.c_str());
				return FALSE;
			}

			uint32 lCapacity = mLoadedFragmentShaders.capacity();
			if (mNumLoadedFragmentShaders == lCapacity)
			{
				mLoadedFragmentShaders.push_back(aFragmentShader);
				aFragmentShaderId = mNumLoadedFragmentShaders;
			}
			else
			{
				int32 lSize = mLoadedFragmentShaders.size();

				while (aFragmentShaderId < lSize && mLoadedFragmentShaders[aFragmentShaderId] != NULL)
				{
					++aFragmentShaderId;
				}

				if (aFragmentShaderId < lSize)
				{
					mLoadedFragmentShaders[aFragmentShaderId] = aFragmentShader;
				}
				else
				{
					mLoadedFragmentShaders.push_back(aFragmentShader);
				}
			}
			mFragmentShaderIds[aFragmentShaderName] = new IdReferences(aFragmentShaderId, 1);
			++mNumLoadedFragmentShaders;
		}

		return TRUE;
	}

	Material* RenderManager::CreateMaterial(const std::string& aMaterialName, const std::string& aTextureName, int32 aVertexShader, int32 aVertexShaderId, int32 aFragmentShader, int32 aFragmentShaderId)
	{
		int32 lShaderPorgram = glCreateProgram();
		glAttachShader(lShaderPorgram, aVertexShader);
		glAttachShader(lShaderPorgram, aFragmentShader);
		glBindFragDataLocation(lShaderPorgram, 0, "outColor");
		glLinkProgram(lShaderPorgram);
		glUseProgram(lShaderPorgram);

		Material* lResult = new Material();
		lResult->Init(aMaterialName, aVertexShaderId, aFragmentShaderId, lShaderPorgram);

		uint32 lCapacity = mLoadedMaterials.capacity();
		int32 lMaterialId = 0;
		if (mNumLoadedMaterials == lCapacity)
		{
			mLoadedMaterials.push_back(lResult);
			lMaterialId = lCapacity;
		}
		else
		{
			int32 lSize = mLoadedMaterials.size();

			while (lMaterialId < lSize && mLoadedMaterials[lMaterialId] != NULL)
			{
				++lMaterialId;
			}

			if (lMaterialId < lSize)
			{
				mLoadedMaterials[lMaterialId] = lResult;
			}
			else
			{
				mLoadedMaterials.push_back(lResult);
			}
		}

		++mNumLoadedMaterials;
		lResult->mId = lMaterialId;

		lResult->mTextureId = LoadTexture(aTextureName);

		return lResult;
	}

	Material* RenderManager::LoadMaterial(const std::string& aFileName)
	{
		std::string lMaterialName, lTextureName, lVertexShaderName, lFragmentShaderName;
		if (!ParseMaterial(aFileName, lMaterialName, lTextureName, lVertexShaderName, lFragmentShaderName))
			return NULL;

		int32 lVertexShader = -1;
		int32 lVertexShaderId = 0;
		if (!LoadVertexShader(aFileName, lVertexShaderName, lVertexShader, lVertexShaderId))
			return NULL;

		
		int32 lFragmentShader = -1;
		int32 lFragmentShaderId = 0;
		if (!LoadFragmentShader(aFileName, lFragmentShaderName, lFragmentShader, lFragmentShaderId))
			return NULL;

		return CreateMaterial(lMaterialName, lTextureName, lVertexShader, lVertexShaderId, lFragmentShader, lFragmentShaderId);
	}
	void RenderManager::UnloadMaterial(Material* aMaterial)
	{
		int32 lVertexShader = mLoadedVertexShaders[aMaterial->mVertexShaderId];
		glDetachShader(aMaterial->mProgramShader, lVertexShader);
		

		TShaderIds::const_iterator lIterator = mVertexShaderIds.begin();
		TShaderIds::const_iterator lIteratorEnd = mVertexShaderIds.end();
		while (lIterator != lIteratorEnd && lIterator->second->mId != aMaterial->mVertexShaderId)
		{
			++lIterator;
		}
		if (--lIterator->second->mReferences == 0)
		{
			mLoadedVertexShaders[aMaterial->mVertexShaderId] = NULL;
			mVertexShaderIds.erase(lIterator);
			--mNumLoadedVertexShaders;
			glDeleteShader(lVertexShader);
		}

		int32 lFragmentShader = mLoadedFragmentShaders[aMaterial->mFragmentShaderId];
		glDetachShader(aMaterial->mProgramShader, lFragmentShader);
		lIterator = mFragmentShaderIds.begin();
		lIteratorEnd = mFragmentShaderIds.end();
		while (lIterator != lIteratorEnd && lIterator->second->mId != aMaterial->mFragmentShaderId)
		{
			++lIterator;
		}
		if (--lIterator->second->mReferences == 0)
		{
			mLoadedFragmentShaders[aMaterial->mFragmentShaderId] = NULL;
			mFragmentShaderIds.erase(lIterator);
			--mNumLoadedFragmentShaders;
			glDeleteShader(lFragmentShader);
		}

		glDeleteProgram(aMaterial->mProgramShader);


		TLoadedMaterials::const_iterator lMaterialIterator = mLoadedMaterials.begin();
		TLoadedMaterials::const_iterator lMaterialIteratorEnd = mLoadedMaterials.end();
		while (*lMaterialIterator == NULL || (lMaterialIterator != lMaterialIteratorEnd) && (*lMaterialIterator)->mId != aMaterial->mId)
		{
			++lMaterialIterator;
		}
		mLoadedMaterials[aMaterial->mId] = NULL;// .erase(lMaterialIterator);
		--mNumLoadedMaterials;
		aMaterial->Release();
		delete aMaterial;
	}
	//----------------------------------------END MATERIALS---------------------------------------

	//-----------------------------------------MESHES-----------------------------------------
	MeshComponent* RenderManager::LoadMeshComponentFromFile(const std::string& aFileName)
	{
		MeshComponent* lResult = NULL;
		Mesh* lMesh = LoadMeshFromFile(aFileName);
		if (lMesh != NULL)
		{
			lResult = (MeshComponent*)logic::ComponentFactory::Instance()->GetComponent(MeshComponent::sId);
			lResult->Init(TRUE);
			lResult->SetMesh(lMesh);
		}
		return lResult;
	}

	Mesh* RenderManager::LoadMeshFromFile(const std::string& aFileName)
	{
		TMeshesIds::const_iterator lMeshIterator = mMeshesIds.find(aFileName);

		if (lMeshIterator != mMeshesIds.end())
		{
			++lMeshIterator->second->mReferences;
			return mLoadedMeshes[lMeshIterator->second->mId]->CreateInstance();
		}

		const float32 lVertexData[] = {
			// X      Y     Z     U     V
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

			0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
			0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
		};
		
		return LoadMesh(aFileName, lVertexData, sizeof(lVertexData), 36);
	}

	MeshComponent* RenderManager::LoadMeshComponentFromVertexArray(const std::string& aMeshName, const float32* aVertexData, uint32 aVertexDataLength, uint32 aNumVertex)
	{
		MeshComponent* lResult = NULL;
		Mesh* lMesh = LoadMeshFromVertexArray(aMeshName, aVertexData, aVertexDataLength, aNumVertex);
		if (lMesh != NULL)
		{
			lResult = (MeshComponent*)logic::ComponentFactory::Instance()->GetComponent(MeshComponent::sId);
			lResult->Init(TRUE);
			lResult->SetMesh(lMesh);
		}
		return lResult;
	}

	Mesh* RenderManager::LoadMeshFromVertexArray(const std::string& aMeshName, const float32* aVertexData, uint32 aVertexDataLength, uint32 aNumVertex)
	{
		TMeshesIds::const_iterator lMeshIterator = mMeshesIds.find(aMeshName);

		if (lMeshIterator != mMeshesIds.end())
		{
			++lMeshIterator->second->mReferences;
			return mLoadedMeshes[lMeshIterator->second->mId]->CreateInstance();
		}

		return LoadMesh(aMeshName, aVertexData, aVertexDataLength, aNumVertex);
	}
	Mesh* RenderManager::LoadMesh(const std::string& aMeshName, const float32* aVertexData, uint32 aVertexDataLength, uint32 aNumVertex)
	{
		Mesh* lResult;
		float32* lTextureCoords = NULL;

		if (aVertexData != NULL /*&& lTextureCoords != NULL*/)
		{
			lResult = new Mesh();

			uint32 lVBO;
			glGenBuffers(1, &lVBO);
			glBindBuffer(GL_ARRAY_BUFFER, lVBO);
			glBufferData(GL_ARRAY_BUFFER, aVertexDataLength, aVertexData, GL_STATIC_DRAW);
			//glBufferData(GL_ARRAY_BUFFER, aVertexDataLength, lVertexData, GL_STATIC_DRAW);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(lTextureCoords), lTextureCoords, GL_STATIC_DRAW);

			lResult->Init(aMeshName, lVBO, 0, aVertexData, aVertexDataLength, 0, lTextureCoords, aNumVertex);

			uint32 lIndex = 0;
			uint32 lCapacity = mLoadedMeshes.capacity();
			if (mNumLoadedMeshes == lCapacity)
			{
				mLoadedMeshes.push_back(lResult);
				lIndex = mNumLoadedMeshes;
			}
			else
			{
				uint32 lSize = mLoadedMeshes.size();

				while (lIndex < lSize && mLoadedMeshes[lIndex] != NULL)
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

			mMeshesIds[aMeshName] = new IdReferences(lIndex, 1);
			lResult->SetId(lIndex);
			++mNumLoadedMeshes;

		}
		else
		{
			core::LogFormatString("Can't load mesh %s", aMeshName.c_str());
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
			mLoadedMeshes[aMesh->mId] = NULL;
			glDeleteBuffers(1, &aMesh->mVBO);

			mMeshesIds.erase(lIterator);
			--mNumLoadedMeshes;

			aMesh->Release();
			delete aMesh;
		}
		else {
			aMesh->Release();
		}
	}
	void RenderManager::RenderMesh(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation, const Mesh* aMesh, Material* mMaterial)
	{
		Matrix4 lModelMatrix;
		Matrix4x4::translate(&lModelMatrix, aPosition);
		Matrix4x4::rotate(&lModelMatrix, aRotation);
		Matrix4x4::scale(&lModelMatrix, aScale);

		mMaterial->PrepareToRender(&lModelMatrix);
		mMaterial->SetVertexFloatAttribPointer("position", 3, FALSE, 5, 0, aMesh->mVBO);
		mMaterial->SetVertexFloatAttribPointer("texcoord", 2, FALSE, 5, 3, aMesh->mVBO);
		//@TODO: if is the same material only need to asign these attrib. one time
		mMaterial->SetMatrix4("view", &mRenderCamera->mViewMatrix);
		mMaterial->SetMatrix4("proj", &mRenderCamera->mProjMatrix);
		if (mMaterial->mTextureId > -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mLoadedTextures[mMaterial->mTextureId]);
			glUniform1i(mMaterial->mTextureParam, 0);
		}

		glDrawArrays(GL_TRIANGLES, 0, aMesh->mNumVertex);		
	}

	//-----------------------------------------END MESHES-----------------------------------------

	Camera* RenderManager::CreatePerspectiveCamera(const Vector3D<float32>& aEye, const Vector3D<float32>& aPosition, const Vector3D<float32>& aUp,
																			float32 aFov, float32 aAspect, float32 aNear, float32 aFar)
	{
		Camera* lResult = (Camera*)logic::ComponentFactory::Instance()->GetComponent(Camera::sId);
		lResult->Init(TRUE, ePerspective);
		lResult->Perspective(aFov, aAspect, aNear, aFar);
		lResult->LookAt(aEye, aPosition, aUp);

		return lResult;
	}

	Camera* RenderManager::CreateOrthographicCamera(float32 aLeft, float32 aRight, float32 aBottom, float32 aUp, float32 aZNear, float32 aZFar)
	{
		Camera* lResult = (Camera*)logic::ComponentFactory::Instance()->GetComponent(Camera::sId);
		lResult->Init(TRUE, eOrthographic);
		lResult->Orthographic(aLeft, aRight, aBottom, aUp, aZNear, aZFar);

		return lResult;
	}

	void RenderManager::SetRenderCamera(Camera* aCamera)
	{
		mRenderCamera = aCamera;
	}

	Camera* RenderManager::GetRenderCamera()
	{
		return mRenderCamera;
	}

} // namespace graphics

