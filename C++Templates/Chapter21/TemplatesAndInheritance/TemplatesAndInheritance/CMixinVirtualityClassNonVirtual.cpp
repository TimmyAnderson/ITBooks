//----------------------------------------------------------------------------------------------------------------------
#include "CMixinVirtualityClassNonVirtual.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CMixinVirtualityClassNonVirtual::SomeNonVirtualMethod(void) const
{
	wcout << L"METHOD [void CMixinVirtualityClassNonVirtual::SomeNonVirtualMethod(void) const] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------