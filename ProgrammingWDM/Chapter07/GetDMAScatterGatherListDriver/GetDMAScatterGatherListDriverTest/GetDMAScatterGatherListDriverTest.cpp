//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <guiddef.h>
#include <Setupapi.h>
#include <string>
#include <iostream>
#include <thread>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
const wchar_t*													DRIVER_NAME=L"\\\\.\\GetDMAScatterGatherListDriver";
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
// Simuluje sa WRITE 1515 bytes. To by mali byt 1-2 MEMORY PAGES (podla zarovnania na MEMORY PAGE BOUNDARY) za predpokladu, ze MEMORY PAGE ma velkost 4096 BYTES.
void Test2(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		const int												NUMBER_OF_ITERATIONS=400;
		string													Buffer="";

		Buffer.append("HUGE TEXT to WRITE [");

		for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			char												LocalBuffer[20];

			if (Index>0)
			{
				Buffer.append(",");
			}

			sprintf_s(LocalBuffer,"%d",Index+1);

			Buffer.append(LocalBuffer);
		}

		Buffer.append("] !");

		const char*												OutputBuffer=Buffer.c_str();
		size_t													NumberOfBytesToWrite=(Buffer.length()+1);
		DWORD													NumberOfBytesWritten;

		wcout << L"TRYING to WRITE [" << NumberOfBytesToWrite << L"] BYTES !\n";

		if (WriteFile(Handle,OutputBuffer,(DWORD) NumberOfBytesToWrite,&NumberOfBytesWritten,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY WRITTEN - NumberOfBytesWritten [%d] !\n",NumberOfBytesWritten);
		}
		else
		{
			wprintf_s(L"Can't WRITE DATA - ERROR [%d] !\n",GetLastError());
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
// Simuluje sa READ 2000 bytes. To by mali byt 1-2 MEMORY PAGES (podla zarovnania na MEMORY PAGE BOUNDARY) za predpokladu, ze MEMORY PAGE ma velkost 4096 BYTES.
void Test3(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[2000];
		DWORD													NumberOfBytesRead;

		ZeroMemory(InputBuffer,sizeof(InputBuffer));

		wcout << L"TRYING to READ [" << sizeof(InputBuffer) << L"] BYTES !\n";

		if (ReadFile(Handle,InputBuffer,sizeof(InputBuffer),&NumberOfBytesRead,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY READ - NumberOfBytesRead [%d] !\n",NumberOfBytesRead);

			if (NumberOfBytesRead>0)
			{
				printf_s("DATA READ [%s] !\n",InputBuffer);
			}
		}
		else
		{
			wprintf_s(L"Can't READ DATA - ERROR [%d] !\n",GetLastError());
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
// Simuluje sa WRITE 4916 bytes. To by mali byt 2-3 MEMORY PAGES (podla zarovnania na MEMORY PAGE BOUNDARY) za predpokladu, ze MEMORY PAGE ma velkost 4096 BYTES.
// !!!!! Ak je BUFFER ulozeny na 2 PAGES, tak OPERACIA ZBEHNE. Ak je na 3 PAGES, tak sa prekroci maximalny pocet pridelenych MAP REGISTERS (2) a DRIVER vrati ERROR.
void Test4(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		const int												NUMBER_OF_ITERATIONS=1200;
		string													Buffer="";

		Buffer.append("HUGE TEXT to WRITE [");

		for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			char												LocalBuffer[20];

			if (Index>0)
			{
				Buffer.append(",");
			}

			sprintf_s(LocalBuffer,"%d",Index+1);

			Buffer.append(LocalBuffer);
		}

		Buffer.append("] !");

		const char*												OutputBuffer=Buffer.c_str();
		size_t													NumberOfBytesToWrite=(Buffer.length()+1);
		DWORD													NumberOfBytesWritten;

		wcout << L"TRYING to WRITE [" << NumberOfBytesToWrite << L"] BYTES !\n";

		if (WriteFile(Handle,OutputBuffer,(DWORD) NumberOfBytesToWrite,&NumberOfBytesWritten,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY WRITTEN - NumberOfBytesWritten [%d] !\n",NumberOfBytesWritten);
		}
		else
		{
			wprintf_s(L"Can't WRITE DATA - ERROR [%d] !\n",GetLastError());
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
// Simuluje sa READ 6000 bytes. To by mali byt 2-3 MEMORY PAGES (podla zarovnania na MEMORY PAGE BOUNDARY) za predpokladu, ze MEMORY PAGE ma velkost 4096 BYTES.
// !!!!! Ak je BUFFER ulozeny na 2 PAGES, tak OPERACIA ZBEHNE. Ak je na 3 PAGES, tak sa prekroci maximalny pocet pridelenych MAP REGISTERS (2) a DRIVER vrati ERROR.
void Test5(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[6000];
		DWORD													NumberOfBytesRead;

		ZeroMemory(InputBuffer,sizeof(InputBuffer));

		wcout << L"TRYING to READ [" << sizeof(InputBuffer) << L"] BYTES !\n";

		if (ReadFile(Handle,InputBuffer,sizeof(InputBuffer),&NumberOfBytesRead,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY READ - NumberOfBytesRead [%d] !\n",NumberOfBytesRead);

			if (NumberOfBytesRead>0)
			{
				printf_s("DATA READ [%s] !\n",InputBuffer);
			}
		}
		else
		{
			wprintf_s(L"Can't READ DATA - ERROR [%d] !\n",GetLastError());
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
// Simuluje sa WRITE 18916 bytes. To by mali byt viac ako 2 MEMORY PAGES za predpokladu, ze MEMORY PAGE ma velkost 4096 BYTES.
// !!!!! DRIVER hodi pri volani FUNCTION vo FIELD [DMA_OPERATIONS.GetScatterGatherList] ERROR [STATUS_INSUFFICIENT_RESOURCES], ktora sa do USER MODE prenesie ako ERROR CODE [ERROR_NO_SYSTEM_RESOURCES]. Je to preto, lebo prenos 18000 BYTES je pridlhy na pocet pridelenych MAP REGISTERS (2), ktore boli pridelene pri testovani.
void Test6(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		const int												NUMBER_OF_ITERATIONS=4000;
		string													Buffer="";

		Buffer.append("HUGE TEXT to WRITE [");

		for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			char												LocalBuffer[20];

			if (Index>0)
			{
				Buffer.append(",");
			}

			sprintf_s(LocalBuffer,"%d",Index+1);

			Buffer.append(LocalBuffer);
		}

		Buffer.append("] !");

		const char*												OutputBuffer=Buffer.c_str();
		size_t													NumberOfBytesToWrite=(Buffer.length()+1);
		DWORD													NumberOfBytesWritten;

		wcout << L"TRYING to WRITE [" << NumberOfBytesToWrite << L"] BYTES !\n";

		if (WriteFile(Handle,OutputBuffer,(DWORD) NumberOfBytesToWrite,&NumberOfBytesWritten,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY WRITTEN - NumberOfBytesWritten [%d] !\n",NumberOfBytesWritten);
		}
		else
		{
			wprintf_s(L"Can't WRITE DATA - ERROR [%d] !\n",GetLastError());
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
// Simuluje sa READ 20000 bytes. To by mali byt viac ako 2 MEMORY PAGES za predpokladu, ze MEMORY PAGE ma velkost 4096 BYTES.
// !!!!! DRIVER hodi pri volani FUNCTION vo FIELD [DMA_OPERATIONS.GetScatterGatherList] ERROR [STATUS_INSUFFICIENT_RESOURCES], ktora sa do USER MODE prenesie ako ERROR CODE [ERROR_NO_SYSTEM_RESOURCES]. Je to preto, lebo prenos 20000 BYTES je pridlhy na pocet pridelenych MAP REGISTERS (2), ktore boli pridelene pri testovani.
void Test7(void)
{
	HANDLE														Handle=CreateFile(DRIVER_NAME,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[20000];
		DWORD													NumberOfBytesRead;

		ZeroMemory(InputBuffer,sizeof(InputBuffer));

		wcout << L"TRYING to READ [" << sizeof(InputBuffer) << L"] BYTES !\n";

		if (ReadFile(Handle,InputBuffer,sizeof(InputBuffer),&NumberOfBytesRead,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY READ - NumberOfBytesRead [%d] !\n",NumberOfBytesRead);

			if (NumberOfBytesRead>0)
			{
				printf_s("DATA READ [%s] !\n",InputBuffer);
			}
		}
		else
		{
			wprintf_s(L"Can't READ DATA - ERROR [%d] !\n",GetLastError());
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
void Test8(void)
{
	thread														T1(Test2);
	thread														T2(Test3);
	thread														T3(Test3);
	thread														T4(Test2);

	T1.join();
	T2.join();
	T3.join();
	T4.join();
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	thread														T1(Test3);
	thread														T2(Test3);
	thread														T3(Test3);
	thread														T4(Test3);

	T1.join();
	T2.join();
	T3.join();
	T4.join();
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	thread														T1(Test4);
	thread														T2(Test5);
	thread														T3(Test4);
	thread														T4(Test5);

	T1.join();
	T2.join();
	T3.join();
	T4.join();
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	thread														T1(Test5);
	thread														T2(Test5);
	thread														T3(Test5);
	thread														T4(Test5);

	T1.join();
	T2.join();
	T3.join();
	T4.join();
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	thread														T1(Test6);
	thread														T2(Test7);
	thread														T3(Test6);
	thread														T4(Test7);

	T1.join();
	T2.join();
	T3.join();
	T4.join();
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	thread														T1(Test7);
	thread														T2(Test7);
	thread														T3(Test7);
	thread														T4(Test7);

	T1.join();
	T2.join();
	T3.join();
	T4.join();
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
		else if (strcmp(Buffer,"6\n")==0)
		{
			Test6();
		}
		else if (strcmp(Buffer,"7\n")==0)
		{
			Test7();
		}
		else if (strcmp(Buffer,"8\n")==0)
		{
			Test8();
		}
		else if (strcmp(Buffer,"9\n")==0)
		{
			Test9();
		}
		else if (strcmp(Buffer,"10\n")==0)
		{
			Test10();
		}
		else if (strcmp(Buffer,"11\n")==0)
		{
			Test11();
		}
		else if (strcmp(Buffer,"12\n")==0)
		{
			Test12();
		}
		else if (strcmp(Buffer,"13\n")==0)
		{
			Test13();
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
		else if (strcmp(Buffer,"x6\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test6();
			}
		}
		else if (strcmp(Buffer,"x7\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test7();
			}
		}
		else if (strcmp(Buffer,"x8\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test8();
			}
		}
		else if (strcmp(Buffer,"x9\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test9();
			}
		}
		else if (strcmp(Buffer,"x10\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test10();
			}
		}
		else if (strcmp(Buffer,"x11\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test11();
			}
		}
		else if (strcmp(Buffer,"x12\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test12();
			}
		}
		else if (strcmp(Buffer,"x13\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test13();
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