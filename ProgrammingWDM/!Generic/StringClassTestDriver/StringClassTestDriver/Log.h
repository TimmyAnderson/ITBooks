//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <Ntddk.h>
#include <wdm.h>
//-------------------------------------------------------------------------------------------------------
class CLog
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
		static void WriteToLog(CLog* Log, char* LogRecord);

	public:
		void WriteToLog(char* LogRecord);

	public:
		CLog(const wchar_t* Path);
		~CLog(void);
};
//-------------------------------------------------------------------------------------------------------