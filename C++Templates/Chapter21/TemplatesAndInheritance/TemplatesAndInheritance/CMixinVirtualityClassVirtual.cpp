//----------------------------------------------------------------------------------------------------------------------
#include "CMixinVirtualityClassVirtual.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CMixinVirtualityClassVirtual::SomeVirtualMethod(void) const
{
	wcout << L"METHOD [void CMixinVirtualityClassVirtual::SomeVirtualMethod(void) const] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------