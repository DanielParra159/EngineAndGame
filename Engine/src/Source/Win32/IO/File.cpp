#define _CRT_SECURE_NO_WARNINGS
#include "IO/File.h"
#include "IO/FileSystem.h"

#include  <stdio.h>

namespace io
{
	BOOL File::Open(const std::string& aName, eOpenModes aOpenMode)
	{
		//@TODO add more modes
		mFileData = fopen((FileSystem::Instance()->GetCurrentDir()+"\\"+aName).c_str(), aOpenMode == eRead ? "rb" : "wb");
		mOpen = mFileData != 0;

		return mOpen;
	}

	void File::Close()
	{
		fclose((FILE*)mFileData);
		mOpen = FALSE;
	}
	void File::Seek(uint32 aOffset, eSeekDir aSeekDir)
	{
		fseek((FILE*)mFileData, aOffset, aSeekDir);
	}

	void File::Seek(uint32 aPosition)
	{
		fseek((FILE*)mFileData, aPosition, eBegin);
	}

	BOOL File::Read(void *aBuffer, uint32 aSize, uint32 aCount)
	{
		uint32 lResult = fread(aBuffer, aSize, aCount, (FILE*)mFileData);
		return lResult == aCount;
	}

	uint32 File::GetSize() const
	{
		uint32 lCurrentPosition = ftell((FILE*)mFileData);
		fseek((FILE*)mFileData, 0, eEnd);
		uint32 lSize = ftell((FILE*)mFileData);
		fseek((FILE*)mFileData, lCurrentPosition, eBegin);

		return lSize;
	}

	uint32 File::GetPosition() const
	{
		return ftell((FILE*)mFileData);
	}

	BOOL File::EndOfFile() const
	{
		return GetPosition() == GetSize();
	}
} // namespace io
