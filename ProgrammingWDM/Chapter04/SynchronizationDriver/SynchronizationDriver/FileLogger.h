//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <Ntddk.h>
#include <wdm.h>
//-------------------------------------------------------------------------------------------------------
class CFileLogger
{
	private:
		static const ULONG										LOG_TAG=' GOL';

	private:
		KEVENT													MEvent;
		UNICODE_STRING											MFilePath;
		ANSI_STRING												MFilePathANSI;

	public:
		void* operator new(size_t Size)
		{
			PVOID												Object=ExAllocatePoolWithTag(NonPagedPool,Size,LOG_TAG);

			return(Object);
		}

		void operator delete(void* Pointer)
		{
			if (Pointer==NULL)
			{
				return;
			}

			ExFreePoolWithTag(Pointer,LOG_TAG);
		}

	public:
		static void WriteToLog(CFileLogger* Log, char* LogRecord);

	public:
		void WriteToLog(char* LogRecord);

	public:
		CFileLogger(const wchar_t* Path);
		~CFileLogger(void);
};
//-------------------------------------------------------------------------------------------------------