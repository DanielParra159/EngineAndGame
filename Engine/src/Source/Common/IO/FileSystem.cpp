#include "IO\FileSystem.h"

namespace io
{
	FileSystem* FileSystem::sInstance = 0;

	FileSystem* FileSystem::Instance()
	{
		if (FileSystem::sInstance == 0)
		{
			FileSystem::sInstance = new FileSystem();
			return FileSystem::sInstance;
		}
		return FileSystem::sInstance;
	}

	BOOL FileSystem::Init(const std::string& aRootDir)
	{
		mRootDir = mCurrentDir = aRootDir;

		return TRUE;
	}

	void FileSystem::Release()
	{

	}

	BOOL FileSystem::ChangeDirectory(const std::string& aDirectory)
	{
		std::string lTempCurrentDir = mCurrentDir;
		std::string lTempDir = aDirectory;
		int32 lIndex = lTempDir.find("..\\");

		if (lIndex != std::string::npos)
		{
			while (lIndex != std::string::npos)
			{
				lTempCurrentDir = lTempCurrentDir.substr(0, lTempCurrentDir.rfind("\\"));
				lTempDir = lTempDir.substr(3);
				lIndex = lTempDir.find("..\\");
			}
			if (lTempDir.length() > 0)
			{
				lTempCurrentDir += "\\"+lTempDir;
			}
		}
		else {
			lIndex = lTempDir.find(".\\");
			if (lIndex != std::string::npos)
			{
				lTempCurrentDir = mRootDir + lTempDir.substr(1);
			}
			else
			{
				lTempCurrentDir = mCurrentDir + "\\" + lTempDir;
			}
		}

		if (CheckValidDirectory(lTempCurrentDir))
		{
			mCurrentDir = lTempCurrentDir;
			return TRUE;
		}

		return FALSE;
	}

	BOOL FileSystem::CheckValidDirectory(const std::string& aDirectory)
	{
		return aDirectory.find(mRootDir) != std::string::npos;
	}
} // namespace io
