//----------------------------------------------------------------------------------------------------------------------
#include "CStaticPolymorphismClass2.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CStaticPolymorphismClass2::Print(void) const
{
	wcout << L"METHOD [CStaticPolymorphismClass2::Print()] CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
int CStaticPolymorphismClass2::GetValue(void) const
{
	return(300);
}
//----------------------------------------------------------------------------------------------------------------------