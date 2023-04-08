#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test(void)
{
	char*		Input="Timmy Anderson";
	wchar_t*	Output=NULL;

	// Najprv zistim dlzku potrebnu na konverziu.
	int			WCHARCount=MultiByteToWideChar(CP_ACP,0,Input,-1,NULL,0);

	// Teraz alokujem pamat.
	Output=new wchar_t[WCHARCount*sizeof(wchar_t)];

	if (MultiByteToWideChar(CP_ACP,0,Input,-1,Output,WCHARCount)!=0)
	{
		printf("Intput: [%s] - char size: [%d] !\n",Input,strlen(Input));
		wprintf(L"Output: [%s] - char size: [%d] !\n",Output,wcslen(Output));
	}
	else
		wprintf(L"ERROR !");

	delete[](Output);
	Output=NULL;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------