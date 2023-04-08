//-----------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <windows.h>
#include <winnt.h>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	// TEB ziskam volanim NtCurrentTeb().
	_TEB*			PTeb=NtCurrentTeb();
	_NT_TIB*		PT1=(_NT_TIB*) PTeb;
	
	printf_s("C++: StackBase: %p, StackLimit: %p !\n",PT1->StackBase,PT1->StackLimit);

	_NT_TIB*		PT2=NULL;

	// TEB ziskam volanim cez ASM.
	_asm
	{
		mov eax, fs:[18h]
		mov PT2,eax
	}

	printf_s("ASM: StackBase: %p, StackLimit: %p !\n",PT2->StackBase,PT2->StackLimit);

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------