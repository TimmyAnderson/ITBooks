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
	OLAP.hEvent=NULL;

	BYTE			*Buffer=new BYTE[Size.LowPart+sizeof(wchar_t)];
	DWORD			BytesRead=0;

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
			DWORD	Counter=0;

            while(TRUE)
            {
				// Simulacia nejakej uzitocnej cinnosti.
				Counter++;

                if (GetOverlappedResult(hFile, &OLAP, &BytesRead, FALSE)==FALSE)
                {
					DWORD		LastError=GetLastError();

                    if (LastError==ERROR_IO_INCOMPLETE)
                    {
						// Overlapped IO stale prebieha.
                        continue;
                    }
					else
					{
						wprintf(L"Some other error: %d !\n",LastError);
					}
                }
				else
				{
					Buffer[BytesRead]='\0';
					Buffer[BytesRead+1]='\0';
					wprintf(L"Data: [%s]\n",Buffer);
		            
					wprintf(L"\n\n\nOperation finished ASYNCHRONOUSLY with Counter: [%d], BytesRead: [%d] !\n",Counter,BytesRead);
	                break;
				}
            }
		}
		else
		{
			wprintf(L"Some other error: %d !\n",LastError);
		}
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