//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
#include "Helpers/MyDebug.h"
#include "Helpers/CString.h"
#include "Helpers/CException.h"
//----------------------------------------------------------------------------------------------------------------------
// !!! IMPORT MODULES.
import ModuleSingleFile;
import ModuleVisibleReachable;
import ModuleNamespaces;
import ModuleGlobalModuleFragment;
import ModuleMultiFiles;
#ifdef _MSC_VER
import ModulePrivateFragment;
#endif
import ModuleExports;
import ModuleExportValue1;
import ModuleExportValue2;
import ModuleReachableImportedTypes1;
import ModuleReachableImportedTypes2;
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModuleSingleFile(void)
{
	PrintLineSeparator();

	// !!! CLASS je IMPORTED z MODULE.
	CModuleSingleFileValue										Value(100);

	wcout << L"VALUE [" << Value.GetValue() << L"]." << endl;

	PrintLineSeparator();

	// !!! FUNCTION je IMPORTED z MODULE.
	PrintInt(200);

	PrintLineSeparator();

	// !!! TEMPLATE FUNCTION je IMPORTED z MODULE.
	Print("TIMMY ANDERSON");

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModuleVisibleReachable(void)
{
	PrintLineSeparator();

	/*
	{
		CVisibleClass											Object(100);

		// !!! CLASS [CNotVisibleClass] je NOT VISIBLE, a preto ho nie je mozne takto pouzit.
		const CNotVisibleClass&									InnerObject=Object.GetComplexValue();

		wcout << L"VALUE [" << InnerObject.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
	*/

	{
		CVisibleClass											Object(100);

		// !!! CLASS [CNotVisibleClass] je NOT VISIBLE, ale je ju mozne pouzit pomocou KEYWORD [auto].
		const auto&												InnerObject=Object.GetComplexValue();

		wcout << L"VALUE [" << InnerObject.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!! NOT EXPORTED TYPE je mozne pouzit pomocou KEYWORD [decltype].
		decltype(declval<CVisibleClass>().GetComplexValue())	Object(200);

		wcout << L"VALUE [" << Object.GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModuleNamespaces(void)
{
	PrintLineSeparator();

	{
		NotExportedNamespace::Print1(100);
	}

	PrintLineSeparator();

	{
		ExportedNamespace::Print2(200);
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModuleGlobalModuleFragment(void)
{
	PrintLineSeparator();

	PrintString(L"TIMMY ANDERSON");

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModuleMultiFiles(void)
{
	PrintLineSeparator();

	{
		CMultiFileClass1										Object(L"TIMMY ANDERSON");

		Object.Print();
	}

	PrintLineSeparator();

	{
		CMultiFileClass2										Object(L"TIMMY ANDERSON");

		Object.Print();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModulePrivateFragment(void)
{
	PrintLineSeparator();

	#ifdef _MSC_VER

	{
		NonPrivateFragmentFunction();

		CNonPrivateFragmentClass								Object;

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!! FUNCTION ma DEFINITION v PRIVATE MODULE FRAGMENT, ale kedze DECLARATION je EXPORTED, tak FUNCTION je mozne pouzit.
		PrivateFragmentFunction();

		// !!!!! CLASS ma DEFINITION v PRIVATE MODULE FRAGMENT a teda NEMOZE byt pouzity.
		//CPrivateFragmentClass									Object;

		//Object.Print();
	}

	#endif

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModuleExports(void)
{
	PrintLineSeparator();

	{
		ExportExportedNamespace::ExportedFunction1();
		ExportExportedNamespace::ExportedFunction2();

		// !!! FUNCTION NIE JE EXPORTED, pretoze je v NON-EXPORTED casti EXPORTED NAMESPACE.
		//ExportExportedNamespace::NotExportedFunction();
	}

	PrintLineSeparator();

	{
		CExportExportedClass									Object;

		Object.Print();
	}

	PrintLineSeparator();

	{
		EExportEnum												Value1=EExportEnum::E_VALUE_1;
		EExportEnum												Value2=EExportEnum::E_VALUE_2;

		wcout << L"ENUM VALUE 1 [" << int(Value1) << L"] ENUM VALUE 2 [" << int(Value2) << L"]." << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"EXPORTED OBJECT [" << ExportExportedObject << L"]." << endl;
	}

	PrintLineSeparator();

	{
		ExportExportedLambdaFunctionObject();
	}

	PrintLineSeparator();

	{
		ModuleInternalPrint();

		ModuleInternalInsideNamespacePrint1();

		MyModuleInternal2::ModuleInternalInsideNamespacePrint2();
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestModuleReachableImportedTypes(void)
{
	PrintLineSeparator();

	/*
	{
		// !!! CLASS NIE je VISIBLE, pretoze NIE je EXPORTED.
		CNotExportedClass										Object(100);

		wcout << L"OUTER CLASS - VALUE [" << Object.GetValue().GetValue() << L"]." << endl;
	}
	*/

	/*
	{
		// !!! CLASS NIE je VISIBLE, pretoze NIE je EXPORTED.
		CNotExportedClass										Object=MyExportedTypeFunction1(100);

		wcout << L"OUTER CLASS - VALUE [" << Object.GetValue().GetValue() << L"]." << endl;
	}

	PrintLineSeparator();
	*/

	{
		// !!! CLASS NIE je VISIBLE, pretoze NIE je EXPORTED, ale je REACHABLE.
		auto												Object=MyExportedTypeFunction1(100);

		// !!!!! MEMBERS REACHABLE CLASS su tiez REACHABLE.
		wcout << L"OUTER CLASS - VALUE [" << Object.GetValue().GetValue() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		auto												Object1=MyExportedTypeFunction1(100);

		// !!!!! CLASS [CMyValue1] je sice IMPORTED do MODULE [ModuleReachableImportedTypes1], ale kedze z neho nebola explicitne EXPORTED, CLASS [CMyValue1] NIE je VISIBLE a COMPILER hodi ERROR.
		CMyValue1											Object2=Object1.GetValue();

		wcout << L"INNER CLASS - VALUE [" << Object2.GetValue() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		auto												Object1=MyExportedTypeFunction1(100);

		// !!!!! CLASS [CMyValue] NIE je VISIBLE, ale je REACHABLE.
		auto												Object2=Object1.GetValue();

		wcout << L"INNER CLASS - VALUE [" << Object2.GetValue() << L"]." << endl;
	}

	/*
	PrintLineSeparator();

	{
		// !!!!! FUNCTION nie je EXPORTED a tym padom NIE je VISIBLE, ani REACHABLE.
		auto												Object=MyNotExportedTypeFunction1(100);

		wcout << L"NOT-EXPORTED FUNCTION - VALUE [" << Object.GetValue().GetValue() << L"]." << endl;
	}
	*/

	PrintLineSeparator();

	{
		// !!!!! FUNCTION je EXPORTED a tym padom je VISIBLE, aj REACHABLE.
		auto												Object=MyExportedTypeFunction1(100);

		wcout << L"EXPORTED FUNCTION - VALUE [" << Object.GetValue().GetValue() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! TYPE ma NAME [CNotExportedClass] a je definovany v MODULE [ModuleReachableImportedTypes1].
		auto												Object1=MyExportedTypeFunction1(100);
		// !!!!! TYPE ma NAME [CNotExportedClass] a je definovany v MODULE [ModuleReachableImportedTypes2].
		auto												Object2=MyExportedTypeFunction2(200);

		// !!!!! Aj ked TYPES maju rovnaky NAME, mozu byt IMPORTED a kedze su REACHABLE, aj pouzite.

		CMyValue1											Value1=Object1.GetValue();
		CMyValue2											Value2=Object2.GetValue();

		wcout << L"SAME NAME - VALUE 1 [" << Value1.GetValue() << L"] VALUE 2 [" << Value2.GetValue() << L"]." << endl;

		// !!!!! Aj ked TYPES maju rovnake NAMES, nie su IDENTICKE.
		bool												AreSameTypes=is_same<decltype(Object1),decltype(Object1)>::value;

		if (AreSameTypes==true)
		{
			wcout << L"TYPES are SAME." << endl;
		}
		else
		{
			wcout << L"TYPES are DIFFERENT." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestModuleSingleFile();
	//TestModuleVisibleReachable();
	//TestModuleNamespaces();
	//TestModuleGlobalModuleFragment();
	//TestModuleMultiFiles();
	//TestModulePrivateFragment();
	//TestModuleExports();
	TestModuleReachableImportedTypes();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------