#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE			hFile=CreateFile(L"..\\TestFile.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,NULL);

	if (hFile==INVALID_HANDLE_VALUE)
	{
		wprintf(L"Can't find file !\n");
		return;
	}

	LARGE_INTEGER	Size;

	GetFileSizeEx(hFile,&Size);

	OVERLAPPED		OLAP;
	
	OLAP.Offset=0;
	OLAP.OffsetHigh=0;

	// Nastavim Event.
	OLAP.hEvent=CreateEvent(NULL,FALSE,FALSE,NULL);

	BYTE			*Buffer=new BYTE[Size.LowPart+sizeof(wchar_t)];
	DWORD			BytesRead=0;
	DWORD			ErrorCode=0;

	if (ReadFile(hFile, Buffer, Size.LowPart*sizeof(BYTE), &BytesRead, &OLAP)==TRUE)
	{
		Buffer[BytesRead]='\0';
		Buffer[BytesRead+1]='\0';
		wprintf(L"Data: [%s]\n",Buffer);
		wprintf(L"\n\n\nOperation finished SYNCHRONOUSLY - BytesRead: [%d] !\n",BytesRead);
	}
	else
	{
		DWORD		LastError=GetLastError();

		if (LastError==ERROR_IO_PENDING)
		{
			DWORD		Counter=0;
			BOOL		IODone=FALSE;

            while (IODone==FALSE)
            {
				DWORD	Ret=MsgWaitForMultipleObjects(1, &OLAP.hEvent, FALSE, INFINITE, QS_ALLINPUT);

				// Popri cakani na koniec IO spracovavam Messages smerovane do Windows Message Queue.
                switch (Ret)
                {
                    case WAIT_OBJECT_0:
					{
						BytesRead=OLAP.InternalHigh;
						ErrorCode=OLAP.Internal;

						Buffer[BytesRead]='\0';
						Buffer[BytesRead+1]='\0';
						wprintf(L"Data: [%s]\n",Buffer);
						wprintf(L"\n\n\nOperation finished ASYNCHRONOUSLY - BytesRead: [%d], ErrorCode: [%d] !\n",BytesRead,ErrorCode);

                        IODone = TRUE;
					}
                    break;

                    case WAIT_OBJECT_0+1:
					{
						wprintf(L"\n\n\nMessage to Windows Message Queue arrived !\n");
					}
                    break;

                    default:
					{
						wprintf(L"Some other error: %d !\n",Ret);
					}
                    break;
                }
            }
		}
		else
		{
			wprintf(L"Some other error: %d !\n",LastError);
		}
	}

	if (OLAP.hEvent!=NULL)
	{
		CloseHandle(OLAP.hEvent);
		OLAP.hEvent=NULL;
	}

	if (Buffer!=NULL)
	{
		delete[](Buffer);
		Buffer=NULL;
	}

	CloseHandle(hFile);
	hFile=NULL;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------