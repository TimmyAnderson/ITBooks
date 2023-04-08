#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
void PrintText(wchar_t* Prefix, BYTE* Address, DWORD FileSize)
{
	wprintf_s(Prefix);

	wprintf_s(L" [");

	for (DWORD i=0;i<FileSize;i++)
		wprintf_s(L"%c",Address[i]);

	wprintf_s(L"] !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle=NULL;
	wchar_t			FileName[]={L"NewMMFile.txt"};

	if ((FileHandle=CreateFile(FileName,GENERIC_READ | GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"File [%s] was SUCCESSFULLY OPENED !\n",FileName);

		int			MaxFileSize=100;

		// Predlzi dlzku novovytvoreneho subor na MaxFileSize BYTES, hoci som do MMF nezapisoval.
		if ((MMFHandle=CreateFileMapping(FileHandle,NULL,PAGE_READWRITE,0,MaxFileSize,NULL))!=NULL)
		{
			wprintf_s(L"MMF was SUCCESSFULLY OPENED !\n");

			CloseHandle(MMFHandle);
			MMFHandle=NULL;
		}
		else
		{
			wprintf_s(L"MMF FAILED to OPEN !\n");
		}


		CloseHandle(FileHandle);
		FileHandle=INVALID_HANDLE_VALUE;
	}
	else
	{
		wprintf_s(L"File [%s] FAILED to OPEN !\n",FileName);
	}
}
//------------------------------------------------------------------------------
// Zakladny test MMF.
void Test2(void)
{
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle=NULL;
	wchar_t			FileName[]={L"MMFile.txt"};
	DWORD			FileSize;

	if ((FileHandle=CreateFile(FileName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"File [%s] was SUCCESSFULLY OPENED !\n",FileName);

		FileSize=GetFileSize(FileHandle,NULL);

		// Pouzijem celu dlzku suboru.
		int			MaxFileSize=0;

		if ((MMFHandle=CreateFileMapping(FileHandle,NULL,PAGE_READWRITE,0,MaxFileSize,NULL))!=NULL)
		{
			wprintf_s(L"MMF was SUCCESSFULLY OPENED !\n");

			// Dam ACCESS na READ-WRITE.
			BYTE*	MMFAddress=NULL;
				
			// !!!!! Kedze som nastavil FILE_MAP_ALL_ACCESS, zmeny sa ZAPISU do SUBORU.
			if ((MMFAddress=(BYTE*)MapViewOfFile(MMFHandle,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
			{
				wprintf_s(L"MMF SUCCESSFULLY MAPPED to address [%p] !\n",MMFAddress);

				// Vypisem text na obrazovku.
				PrintText(L"Original text:",MMFAddress,FileSize);

				// Obratim text naopak.
				for (int i=0,To=FileSize/2;i<To;i++)
				{
					BYTE	Temp=MMFAddress[i];

					MMFAddress[i]=MMFAddress[FileSize-i-1];
					MMFAddress[FileSize-i-1]=Temp;
				}

				PrintText(L"MODIFIED text:",MMFAddress,FileSize);

				UnmapViewOfFile(MMFAddress);
			}

			CloseHandle(MMFHandle);
			MMFHandle=NULL;
		}
		else
		{
			wprintf_s(L"MMF FAILED to OPEN !\n");
		}

		CloseHandle(FileHandle);
		FileHandle=INVALID_HANDLE_VALUE;
	}
	else
	{
		wprintf_s(L"File [%s] FAILED to OPEN !\n",FileName);
	}
}
//------------------------------------------------------------------------------
// Testujem PAGE_WRITECOPY.
void Test3(void)
{
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle=NULL;
	wchar_t			FileName[]={L"MMFile.txt"};
	DWORD			FileSize;

	if ((FileHandle=CreateFile(FileName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"File [%s] was SUCCESSFULLY OPENED !\n",FileName);

		FileSize=GetFileSize(FileHandle,NULL);

		// Pouzijem celu dlzku suboru.
		int			MaxFileSize=0;

		// !!!!! Pouzijem atribut PAGE_WRITECOPY.
		if ((MMFHandle=CreateFileMapping(FileHandle,NULL,PAGE_WRITECOPY,0,MaxFileSize,NULL))!=NULL)
		{
			wprintf_s(L"MMF was SUCCESSFULLY OPENED !\n");

			// Dam ACCESS na READ-WRITE.
			BYTE*	MMFAddress=NULL;
				
			// !!!!! Kedze som nastavil FILE_MAP_COPY, zmeny sa NEULOZIA DO SUBORU a spravia sa IBA v PAMATI.
			if ((MMFAddress=(BYTE*)MapViewOfFile(MMFHandle,FILE_MAP_COPY,0,0,0))!=NULL)
			{
				wprintf_s(L"MMF SUCCESSFULLY MAPPED to address [%p] !\n",MMFAddress);

				// Vypisem text na obrazovku.
				PrintText(L"Original text:",MMFAddress,FileSize);

				// Obratim text naopak.
				for (int i=0,To=FileSize/2;i<To;i++)
				{
					BYTE	Temp=MMFAddress[i];

					MMFAddress[i]=MMFAddress[FileSize-i-1];
					MMFAddress[FileSize-i-1]=Temp;
				}

				PrintText(L"MODIFIED text:",MMFAddress,FileSize);

				UnmapViewOfFile(MMFAddress);
			}

			CloseHandle(MMFHandle);
			MMFHandle=NULL;
		}
		else
		{
			wprintf_s(L"MMF FAILED to OPEN !\n");
		}

		CloseHandle(FileHandle);
		FileHandle=INVALID_HANDLE_VALUE;
	}
	else
	{
		wprintf_s(L"File [%s] FAILED to OPEN !\n",FileName);
	}
}
//------------------------------------------------------------------------------
// Vytvorim 2 VIEWS a testujem koherenciu.
void Test4(void)
{
	const int		MAX_FILE_SIZE=35;
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle=NULL;
	wchar_t			FileName[]={L"CoherenceTest.txt"};
	DWORD			FileSize;

	if ((FileHandle=CreateFile(FileName,GENERIC_READ | GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"File [%s] was SUCCESSFULLY OPENED !\n",FileName);

		FileSize=MAX_FILE_SIZE;

		if ((MMFHandle=CreateFileMapping(FileHandle,NULL,PAGE_READWRITE,0,FileSize,NULL))!=NULL)
		{
			wprintf_s(L"MMF was SUCCESSFULLY OPENED !\n");

			BYTE*		MMFAddress1=NULL;
			BYTE*		MMFAddress2=NULL;
				
			if ((MMFAddress1=(BYTE*)MapViewOfFile(MMFHandle,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
			{
				wprintf_s(L"MMF SUCCESSFULLY MAPPED to 1. address [%p] !\n",MMFAddress1);

				if ((MMFAddress2=(BYTE*)MapViewOfFile(MMFHandle,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
				{
					wprintf_s(L"MMF SUCCESSFULLY MAPPED to 2. address [%p] !\n",MMFAddress2);

					PrintText(L"1. address - BEFORE:",MMFAddress1,FileSize);
					PrintText(L"2. address - BEFORE:",MMFAddress2,FileSize);

					char			Text1[]={"Timmy Anderson"};

					memcpy(MMFAddress1,Text1,sizeof(Text1));

					PrintText(L"1. address - AFTER change ADDRESS 1:",MMFAddress1,FileSize);
					PrintText(L"2. address - AFTER change ADDRESS 1:",MMFAddress2,FileSize);

					char			Text2[]={"Jenny Thompson"};

					memcpy(MMFAddress2,Text2,sizeof(Text2));

					PrintText(L"1. address - AFTER change ADDRESS 2:",MMFAddress1,FileSize);
					PrintText(L"2. address - AFTER change ADDRESS 2:",MMFAddress2,FileSize);

					UnmapViewOfFile(MMFAddress2);
				}

				UnmapViewOfFile(MMFAddress1);
			}

			CloseHandle(MMFHandle);
			MMFHandle=NULL;
		}
		else
		{
			wprintf_s(L"MMF FAILED to OPEN !\n");
		}

		CloseHandle(FileHandle);
		FileHandle=INVALID_HANDLE_VALUE;
	}
	else
	{
		wprintf_s(L"File [%s] FAILED to OPEN !\n",FileName);
	}
}
//------------------------------------------------------------------------------
// Vytvorim 2 MMF a testujem koherenciu.
// !!! Hoci data v tomto priklad SU KOHERENTNE, tak Windows to NEGARANTUJE.
void Test5(void)
{
	const int		MAX_FILE_SIZE=35;
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle1=NULL;
	HANDLE			MMFHandle2=NULL;
	wchar_t			FileName[]={L"CoherenceTest.txt"};
	DWORD			FileSize;

	if ((FileHandle=CreateFile(FileName,GENERIC_READ | GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"File [%s] was SUCCESSFULLY OPENED !\n",FileName);

		FileSize=MAX_FILE_SIZE;

		if ((MMFHandle1=CreateFileMapping(FileHandle,NULL,PAGE_READWRITE,0,FileSize,NULL))!=NULL)
		{
			wprintf_s(L"MMF 1 was SUCCESSFULLY OPENED !\n");

			if ((MMFHandle2=CreateFileMapping(FileHandle,NULL,PAGE_READWRITE,0,FileSize,NULL))!=NULL)
			{
				wprintf_s(L"MMF 2 was SUCCESSFULLY OPENED !\n");

				BYTE*		MMFAddress1=NULL;
				BYTE*		MMFAddress2=NULL;
					
				if ((MMFAddress1=(BYTE*)MapViewOfFile(MMFHandle1,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
				{
					wprintf_s(L"MMF 1 SUCCESSFULLY MAPPED to address [%p] !\n",MMFAddress1);

					if ((MMFAddress2=(BYTE*)MapViewOfFile(MMFHandle2,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
					{
						wprintf_s(L"MMF 2 SUCCESSFULLY MAPPED to address [%p] !\n",MMFAddress2);

						PrintText(L"1. address - BEFORE:",MMFAddress1,FileSize);
						PrintText(L"2. address - BEFORE:",MMFAddress2,FileSize);

						char			Text1[]={"Timmy Anderson"};

						memcpy(MMFAddress1,Text1,sizeof(Text1));

						PrintText(L"1. address - AFTER change ADDRESS 1:",MMFAddress1,FileSize);
						PrintText(L"2. address - AFTER change ADDRESS 1:",MMFAddress2,FileSize);

						char			Text2[]={"Jenny Thompson"};

						memcpy(MMFAddress2,Text2,sizeof(Text2));

						PrintText(L"1. address - AFTER change ADDRESS 2:",MMFAddress1,FileSize);
						PrintText(L"2. address - AFTER change ADDRESS 2:",MMFAddress2,FileSize);

						UnmapViewOfFile(MMFAddress2);
					}

					UnmapViewOfFile(MMFAddress1);
				}

				CloseHandle(MMFHandle2);
				MMFHandle2=NULL;
			}

			CloseHandle(MMFHandle1);
			MMFHandle1=NULL;
		}
		else
		{
			wprintf_s(L"MMF FAILED to OPEN !\n");
		}

		CloseHandle(FileHandle);
		FileHandle=INVALID_HANDLE_VALUE;
	}
	else
	{
		wprintf_s(L"File [%s] FAILED to OPEN !\n",FileName);
	}
}
//------------------------------------------------------------------------------
// Demostruje zdielanie pamate medzi dvoma procesmi.
void Test6(void)
{
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle=NULL;
	wchar_t			FileName[]={L"SharedFileBetweenProcesses.txt"};
	DWORD			FileSize;
	char			ID[1024];
	size_t			Len;

	// Meno MMF zidelane medzi procesmi.
	wchar_t			MMFName[]=L"MySuperMMF";

	sprintf_s(ID,_countof(ID),"Last ProcessID is: [%d] !",GetCurrentProcessId());
	Len=strlen(ID);

	wprintf_s(L"CURRENT PROCESS ID: [%d] !\n",GetCurrentProcessId());

	if ((FileHandle=CreateFile(FileName,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,MMFName))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"File [%s] was SUCCESSFULLY OPENED !\n",FileName);

		FileSize=GetFileSize(FileHandle,NULL);

		// Pouzijem celu dlzku suboru.
		int			MaxFileSize=0;

		if ((MMFHandle=CreateFileMapping(FileHandle,NULL,PAGE_READWRITE,0,MaxFileSize,NULL))!=NULL)
		{
			wprintf_s(L"MMF was SUCCESSFULLY OPENED !\n");

			// Dam ACCESS na READ-WRITE.
			BYTE*	MMFAddress=NULL;
				
			// !!!!! Kedze som nastavil FILE_MAP_ALL_ACCESS, zmeny sa ZAPISU do SUBORU.
			if ((MMFAddress=(BYTE*)MapViewOfFile(MMFHandle,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
			{
				wprintf_s(L"MMF SUCCESSFULLY MAPPED to address [%p] !\n",MMFAddress);

				// Vypisem text na obrazovku.
				PrintText(L"Original text:",MMFAddress,FileSize);

				CopyMemory(MMFAddress,ID,Len);

				PrintText(L"MODIFIED text 1:",MMFAddress,FileSize);

				wprintf_s(L"Now you can run 2nd instance of program !\n");

				// !!!!! Ter
				_getch();

				PrintText(L"MODIFIED text 2:",MMFAddress,FileSize);

				UnmapViewOfFile(MMFAddress);
			}

			CloseHandle(MMFHandle);
			MMFHandle=NULL;
		}
		else
		{
			wprintf_s(L"MMF FAILED to OPEN !\n");
		}

		CloseHandle(FileHandle);
		FileHandle=INVALID_HANDLE_VALUE;
	}
	else
	{
		wprintf_s(L"File [%s] FAILED to OPEN !\n",FileName);
	}
}
//------------------------------------------------------------------------------
// Demostruje zdielanie pamate MAPOVANEJ do PAGE FILE medzi dvoma procesmi.
void Test7(void)
{
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle=NULL;
	DWORD			DataSize;
	char			ID[1024];
	size_t			Len;

	// Meno MMF zidelane medzi procesmi.
	wchar_t			MMFName[]=L"MySuperMMF";

	sprintf_s(ID,_countof(ID),"Last ProcessID is: [%d] !",GetCurrentProcessId());
	Len=strlen(ID);

	wprintf_s(L"CURRENT PROCESS ID: [%d] !\n",GetCurrentProcessId());

	// Velkost musi byt >0.
	DataSize=30;

	// !!!!! Mapujem do PAGE FILE, preto pouzijem namiesto HANDLE hondotu INVALID_HANDLE_VALUE.
	if ((MMFHandle=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,DataSize,MMFName))!=NULL)
	{
		wprintf_s(L"MMF was SUCCESSFULLY OPENED !\n");

		// Dam ACCESS na READ-WRITE.
		BYTE*	MMFAddress=NULL;
			
		// !!!!! Kedze som nastavil FILE_MAP_ALL_ACCESS, zmeny sa ZAPISU do SUBORU.
		if ((MMFAddress=(BYTE*)MapViewOfFile(MMFHandle,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
		{
			wprintf_s(L"MMF SUCCESSFULLY MAPPED to address [%p] !\n",MMFAddress);

			// Vypisem text na obrazovku.
			PrintText(L"Original text:",MMFAddress,DataSize);

			CopyMemory(MMFAddress,ID,Len);

			PrintText(L"MODIFIED text 1:",MMFAddress,DataSize);

			wprintf_s(L"Now you can run 2nd instance of program !\n");

			// !!!!! Ter
			_getch();

			PrintText(L"MODIFIED text 2:",MMFAddress,DataSize);

			UnmapViewOfFile(MMFAddress);
		}

		CloseHandle(MMFHandle);
		MMFHandle=NULL;
	}
	else
	{
		wprintf_s(L"MMF FAILED to OPEN !\n");
	}
}
//------------------------------------------------------------------------------
// Demostruje pouzitie SPARSE file a MMF.
void Test8(void)
{
	HANDLE			FileHandle=INVALID_HANDLE_VALUE;
	HANDLE			MMFHandle=NULL;
	// Velkost musi byt >0.
	const DWORD		DATA_SIZE=1024;

	// !!!!! Iba REZERVUJEM PAMET nastavenim SEC_RESERVE.
	if ((MMFHandle=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE | SEC_RESERVE,0,DATA_SIZE,NULL))!=NULL)
	{
		wprintf_s(L"MMF was SUCCESSFULLY OPENED !\n");

		// Dam ACCESS na READ-WRITE.
		BYTE*	MMFAddress=NULL;
			
		if ((MMFAddress=(BYTE*)MapViewOfFile(MMFHandle,FILE_MAP_ALL_ACCESS,0,0,0))!=NULL)
		{
			wprintf_s(L"MMF SUCCESSFULLY MAPPED to address [%p] !\n",MMFAddress);

			// !!! Pamat este NIE JE COMMITED a preto nasledujuci kod ZLYHA.
			//MMFAddress[0]=100;

			// !!! Az TERAZ vykonam COMMIT pamate.
			MMFAddress=(BYTE*) VirtualAlloc(MMFAddress,DATA_SIZE,MEM_COMMIT,PAGE_READWRITE);

			// Teraz uz MOZEM ZAPISOVAT DO PAMATE.
			MMFAddress[0]=100;

			wprintf_s(L"Value at address [%p] is [%d] !\n",MMFAddress,MMFAddress[0]);

			UnmapViewOfFile(MMFAddress);
		}

		CloseHandle(MMFHandle);
		MMFHandle=NULL;
	}
	else
	{
		wprintf_s(L"MMF FAILED to OPEN !\n");
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	Test8();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------