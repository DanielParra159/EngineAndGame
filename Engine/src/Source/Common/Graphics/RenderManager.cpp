#include "Graphics/RenderManager.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/Camera.h"

#include "Support/Matrix4.h"
#include "Support/Math.h"

#include "System/Time.h"

#include "IO/FileSystem.h"
#include "IO/File.h"

#include "Core/Log.h"
#include "Logic/ComponentFactory.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include "SDL.h"
#include <SDL_opengl.h>
#include <SOIL.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

		if (mRenderer == NULL)
			return FALSE;

		mClearColor = aClearColor;
		/*SDL_SetRenderDrawColor(mRenderer,
							   (uint32)(aClearColor.mR * 255),
							   (uint32)(aClearColor.mG * 255),
							   (uint32)(aClearColor.mB * 255),
							   (uint32)(aClearColor.mA * 255));*/

		return TRUE;
	}

	void RenderManager::Release()
	{
		LOOP_ITERATOR(TMeshesIds::iterator, mMeshesIds, lIterator, lEndElement) {
			glDeleteBuffers(1, &lIterator->second->mMesh->mVBO);
			lIterator->second->mMesh->Release();
			delete lIterator->second->mMesh;
			delete lIterator->second;
		}
		mMeshesIds.clear();
		LOOP_ITERATOR(TLoadedMeshes::iterator, mLoadedMeshes, lIterator, lEndElement) {
			(*lIterator)->Release();
			delete (*lIterator);
		}
		mLoadedMeshes.clear();


		LOOP_ITERATOR(TLoadedMaterials::iterator, mLoadedMaterials, lIterator, lEndElement)
		{
			(*lIterator)->Release();
			glDetachShader((*lIterator)->mProgramShader, (*lIterator)->mVertexShader->mId);
			glDetachShader((*lIterator)->mProgramShader, (*lIterator)->mFragmentShader->mId);
			glDeleteProgram((*lIterator)->mProgramShader);
			delete (*lIterator);
		}

		mLoadedMaterials.clear();

		LOOP_ITERATOR(TShaderIds::const_iterator, mLoadedVertexShaders, lIterator, lEndElement)
		{
			lIterator->second->Release();
			delete lIterator->second;
		}

		mLoadedVertexShaders.clear();

		LOOP_ITERATOR(TShaderIds::const_iterator, mLoadedFragmentShaders, lIterator, lEndElement)
		{
			lIterator->second->Release();
			delete lIterator->second;
		}
		mLoadedFragmentShaders.clear();

		LOOP_ITERATOR(TTexturesIds::const_iterator, mLoadedTextures, lIterator, lEndElement)
		{
			lIterator->second->Release();
			delete lIterator->second;
		}
		//mLoadedTexturesOLD.clear();
		mLoadedTextures.clear();

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

	void RenderManager::RenderSprite(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation, const Sprite* aSprite)
	{
		
	}

	void RenderManager::UnloadTexture(const Texture* aTexture)
	{
		assert(aTexture != NULL && aTexture->mId >= 0);

		LOOP_ITERATOR(TTexturesIds::const_iterator, mLoadedTextures, lIterator, lEndElement)
		{
			if (lIterator->second->mId == aTexture->mId)
			{
				if (lIterator->second->RemoveReference() == 0)
				{
					//mLoadedTexturesOLD.erase(lIterator->second);
					lIterator->second->Release();
					delete lIterator->second;


					mLoadedTextures.erase(lIterator);
				}
				break;
			}
		}
	}

	const Texture* RenderManager::LoadTexture(const std::string& aFileName, eTextureFormats aFormat)
	{
		Texture* lTexture = NULL;
		TTexturesIds::const_iterator lTextureIterator = mLoadedTextures.find(aFileName);

		if (lTextureIterator != mLoadedTextures.end())
		{
			lTextureIterator->second->AddReference();
			return lTextureIterator->second;
		}


		std::string lTexturePath = io::FileSystem::Instance()->GetCurrentDir() + "\\" + aFileName;

		lTexture = new Texture();

		if (lTexture->Init(lTexturePath, aFormat))
		{
			//mLoadedTexturesOLD.insert(lTexture);
			mLoadedTextures[aFileName] = lTexture;
		}
		else
		{
			delete lTexture;
			lTexture = NULL;
			core::LogFormatString("Can't load image %s", aFileName.c_str());
		}

		return lTexture;
	}

	Sprite* RenderManager::CreateSprite(const std::string& aFileName, eTextureFormats aFormat)
	{
		Sprite *lResult = NULL;

		/*const Texture* lTexture = LoadTexture(aFileName, aFormat);
		if (lTexture != NULL)
		{
			lResult = new Sprite();
			lResult->Init(lTexture);
		}
		else {
			core::LogFormatString("Can\'t load texture %s\n", aFileName);
		}*/

		return lResult;
	}

	void RenderManager::DeleteSprite(Sprite* aSprite)
	{
		/*aSprite->Release();
		delete aSprite;
		aSprite = NULL;*/
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

	const Shader* RenderManager::LoadVertexShader(const std::string& aMaterialFileName, const std::string& aVertexShaderName)
	{
		TShaderIds::const_iterator lShaderIterator = mLoadedVertexShaders.find(aVertexShaderName);
		Shader* lShader = NULL;

		if (lShaderIterator != mLoadedVertexShaders.end())
		{
			lShaderIterator->second->AddReference();
			return lShaderIterator->second;
		}
		else {
			io::File lFileAux = io::File();
			if (!lFileAux.Open(aVertexShaderName + ".glvs"))
			{
				core::LogFormatString("Can't open vertex shader %s", (aVertexShaderName + ".glvs").c_str());
				return NULL;
			}
			uint32 lFileSize = lFileAux.GetSize();

			std::string lBuffer = std::string(lFileSize, ' ');

			if (!lFileAux.Read(&lBuffer[0], sizeof(int8), lFileSize))
			{
				core::LogFormatString("Can't read vertex shader %s", (aVertexShaderName + ".glvs").c_str());
				return NULL;
			}
			lFileAux.Close();

			lShader = new Shader();
			if (lShader->Init(aVertexShaderName, EShaderTypes::eVertex, lBuffer.c_str())) {
				mLoadedVertexShaders[aVertexShaderName] = lShader;
			}
			else {
				int8 lBuffer[512];
				glGetShaderInfoLog(lShader->mId, 512, NULL, lBuffer);
				core::LogFormatString("%s", lBuffer);
				core::LogFormatString("Can't compile vertex shader %s", aVertexShaderName.c_str());
				delete lShader;
				lShader = NULL;
			}
		}
		return lShader;
	}

	const Shader* RenderManager::LoadFragmentShader(const std::string& aMaterialFileName, const std::string& aFragmentShaderName)
	{
		Shader* lShader = NULL;
		TShaderIds::const_iterator lShaderIterator = mLoadedFragmentShaders.find(aFragmentShaderName);
		if (lShaderIterator != mLoadedFragmentShaders.end())
		{
			lShaderIterator->second->AddReference();
			return lShaderIterator->second;
		}
		else
		{
			io::File lFileAux = io::File();
			if (!lFileAux.Open(aFragmentShaderName + ".glfs"))
			{
				core::LogFormatString("Can't open fragment shader %s", (aFragmentShaderName + ".glfs").c_str());
				return NULL;
			}
			uint32 lFileSize = lFileAux.GetSize();

			std::string lBuffer = std::string(lFileSize, ' ');

			if (!lFileAux.Read(&lBuffer[0], sizeof(int8), lFileSize))
			{
				core::LogFormatString("Can't read fragment shader %s", (aFragmentShaderName + ".glfs").c_str());
				return NULL;
			}
			lFileAux.Close();

			lShader = new Shader();
			if (lShader->Init(aFragmentShaderName, EShaderTypes::eFragment, lBuffer.c_str())) {
				mLoadedFragmentShaders[aFragmentShaderName] = lShader;
			}
			else {
				int8 lBuffer[512];
				glGetShaderInfoLog(lShader->mId, 512, NULL, lBuffer);
				core::LogFormatString("%s", lBuffer);
				core::LogFormatString("Can't compile fragment shader %s", aFragmentShaderName.c_str());
				delete lShader;
				lShader = NULL;
			}
		}

		return lShader;
	}

	Material* RenderManager::CreateMaterial(const std::string& aMaterialName, const std::string& aTextureName, 
		const Shader* aVertexShader, const Shader* aFragmentShader, BOOL aTransparency)
	{
		int32 lShaderPorgram = glCreateProgram();
		glAttachShader(lShaderPorgram, aVertexShader->mId);
		glAttachShader(lShaderPorgram, aFragmentShader->mId);
		glBindFragDataLocation(lShaderPorgram, 0, "outColor");
		glLinkProgram(lShaderPorgram);
		glUseProgram(lShaderPorgram);

		Material* lResult = new Material();
		lResult->Init(aMaterialName, aVertexShader, aFragmentShader, lShaderPorgram);

		mLoadedMaterials.insert(lResult);

		lResult->mDiffuseTexture = LoadTexture(aTextureName, aTransparency ? eTextureFormats::eRGBA : eTextureFormats::eRGB);

		return lResult;
	}

	Material* RenderManager::LoadMaterial(const std::string& aFileName)
	{
		std::string lMaterialName, lTextureName, lVertexShaderName, lFragmentShaderName;
		if (!ParseMaterial(aFileName, lMaterialName, lTextureName, lVertexShaderName, lFragmentShaderName))
			return NULL;

		const Shader* lVertexShader = NULL;
		if ((lVertexShader = LoadVertexShader(aFileName, lVertexShaderName)) == NULL)
			return NULL;

		const Shader* lFragmentShader = NULL;
		if ((lFragmentShader = LoadFragmentShader(aFileName, lFragmentShaderName)) == NULL)
			return NULL;

		BOOL lTransparency = FALSE; //@TODO read from material
		return CreateMaterial(lMaterialName, lTextureName, lVertexShader, lFragmentShader, lTransparency ? eTextureFormats::eRGBA : eTextureFormats::eRGB);
	}
	void RenderManager::UnloadMaterial(Material* aMaterial)
	{
		glDetachShader(aMaterial->mProgramShader, aMaterial->mVertexShader->mId);
		
		LOOP_ITERATOR(TShaderIds::const_iterator, mLoadedVertexShaders, lIterator, lEndElement)
		{
			if (lIterator->second->mId == aMaterial->mVertexShader->mId)
			{
				if (lIterator->second->RemoveReference() == 0)
				{
					lIterator->second->Release();
					delete lIterator->second;
					mLoadedVertexShaders.erase(lIterator);
				}
				break;
			}
		}

		glDetachShader(aMaterial->mProgramShader, aMaterial->mFragmentShader->mId);
		LOOP_ITERATOR(TShaderIds::const_iterator, mLoadedFragmentShaders, lIterator, lEndElement)
		{
			if (lIterator->second->mId == aMaterial->mFragmentShader->mId)
			{
				if (lIterator->second->RemoveReference() == 0)
				{
					lIterator->second->Release();
					delete lIterator->second;
					mLoadedFragmentShaders.erase(lIterator);
				}
				break;
			}
		}

		glDeleteProgram(aMaterial->mProgramShader);

		mLoadedMaterials.erase(aMaterial);
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
			Mesh* lMesh = (Mesh*)lMeshIterator->second->mMesh->CreateInstance();
			lMeshIterator->second->AddReference();
			mLoadedMeshes.insert(lMesh);
			return lMesh;
		}

		const struct aiScene* scene = aiImportFile((io::FileSystem::Instance()->GetCurrentDir() + "\\" + aFileName).c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
		if (scene == NULL)
		{
			core::LogFormatString("Can't load %s mesh", (io::FileSystem::Instance()->GetCurrentDir() + "\\" + aFileName).c_str());
			return NULL;
		}

		float32* lVertexData;
		uint32 lNumVertices = 0;
		uint32 lNumFaces = 0;
		for (uint32 n = 0; n < scene->mRootNode->mNumChildren; ++n) {
			for (uint32 m = 0; m < scene->mRootNode->mChildren[n]->mNumMeshes; ++m) {
				const struct aiMesh* mesh = scene->mMeshes[scene->mRootNode->mChildren[n]->mMeshes[m]];
				lNumFaces = mesh->mNumFaces;
				int32 lDataIndex = 0;
				lVertexData = new float32[lNumFaces *3 * 8];
				for (uint32 i = 0; i < lNumFaces; ++i)
				{
					const struct aiFace* face = &mesh->mFaces[i];
					for (uint32 j = 0; j < face->mNumIndices; j++) {
						lNumVertices += 1;
						uint32 lVertexIndex = face->mIndices[j];
						lVertexData[lDataIndex] = mesh->mVertices[lVertexIndex].x;
						lVertexData[lDataIndex + 1] = mesh->mVertices[lVertexIndex].y;
						lVertexData[lDataIndex + 2] = mesh->mVertices[lVertexIndex].z;
						lVertexData[lDataIndex + 3] = mesh->mNormals[lVertexIndex].x;
						lVertexData[lDataIndex + 4] = mesh->mNormals[lVertexIndex].y;
						lVertexData[lDataIndex + 5] = mesh->mNormals[lVertexIndex].z;
						lVertexData[lDataIndex + 6] = mesh->mTextureCoords[0][lVertexIndex].x;
						lVertexData[lDataIndex + 7] = mesh->mTextureCoords[0][lVertexIndex].y;
						lDataIndex += 8;
					}
				}
			}
		}

		aiReleaseImport(scene);
		
		return LoadMesh(aFileName, lVertexData, sizeof(float32)*lNumFaces*3*8, lNumVertices);
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
			Mesh* lMesh = (Mesh*)lMeshIterator->second->mMesh->CreateInstance();
			lMeshIterator->second->AddReference();
			mLoadedMeshes.insert(lMesh);
			return lMesh;
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

			std::string lMeshPath = io::FileSystem::Instance()->GetCurrentDir() + "\\" + aMeshName;
			lResult->Init(aMeshName, lVBO, 0, aVertexData, aVertexDataLength, 0, lTextureCoords, aNumVertex);
			mMeshesIds[aMeshName] = new MeshReferences(lResult);
		}
		else
		{
			core::LogFormatString("Can't load mesh %s", aMeshName.c_str());
		}

		return lResult == NULL ? NULL : (Mesh*)lResult->CreateInstance();
	}

	void RenderManager::UnloadMesh(Mesh* aMesh, BOOL aPermanent)
	{
		MeshReferences* lMeshReferences = mMeshesIds[aMesh->mName];
		TLoadedMeshes::const_iterator lMeshIterator = mLoadedMeshes.find(aMesh);
		if (lMeshIterator != mLoadedMeshes.end()) {
			// Is an instance
			mLoadedMeshes.erase(aMesh);
			aMesh->Release();
			delete aMesh;
			if (lMeshReferences->RemoveReference() == 0 && aPermanent) {
				glDeleteBuffers(1, &lMeshReferences->mMesh->mVBO);
				mMeshesIds.erase(lMeshReferences->mMesh->mName);
				lMeshReferences->mMesh->Release();
				delete lMeshReferences->mMesh;
				delete lMeshReferences;
			}
		}
		else {
			// "Original" mesh
			if (lMeshReferences->RemoveReference() == 0 && aPermanent) {
				glDeleteBuffers(1, &aMesh->mVBO);
				delete lMeshReferences;
				mMeshesIds.erase(aMesh->mName);
				aMesh->Release();
				delete aMesh;
			}
			else {
				aMesh->Release();
				delete aMesh;
			}
		}
	}
	void RenderManager::RenderMesh(const Vector3D<float32>* aPosition, const Vector3D<float32>* aScale, const Vector3D<float32>* aRotation, const Mesh* aMesh)
	{
		Matrix4 lModelMatrix;
		Matrix4x4::translate(&lModelMatrix, aPosition);
		Matrix4x4::rotate(&lModelMatrix, aRotation);
		Matrix4x4::scale(&lModelMatrix, aScale);


		static float32 lLihgtPosX = 0.0f;
		static int32 lSign = 1;
		lLihgtPosX += sys::Time::GetDeltaSec() * lSign *4;
		if (Math::Abs(lLihgtPosX) > 30.0f)
			lSign *= -1;

		aMesh->mMaterial->PrepareToRender(&lModelMatrix, mRenderCamera->GetCameraPosition(), Vector3D<float32>(1.0f, 1.0f, 1.0f), Vector3D<float32>(lLihgtPosX, 8.0f, 3.0f));
		aMesh->mMaterial->SetVertexFloatAttribPointer("position", 3, FALSE, 8, 0, aMesh->mVBO);
		aMesh->mMaterial->SetVertexFloatAttribPointer("normal", 3, FALSE, 8, 3, aMesh->mVBO);
		aMesh->mMaterial->SetVertexFloatAttribPointer("texcoord", 2, FALSE, 8, 6, aMesh->mVBO);
		//@TODO: if is the same material only need to asign these attrib. one time
		aMesh->mMaterial->SetMatrix4("view", &mRenderCamera->mViewMatrix);
		aMesh->mMaterial->SetMatrix4("proj", &mRenderCamera->mProjMatrix);
		if (aMesh->mMaterial->mDiffuseTexture != NULL)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, aMesh->mMaterial->mDiffuseTexture->mId);
			//glUniform1i(mMaterial->mTextureParam, 0);
		}
		if (aMesh->mMaterial->mNormalTexture != NULL)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, aMesh->mMaterial->mNormalTexture->mId);
			//glUniform1i(mMaterial->mTextureParam, 0);
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

