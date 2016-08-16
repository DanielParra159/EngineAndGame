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
			eRead,
			eWrite
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
		~File() {}

		/**
		Open a file
		@param aName, file name
		@param aOpenMode, open mode
		@return TRUE if can be opened
		*/
		BOOL											Open(const std::string& aName, eOpenModes aOpenMode = eRead);
		/**
		Close a file
		*/
		void											Close();
		/**
		Set the index position in the file
		@param aOffset, offset position
		@param aSeekDir, dir of the seek
		*/
		void											Seek(uint32 aOffset, eSeekDir aSeekDir);
		/**
		Set the index position in the file
		@param aPosition, the position from begin of file
		*/
		void											Seek(uint32 aPosition);
		/**
		Read data from the file
		@param aBuffer, the buffer to store the data readed
		@param aSize, size, in bytes, of each element to be read
		@param aCount, number of elements to read
		@return TRUE if can be readed
		*/
		BOOL											Read(void *aBuffer, uint32 aSize, uint32 aCount);
		/**
		Gets the file size
		@return file size
		*/
		uint32											GetSize() const;
		/**
		Gets the index position
		@return index position
		*/
		uint32											GetPosition() const;
		/**
		Get if index position is on end of file
		@return TRUE if index position is on end of file
		*/
		BOOL											EndOfFile() const;
		/**
		Get if the file is open
		@return TRUE if the file is open
		*/
		BOOL											IsOpen() const { return mOpen; }
	}; // File
} // namespace io
#endif // _ENGINE_IO_FILE_H_
