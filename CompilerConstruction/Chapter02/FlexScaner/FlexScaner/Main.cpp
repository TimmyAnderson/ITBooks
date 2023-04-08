#include <stdio.h>
#include <conio.h>
//-------------------------------------------------------------------------------------------------------
extern "C" int yylex(void);
extern "C" FILE *yyin;
extern "C" void PrintScaningResults(void);
//-------------------------------------------------------------------------------------------------------
// !!! Tato funkcia je volana pri najdeni EOF. V nej mozem bud vratit 1 - koniec SCANINGU, alebo NACITAT DALSI SUBOR do VSTUPNYCH BUFFEROV SCANERA a vratit 0.
extern "C" int yywrap(void)
{
	wprintf_s(L"yywrap() CALLED !\n");

	// Koniec SCANINGU.
	return(1);
}
//-------------------------------------------------------------------------------------------------------
void DoScan(wchar_t* FileName)
{
	FILE			*FP=NULL;
	errno_t			Error=_wfopen_s(&FP,FileName,L"r");

	if (Error==0 && FP!=NULL)
	{
		wprintf_s(L"SCANING... !\n");

		yyin=FP;
		yylex();

		wprintf_s(L"SCANING FINISHED !\n");

		PrintScaningResults();
	}
	else
	{
		wprintf_s(L"Can't READ INPUT FILE [%s] !\n",FileName);
	}

	if (FP!=NULL)
	{
		fclose(FP);
		FP=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void wmain(int argc, wchar_t **argv)
{
	DoScan(L"!Files\\TestSourceCode.txt");

	_getch();
}
//-------------------------------------------------------------------------------------------------------