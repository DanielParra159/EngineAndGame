#ifndef _ENGINE_IO_FILESYSTEM_H_
#define _ENGINE_IO_FILESYSTEM_H_

#include "Defs.h"
#include "Types.h"

#include <string>

namespace core
{
	class Game;
}

namespace io
{
	/**
	This class manages the directories where the files are read.
	It can browse directories with relative paths and absoluas.
	*/
	class FileSystem
	{
		friend class core::Game;
		SINGLETON_HEAD(FileSystem);
	private:
		std::string										mCurrentDir;
		std::string										mRootDir;

	public:
		/**
		Changes the current directory to new absolute or relative directory
		@param aDirectory, new directory in absolute or relative path
		@return TRUE if new directory is valid
		*/
		BOOL											ChangeDirectory(const std::string& aDirectory);
		/**
		Gets the current directory
		@return Current directory
		*/
		const std::string&								GetCurrentDir() { return mCurrentDir;	}

	private:
		FileSystem() {}
		~FileSystem() {}

		BOOL											Init(const std::string& aRootDir);
		void											Release();

		BOOL											CheckValidDirectory(const std::string& aDirectory);
	}; // FileSystem
} // namespace io
#endif // _ENGINE_IO_FILESYSTEM_H_
