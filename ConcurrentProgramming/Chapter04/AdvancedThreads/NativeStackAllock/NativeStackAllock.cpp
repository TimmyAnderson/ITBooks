//-----------------------------------------------------------------------------
#include "stdafx.h"
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	char*			Text="Hello World !";
	int				Len=strlen(Text)+1;
	void			*StackMem=_malloca(Len);

	strcpy_s((char*) StackMem,Len,Text);

	printf_s("Text in Stack: [%s] !",StackMem);

	// Umyselne tu vyrobim chybu.
	//strcpy_s((char*) StackMem,5,Text);

	_freea(StackMem);

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------