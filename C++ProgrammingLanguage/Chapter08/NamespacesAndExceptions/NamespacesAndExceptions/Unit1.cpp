//-------------------------------------------------------------------------------------------------------
#include <conio.h>
#include <string>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
namespace
{
//-------------------------------------------------------------------------------------------------------
	void Unit1_UnnamedNamespace_Function(void)
	{
		wcout << "Unit1_UnnamedNamespace_Function() !\n";
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Unit1_NoNamespace_Function(void)
{
	wcout << "Unit1_NoNamespace_Function() !\n";

	// !!! V ramci JEDNEHO MODULE su VSETKY KONSTRUKTY UNNAMED NAMESPACE PRISTUPNE.
	Unit1_UnnamedNamespace_Function();
}
//-------------------------------------------------------------------------------------------------------