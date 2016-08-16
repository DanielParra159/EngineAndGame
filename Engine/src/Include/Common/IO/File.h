#ifndef _ENGINE_IO_FILE_H_
#define _ENGINE_IO_FILE_H_

#include "Types.h"
#include <string>

namespace io
{
	/**
	This class allow to read and write files to disk
	@TODO: FileSystem
	*/
	class File
	{
	public:
		enum eOpenModes
		{
			eRead
		};
		/**
		Indicates the seek dir, it must be in this order (eBegin = 0, eCurrent = 1, eEnd = 2)
		*/
		enum eSeekDir
		{
			//Begin of file
			eBegin = 0,
			//Current position
			eCurrent = 1,
			//End of file
			eEnd = 2
		};
	private:
		void*											mFileData;
		BOOL											mOpen;
	public:
		File() {}
		virtual ~File() {}

		BOOL											Open(const int8* aName, eOpenModes aOpenMode = eRead);
		void											Close();
		void											Seek(uint32 aOffset, eSeekDir aSeekDir);
		void											Seek(uint32 aPosition);
		BOOL											Read(void *aBuffer, uint32 aSize, uint32 aCount);
		uint32											GetSize() const;
		uint32											GetPosition() const;

		BOOL											IsOpen() const { return mOpen; }
	}; // File
} // namespace io
#endif // _ENGINE_IO_FILE_H_
