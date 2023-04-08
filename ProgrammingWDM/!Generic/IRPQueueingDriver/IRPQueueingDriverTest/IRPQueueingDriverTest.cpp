//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <guiddef.h>
#include <Setupapi.h>
#include <thread>
#include <system_error>
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_QUEUE_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
const wchar_t*													DRIVER_NAME=L"\\\\.\\IRPQueueingDriver";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void AsynchronousTestThread(int NumberOfOperations)
{
	HANDLE*														EventHandles=new HANDLE[NumberOfOperations];
	OVERLAPPED*													Overlapped=new OVERLAPPED[NumberOfOperations];
	HANDLE*														Handles=new HANDLE[NumberOfOperations];
	bool														HasError=false;

	if (EventHandles!=nullptr && Overlapped!=nullptr && Handles!=nullptr)
	{
		ZeroMemory(EventHandles,sizeof(HANDLE)*NumberOfOperations);
		ZeroMemory(Overlapped,sizeof(OVERLAPPED)*NumberOfOperations);
		ZeroMemory(Handles,sizeof(HANDLE)*NumberOfOperations);

		for(int Index=0;Index<NumberOfOperations;Index++)
		{
			if ((EventHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL))==NULL)
			{
				wprintf_s(L"Can't create EVENT [%d] !\n",Index);
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			for(int Index=0;Index<NumberOfOperations;Index++)
			{
				Overlapped[Index].Offset=0;
				Overlapped[Index].hEvent=EventHandles[Index];
			}

			for(int Index=0;Index<NumberOfOperations;Index++)
			{
				HANDLE											Handle=CreateFile(DRIVER_NAME,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

				if (Handle!=INVALID_HANDLE_VALUE)
				{
					wprintf_s(L"HANDLE [%d] is CREATED !\n",Index);

					Handles[Index]=Handle;
				}
				else
				{
					wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
					HasError=true;
					break;
				}
			}

			if (HasError==false)
			{
				// Pre jednoduchost sa pouziva ten isty BUFFER, co v reale by samozrejme sposobilo SUCASNE prepisovanie toho isteho BUFFER VIACERYMI ASYNCHRONNYMI OPERACIAMI.
				char											InputBuffer[1000];

				for(int Index=0;Index<NumberOfOperations;Index++)
				{
					wprintf_s(L"DATA READ [%d] is going to START !\n",Index);

					if (ReadFile(Handles[Index],InputBuffer,sizeof(InputBuffer),NULL,&Overlapped[Index])!=FALSE)
					{
						wprintf_s(L"DATA READ [%d] SYNCHRONOUSLY !\n",Index);
					}
					else
					{
						DWORD									LE=GetLastError();

						if (LE==ERROR_IO_PENDING)
						{
							wprintf_s(L"ASYNCHRONOUS OPERATION [%d] STARTED !\n",Index);
						}
						else
						{
							wprintf_s(L"Can't READ [%d] DATA - ERROR [%d] !\n",Index,GetLastError());

							SetEvent(EventHandles[Index]);
						}
					}
				}

				wprintf_s(L"WAITING for OPERATIONS to FINISH !\n");

				for(int Index=0;Index<NumberOfOperations;Index++)
				{
					WaitForSingleObject(EventHandles[Index],INFINITE);
				}
			}

			for(int Index=0;Index<NumberOfOperations;Index++)
			{
				if (Handles[Index]!=NULL)
				{
					if (CloseHandle(Handles[Index])!=FALSE)
					{
						wprintf_s(L"DEVICE [%d] SUCCESSFULLY CLOSED !\n",Index);
					}
					else
					{
						wprintf_s(L"Can't CLOSE DEVICE [%d] - ERROR [%d] !\n",Index,GetLastError());
					}

					Handles[Index]=NULL;
				}
			}
		}

		for(int Index=0;Index<NumberOfOperations;Index++)
		{
			if (EventHandles[Index]!=NULL)
			{
				if (CloseHandle(EventHandles[Index])!=FALSE)
				{
					wprintf_s(L"EVENT [%d] SUCCESSFULLY CLOSED !\n",Index);
				}
				else
				{
					wprintf_s(L"Can't CLOSE EVENT [%d] - ERROR [%d] !\n",Index,GetLastError());
				}

				EventHandles[Index]=NULL;
			}
		}
	}
	else
	{
		wprintf_s(L"Not ENOUGH MEMORY !");
	}

	if (EventHandles!=NULL)
	{
		delete[](EventHandles);
		EventHandles=nullptr;
	}

	if (Overlapped!=NULL)
	{
		delete[](Overlapped);
		Overlapped=nullptr;
	}

	if (Handles!=NULL)
	{
		delete[](Handles);
		Handles=nullptr;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[512];
		BYTE													OutputBuffer[1024];
		DWORD													BytesReturned=0;

		ZeroMemory(InputBuffer,sizeof(InputBuffer));
		ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

		sprintf_s(InputBuffer,_countof(InputBuffer),"My name is Jenny Thompson !");
		wprintf_s(L"InputBuffer [%p], OutputBuffer [%p] !\n",InputBuffer,OutputBuffer);
		printf_s("InputBuffer [%s] !\n",InputBuffer);

		if (DeviceIoControl(Handle,IOCTL_SIMPLE_TEST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT - BytesReturned [%d], OutputBuffer [%s] !\n",BytesReturned,(wchar_t*)OutputBuffer);
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[512];
		BYTE													OutputBuffer[1024];
		DWORD													BytesReturned=0;

		ZeroMemory(InputBuffer,sizeof(InputBuffer));
		ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

		sprintf_s(InputBuffer,_countof(InputBuffer),"My name is Jenny Thompson !");
		wprintf_s(L"InputBuffer [%p], OutputBuffer [%p] !\n",InputBuffer,OutputBuffer);
		printf_s("InputBuffer [%s] !\n",InputBuffer);

		if (DeviceIoControl(Handle,IOCTL_QUEUE_IRP_TEST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT - BytesReturned [%d], OutputBuffer [%s] !\n",BytesReturned,(wchar_t*)OutputBuffer);
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
// TEST emuluje ASYNCHRONNU OPERACIU.
void Test3(void)
{
	HANDLE														EventHandle=CreateEvent(NULL,TRUE,FALSE,NULL);

	if (EventHandle!=NULL)
	{
		OVERLAPPED												Overlapped;

		ZeroMemory(&Overlapped,sizeof(OVERLAPPED));

		Overlapped.Offset=0;
		Overlapped.hEvent=EventHandle;

		HANDLE													Handle=CreateFile(DRIVER_NAME,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

		if (Handle!=INVALID_HANDLE_VALUE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

			char												InputBuffer[1000];
			DWORD												NumberOfBytesRead;

			if (ReadFile(Handle,InputBuffer,sizeof(InputBuffer),&NumberOfBytesRead,&Overlapped)!=FALSE)
			{
				wprintf_s(L"DATA READ SYNCHRONOUSLY - NumberOfBytesRead [%d] !\n",NumberOfBytesRead);
			}
			else
			{
				DWORD											LE=GetLastError();

				if (LE==ERROR_IO_PENDING)
				{
					wprintf_s(L"ASYNCHRONOUS OPERATION STARTED !\n");
				}
				else
				{
					wprintf_s(L"Can't READ DATA - ERROR [%d] !\n",GetLastError());

					SetEvent(EventHandle);
				}
			}

			WaitForSingleObject(EventHandle,INFINITE);

			if (CloseHandle(Handle)!=FALSE)
			{
				wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
			}
			else
			{
				wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
			}

			if (CloseHandle(EventHandle)!=FALSE)
			{
				wprintf_s(L"EVENT SUCCESSFULLY CLOSED !\n");
			}
			else
			{
				wprintf_s(L"Can't CLOSE EVENT - ERROR [%d] !\n",GetLastError());
			}
		}
		else
		{
			wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't create EVENT !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
// TEST emuluje opakovanu ASYNCHRONNU OPERACIU.
void Test4(void)
{
	const int													NUMBER_OF_OPERATIONS=5;
	HANDLE														EventHandles[NUMBER_OF_OPERATIONS];
	OVERLAPPED													Overlapped[NUMBER_OF_OPERATIONS];
	bool														HasError=false;

	ZeroMemory(&EventHandles,sizeof(EventHandles));
	ZeroMemory(&Overlapped,sizeof(Overlapped));

	for(int Index=0;Index<NUMBER_OF_OPERATIONS;Index++)
	{
		if ((EventHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL))==NULL)
		{
			wprintf_s(L"Can't create EVENT [%d] !\n",Index);
			HasError=true;
			break;
		}
	}

	if (HasError==false)
	{
		for(int Index=0;Index<NUMBER_OF_OPERATIONS;Index++)
		{
			Overlapped[Index].Offset=0;
			Overlapped[Index].hEvent=EventHandles[Index];
		}

		HANDLE													Handles[NUMBER_OF_OPERATIONS];

		ZeroMemory(&Handles,sizeof(Handles));

		for(int Index=0;Index<NUMBER_OF_OPERATIONS;Index++)
		{
			HANDLE												Handle=CreateFile(DRIVER_NAME,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

			if (Handle!=INVALID_HANDLE_VALUE)
			{
				Handles[Index]=Handle;
			}
			else
			{
				wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
				HasError=true;
				break;
			}
		}

		if (HasError==false)
		{
			// Pre jednoduchost sa pouziva ten isty BUFFER, co v reale by samozrejme sposobilo SUCASNE prepisovanie toho isteho BUFFER VIACERYMI ASYNCHRONNYMI OPERACIAMI.
			char												InputBuffer[1000];

			for(int Index=0;Index<NUMBER_OF_OPERATIONS;Index++)
			{
				if (ReadFile(Handles[Index],InputBuffer,sizeof(InputBuffer),NULL,&Overlapped[Index])!=FALSE)
				{
					wprintf_s(L"DATA READ [%d] SYNCHRONOUSLY !\n",Index);
				}
				else
				{
					DWORD										LE=GetLastError();

					if (LE==ERROR_IO_PENDING)
					{
						wprintf_s(L"ASYNCHRONOUS OPERATION [%d] STARTED !\n",Index);
					}
					else
					{
						wprintf_s(L"Can't READ [%d] DATA - ERROR [%d] !\n",Index,GetLastError());

						SetEvent(EventHandles[Index]);
					}
				}
			}

			wprintf_s(L"WAITING for OPERATIONS to FINISH !\n");

			for(int Index=0;Index<NUMBER_OF_OPERATIONS;Index++)
			{
				WaitForSingleObject(EventHandles[Index],INFINITE);
			}
		}

		for(int Index=0;Index<NUMBER_OF_OPERATIONS;Index++)
		{
			if (Handles[Index]!=NULL)
			{
				if (CloseHandle(Handles[Index])!=FALSE)
				{
					wprintf_s(L"DEVICE [%d] SUCCESSFULLY CLOSED !\n",Index);
				}
				else
				{
					wprintf_s(L"Can't CLOSE DEVICE [%d] - ERROR [%d] !\n",Index,GetLastError());
				}

				Handles[Index]=NULL;
			}
		}
	}

	for(int Index=0;Index<NUMBER_OF_OPERATIONS;Index++)
	{
		if (EventHandles[Index]!=NULL)
		{
			if (CloseHandle(EventHandles[Index])!=FALSE)
			{
				wprintf_s(L"EVENT [%d] SUCCESSFULLY CLOSED !\n",Index);
			}
			else
			{
				wprintf_s(L"Can't CLOSE EVENT [%d] - ERROR [%d] !\n",Index,GetLastError());
			}

			EventHandles[Index]=NULL;
		}
	}
}
//-------------------------------------------------------------------------------------------------------
// TEST emuluje opakovanu ASYNCHRONNU OPERACIU vo viacerych THREADS.
void Test5(void)
{
	const int													NUMBER_OF_THREADS=3;
	const int													NUMBER_OF_OPERATIONS=3;

	std::thread													Threads[NUMBER_OF_THREADS];

	try
	{
		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			Threads[Index]=std::thread(AsynchronousTestThread,NUMBER_OF_OPERATIONS);
		}
	}
	catch(std::system_error& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}
	
	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			Threads[Index].join();
		}
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int wmain(int argc, wchar_t* argv[])
{
	wprintf_s(L"ENTER VALUE (or 'q' to EXIT):\n");

	for(;;)
	{
		char													Buffer[100];

		fgets(Buffer,_countof(Buffer),stdin);

		if (strcmp(Buffer,"q\n")==0)
		{
			break;
		}
		else if (strcmp(Buffer,"1\n")==0)
		{
			Test1();
		}
		else if (strcmp(Buffer,"2\n")==0)
		{
			Test2();
		}
		else if (strcmp(Buffer,"3\n")==0)
		{
			Test3();
		}
		else if (strcmp(Buffer,"4\n")==0)
		{
			Test4();
		}
		else if (strcmp(Buffer,"5\n")==0)
		{
			Test5();
		}
		else if (strcmp(Buffer,"x1\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test1();
			}
		}
		else if (strcmp(Buffer,"x2\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test2();
			}
		}
		else if (strcmp(Buffer,"x3\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test3();
			}
		}
		else if (strcmp(Buffer,"x4\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test4();
			}
		}
		else if (strcmp(Buffer,"x5\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test5();
			}
		}
		else
		{
			system("cls");
			wprintf_s(L"ENTER VALUE (or 'q' to EXIT):\n");
		}
	}

	wprintf_s(L"Press any KEY to EXIT !\n");
	(void)_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------