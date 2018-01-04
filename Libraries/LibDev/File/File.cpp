//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <assert.h>

// Windows.h include
	// many warnings - need to wrap for Wall warnings
	#pragma warning( push )
	#pragma warning( disable : 4820 )
	#pragma warning( disable : 4668 )
		#include <Windows.h>
	#pragma warning( pop ) 

#include "File.h"
#include "Trace.h"


File::Error File::Open( File::Handle &fh, const char * const fileName, File::Mode mode )
{
	if (mode == File::Mode::WRITE)
	{
		// Create writable file if it doesn't exist. If file exits, overwrite it and give write access.
		fh = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if (mode == File::Mode::READ)
	{
		// Open file only if it exists and make it readonly. If it doesn't exist then it will return an error 
		fh = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	}
	else if (mode == File::Mode::READ_WRITE)
	{
		// Create file that can be written and read. If file exists, overwrite it and give it read/write access.
		fh = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	
	// If file handle is invalid
	if (fh == INVALID_HANDLE_VALUE)
	{	
		Trace::out("Failed to OPEN %s. Error code - %u(0x%X). More information on error code: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx\n", 
					fileName, (unsigned int)GetLastError(), (unsigned int)GetLastError());
		// return error
		return File::Error::OPEN_FAIL;
	}
	
	return 	File::Error::SUCCESS;
}

File::Error File::Close( const File::Handle fh )
{
	// If handle cannot be closed because it is invalid
	if (CloseHandle(fh) == 0)
	{
		Trace::out("Failed to CLOSE handle 0x%p. Error code - %u(0x%X). More information on error code: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx\n",
					fh, (unsigned int)GetLastError(), (unsigned int)GetLastError());
		// return error
		return File::Error::CLOSE_FAIL;
	}

	return 	File::Error::SUCCESS;
}

File::Error File::Write( File::Handle fh, const void * const buffer, const size_t inSize )
{
	// If file cannot be written
	if (WriteFile(fh, buffer, inSize, 0, 0) == 0)
	{
		Trace::out("Failed to WRITE handle 0x%p. Error code - %u(0x%X). More information on error code: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx\n",
					fh, (unsigned int)GetLastError(), (unsigned int)GetLastError());
		// return error
		return File::Error::WRITE_FAIL;
	}

	return 	File::Error::SUCCESS;
}

File::Error File::Read( File::Handle fh,  void * const buffer, const size_t inSize )
{
	// If file cannot be read
	if (ReadFile(fh, buffer, inSize, 0, 0) == 0)
	{
		Trace::out("Failed to READ handle 0x%p. Error code - %u(0x%X). More information on error code: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx\n",
					fh, (unsigned int)GetLastError(), (unsigned int)GetLastError());
		// return error
		return File::Error::READ_FAIL;
	}

	return 	File::Error::SUCCESS;
}

File::Error File::Seek( File::Handle fh, File::Location location, int offset )
{
	// Get Win32 moveMethod
	unsigned long moveMethod = GetWin32MoveMethod(location);
	
	DWORD result = SetFilePointer(fh,			// File handle
								  offset,		// Move pointer by specified byte offset
								  0,			// Don't use high order 32 bit offset
								  moveMethod);  // Start pointer at specified file position

	// If pointer in SetFilePointer is invalid
	if (result == INVALID_SET_FILE_POINTER)
	{
		Trace::out("Failed to SEEK handle 0x%p. Error code - %u(0x%X). More information on error code: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx\n",
					fh, (unsigned int)GetLastError(), (unsigned int)GetLastError());
		// return error
		return File::Error::SEEK_FAIL;
	}

	return 	File::Error::SUCCESS;
}

File::Error File::Tell( File::Handle fh, unsigned int &offset )
{

	offset = SetFilePointer(fh,				// File handle 
							0,				// Don't change pointer byte offset
							0,				// Don't use high order 32 bit offset
							FILE_CURRENT);  // Use current position of pointer in file

	// If pointer in SetFilePointer is invalid
	if (offset == INVALID_SET_FILE_POINTER)
	{
		Trace::out("Failed to TELL handle 0x%p. Error code - %u(0x%X). More information on error code: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx\n",
					fh, (unsigned int)GetLastError(), (unsigned int)GetLastError());
		// Return error
		return File::Error::TELL_FAIL;
	}

	return 	File::Error::SUCCESS;
}

File::Error File::Flush( File::Handle fh )
{

	// If file buffer does NOT successful flush
	if (FlushFileBuffers(fh) == 0)
	{
		Trace::out("Failed to FLUSH handle 0x%p. Error code - %u(0x%X). More information on error code: https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx\n",
					fh, (unsigned int)GetLastError(), (unsigned int)GetLastError());
		// Return error
		return File::Error::FLUSH_FAIL;
	}

	return 	File::Error::SUCCESS;
}


unsigned long File::GetWin32MoveMethod(File::Location fileLocation)
{
	unsigned long location = 0L;

	switch (fileLocation)
	{
	case File::Location::BEGIN:
		location = FILE_BEGIN;
		break;
	case File::Location::CURRENT:
		location = FILE_CURRENT;
		break;
	case File::Location::END:
		location = FILE_END;
		break;
	}

	return location;
}

// ---  End of File ---------------
