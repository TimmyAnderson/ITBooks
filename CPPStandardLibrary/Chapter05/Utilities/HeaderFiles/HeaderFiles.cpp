//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "MyDebug.h"
#include "SStructure.h"
#include "CClassWithDestructor.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CClassWithDestructor											GlobalVariable(L"GLOBAL VARIABLE");
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMaxAlign(void)
{
	PrintLineSeparator();

	wcout << L"MAX ALIGNMMENT [" << sizeof(max_align_t) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOffsetOf(void)
{
	PrintLineSeparator();

	wcout << L"OFFSET IntField1 [" << offsetof(SStructure,MIntField1) << L"] !" << endl;
	wcout << L"OFFSET WStringField [" << offsetof(SStructure,MWStringField) << L"] !" << endl;
	wcout << L"OFFSET BoolField [" << offsetof(SStructure,MBoolField) << L"] !" << endl;
	wcout << L"OFFSET IntArrayField [" << offsetof(SStructure,MIntArrayField) << L"] !" << endl;
	wcout << L"OFFSET DoubleField [" << offsetof(SStructure,MDoubleField) << L"] !" << endl;
	wcout << L"OFFSET CharField [" << offsetof(SStructure,MCharField) << L"] !" << endl;
	wcout << L"OFFSET IntField2 [" << offsetof(SStructure,MIntField2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ExitCallback1(void)
{
	wcout << L"EXIT CALLBACK 1 CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void ExitCallback2(void)
{
	wcout << L"EXIT CALLBACK 2 CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void QuickExitCallback1(void)
{
	wcout << L"QUICK EXIT CALLBACK 1 CALLED !" << endl;
}
//-----------------------------------------------------------------------------
void QuickExitCallback2(void)
{
	wcout << L"QUICK EXIT CALLBACK 2 CALLED !" << endl;
}
//-----------------------------------------------------------------------------
// !!! FUNCTION sposobuje zobrazenie textov pri SKONCENI PROGRAMU. Preto je lepsie ho spustat priamo z konzoly.
// !!!!! DESTRUCTOR pre LOCAL VARIABLE sa ZAVOLA.
// !!!!! DESTRUCTOR pre STATIC VARIABLE sa ZAVOLA.
// !!!!! DESTRUCTOR pre GLOBAL VARIABLE sa ZAVOLA.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION atexit() sa ZAVOLAJU. Volaju sa v OPACNOM PORADI v akom boli zaregistrovane a este PRED VOLANIM DESTRUCTORS pre STATIC a GLOBAL VARIABLES.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION at_quick_exit() sa NEZAVOLAJU.
void TestNormalExit(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	StaticVariable.Do();

	CClassWithDestructor										LocalVariable(L"LOCAL VARIABLE");

	LocalVariable.Do();

	atexit(ExitCallback1);
	atexit(ExitCallback2);

	at_quick_exit(QuickExitCallback1);
	at_quick_exit(QuickExitCallback2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION sposobuje UKOCENIE PROGRAMU POCAS BEHU FUNCTION a zaroven zobrazenie textov pri SKONCENI PROGRAMU. Preto je lepsie ho spustat priamo z konzoly.
// !!!!! DESTRUCTOR pre LOCAL VARIABLE sa NEZAVOLA.
// !!!!! DESTRUCTOR pre STATIC VARIABLE sa ZAVOLA.
// !!!!! DESTRUCTOR pre GLOBAL VARIABLE sa ZAVOLA.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION atexit() sa ZAVOLAJU. Volaju sa v OPACNOM PORADI v akom boli zaregistrovane a este PRED VOLANIM DESTRUCTORS pre STATIC a GLOBAL VARIABLES.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION at_quick_exit() sa NEZAVOLAJU.
void TestExitByExit(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	StaticVariable.Do();

	CClassWithDestructor										LocalVariable(L"LOCAL VARIABLE");

	LocalVariable.Do();

	atexit(ExitCallback1);
	atexit(ExitCallback2);

	at_quick_exit(QuickExitCallback1);
	at_quick_exit(QuickExitCallback2);

	wcout << L"BEFORE EXIT !" << endl;

	// !!! Sposobi OKAMZITE ukoncenie PROGRAMU.
	exit(EXIT_FAILURE);

	// !!! Tu sa uz CODE NEDOSTANE.
	wcout << L"AFTER EXIT !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION sposobuje UKOCENIE PROGRAMU POCAS BEHU FUNCTION a zaroven zobrazenie textov pri SKONCENI PROGRAMU. Preto je lepsie ho spustat priamo z konzoly.
// !!!!! DESTRUCTOR pre LOCAL VARIABLE sa NEZAVOLA.
// !!!!! DESTRUCTOR pre STATIC VARIABLE sa NEZAVOLA.
// !!!!! DESTRUCTOR pre GLOBAL VARIABLE sa NEZAVOLA.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION atexit() sa NEZAVOLAJU.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION at_quick_exit() sa ZAVOLAJU. Volaju sa v OPACNOM PORADI v akom boli zaregistrovane.
void TestExitByQuickExit(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	StaticVariable.Do();

	CClassWithDestructor										LocalVariable(L"LOCAL VARIABLE");

	LocalVariable.Do();

	atexit(ExitCallback1);
	atexit(ExitCallback2);

	at_quick_exit(QuickExitCallback1);
	at_quick_exit(QuickExitCallback2);

	wcout << L"BEFORE EXIT !" << endl;

	// !!! Sposobi OKAMZITE ukoncenie PROGRAMU BEZ volania DESTRUCTORS pre GLOBAL a STATIC OBJECTS.
	quick_exit(EXIT_FAILURE);

	// !!! Tu sa uz CODE NEDOSTANE.
	wcout << L"AFTER EXIT !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION sposobuje UKOCENIE PROGRAMU POCAS BEHU FUNCTION a zaroven zobrazenie textov pri SKONCENI PROGRAMU. Preto je lepsie ho spustat priamo z konzoly.
// !!!!! DESTRUCTOR pre LOCAL VARIABLE sa NEZAVOLA.
// !!!!! DESTRUCTOR pre STATIC VARIABLE sa NEZAVOLA.
// !!!!! DESTRUCTOR pre GLOBAL VARIABLE sa NEZAVOLA.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION atexit() sa NEZAVOLAJU.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION at_quick_exit() sa NEZAVOLAJU.
void TestExitBy_Exit(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	StaticVariable.Do();

	CClassWithDestructor										LocalVariable(L"LOCAL VARIABLE");

	LocalVariable.Do();

	atexit(ExitCallback1);
	atexit(ExitCallback2);

	at_quick_exit(QuickExitCallback1);
	at_quick_exit(QuickExitCallback2);

	wcout << L"BEFORE EXIT !" << endl;

	// !!! Sposobi OKAMZITE ukoncenie PROGRAMU.
	_Exit(EXIT_FAILURE);

	// !!! Tu sa uz CODE NEDOSTANE.
	wcout << L"AFTER EXIT !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! FUNCTION sposobuje UKOCENIE PROGRAMU POCAS BEHU FUNCTION a zaroven zobrazenie textov pri SKONCENI PROGRAMU. Preto je lepsie ho spustat priamo z konzoly.
// !!!!! DESTRUCTOR pre LOCAL VARIABLE sa NEZAVOLA.
// !!!!! DESTRUCTOR pre STATIC VARIABLE sa NEZAVOLA.
// !!!!! DESTRUCTOR pre GLOBAL VARIABLE sa NEZAVOLA.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION atexit() sa NEZAVOLAJU.
// !!!!! FUNCTIONS zaregistrovane volanim FUNCTION at_quick_exit() sa NEZAVOLAJU.
void TestExitByAbort(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	StaticVariable.Do();

	CClassWithDestructor										LocalVariable(L"LOCAL VARIABLE");

	LocalVariable.Do();

	atexit(ExitCallback1);
	atexit(ExitCallback2);

	at_quick_exit(QuickExitCallback1);
	at_quick_exit(QuickExitCallback2);

	wcout << L"BEFORE EXIT !" << endl;

	// !!! Sposobi OKAMZITE ukoncenie PROGRAMU.
	abort();

	// !!! Tu sa uz CODE NEDOSTANE.
	wcout << L"AFTER EXIT !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestMaxAlign();
	//TestOffsetOf();
	//TestNormalExit();
	//TestExitByExit();
	//TestExitByQuickExit();
	//TestExitBy_Exit();
	TestExitByAbort();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------