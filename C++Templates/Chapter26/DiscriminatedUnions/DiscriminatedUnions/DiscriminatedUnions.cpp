//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <concepts>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
#include "CVariantStorage.h"
#include "CTypeListFindIndexOfType.h"
#include "CVariant.h"
#include "CThrowException.h"
#include "CVariantVisitPrinter.h"
#include "CVariantVisitGetter.h"
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
void TestVariantStorage(void)
{
	PrintLineSeparator();

	{
		using													TYPE=CVariantStorage<CString,int,double,bool>;

		wcout << L"VARIANT STORAGE - TYPE [" << GetTypeInfoName<TYPE>() << L"] LARGEST TYPE [" << GetTypeInfoName<TYPE::LargestType>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		using													TYPE=CVariantStorage<int,double,bool>;

		wcout << L"VARIANT STORAGE - TYPE [" << GetTypeInfoName<TYPE>() << L"] LARGEST TYPE [" << GetTypeInfoName<TYPE::LargestType>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariantEmptyIsGet(void)
{
	PrintLineSeparator();

	{
		// !!! BY DEFAULT VARIANT je nastaveny na DEFAULT VALUE 1. TYPE.
		CVariant<CString,int,double,bool>						Object;

		wcout << L"VARIANT - EMPTY [" << Object.Empty() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object;

		wcout << L"VARIANT - IS <CString> [" << Object.Is<CString>() << L"]." << endl;
		wcout << L"VARIANT - IS <int> [" << Object.Is<int>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object;

		try
		{
			CString												Value=Object.Get<CString>();

			wcout << L"VARIANT - GET <CString> [" << Value << L"]." << endl;
		}
		catch(const CException& Exception)
		{
			wcout << L"VARIANT - GET <CString> - ERROR [" << Exception.GetMessage() << L"]." << endl;
		}

		try
		{
			double												Value=Object.Get<double>();

			wcout << L"VARIANT - GET <double> [" << Value << L"]." << endl;
		}
		catch(const CException& Exception)
		{
			wcout << L"VARIANT - GET <double> - ERROR [" << Exception.GetMessage() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		const CVariant<CString,int,double,bool>					Object;

		try
		{
			CString												Value=Object.Get<CString>();

			wcout << L"VARIANT - GET <CString> [" << Value << L"]." << endl;
		}
		catch(const CException& Exception)
		{
			wcout << L"VARIANT - GET <CString> - ERROR [" << Exception.GetMessage() << L"]." << endl;
		}

		try
		{
			double												Value=Object.Get<double>();

			wcout << L"VARIANT - GET <double> [" << Value << L"]." << endl;
		}
		catch(const CException& Exception)
		{
			wcout << L"VARIANT - GET <double> - ERROR [" << Exception.GetMessage() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		try
		{
			CString												Value=CVariant<CString,int,double,bool>{}.Get<CString>();

			wcout << L"VARIANT - GET <CString> [" << Value << L"]." << endl;
		}
		catch(const CException& Exception)
		{
			wcout << L"VARIANT - GET <CString> - ERROR [" << Exception.GetMessage() << L"]." << endl;
		}

		try
		{
			double												Value=CVariant<CString,int,double,bool>{}.Get<double>();

			wcout << L"VARIANT - GET <double> [" << Value << L"]." << endl;
		}
		catch(const CException& Exception)
		{
			wcout << L"VARIANT - GET <double> - ERROR [" << Exception.GetMessage() << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariantConstructionAndDestruction(void)
{
	PrintLineSeparator();

	{
		// !!!!! Vola sa CONSTRUCTOR CLASS [CVariantChoice<CString,CString,int,double,bool>], ktory je IMPORTED do CLASS [CVariant] pomocou USING.
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa CONSTRUCTOR CLASS [CVariantChoice<int,CString,int,double,bool>], ktory je IMPORTED do CLASS [CVariant] pomocou USING.
		CVariant<CString,int,double,bool>						Object(100);

		wcout << L"VARIANT - GET <int> [" << Object.Get<int>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa CONSTRUCTOR CLASS [CVariantChoice<double,CString,int,double,bool>], ktory je IMPORTED do CLASS [CVariant] pomocou USING.
		CVariant<CString,int,double,bool>						Object(123.456);

		wcout << L"VARIANT - GET <double> [" << Object.Get<double>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa CONSTRUCTOR CLASS [CVariantChoice<bool,CString,int,double,bool>], ktory je IMPORTED do CLASS [CVariant] pomocou USING.
		CVariant<CString,int,double,bool>						Object(true);

		wcout << L"VARIANT - GET <bool> [" << Object.Get<bool>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Vola sa CONSTRUCTOR CLASS [CVariantChoice<CString,CString,int,double,bool>], ktory je IMPORTED do CLASS [CVariant] pomocou USING.
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"] IS EMPTY [" << Object.Empty() << L"]." << endl;

		Object.Destroy();

		wcout << L"VARIANT - IS EMPTY [" << Object.Empty() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariantOperatorAssignment(void)
{
	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"]." << endl;

		// !!! Nemeni sa TYPE.
		// !!! Vola sa MOVE OPERATOR [OPERATOR=].
		Object=CString(L"Anderson");

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"]." << endl;

		// !!! Nemeni sa TYPE.
		// !!! Vola sa MOVE OPERATOR [OPERATOR=].
		// !!!!! Robi sa SELF ASSIGNMENT.
		Object=Object.Get<CString>();

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"]." << endl;

		// !!! Meni sa TYPE.
		// !!! Vola sa MOVE OPERATOR [OPERATOR=].
		Object=123.456;

		wcout << L"VARIANT - GET <double> [" << Object.Get<double>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));
		double													Value=123.456;

		wcout << L"VARIANT - GET <CString> [" << Object.Get<CString>() << L"]." << endl;

		// !!! Meni sa TYPE.
		// !!! Vola sa COPY OPERATOR [OPERATOR=].
		Object=Value;

		wcout << L"VARIANT - GET <double> [" << Object.Get<double>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariantOperatorAssignmentExceptions(void)
{
	PrintLineSeparator();

	{
		try
		{
			CThrowException										ThrowException{};
			CVariant<CThrowException,CString,int,double,bool>	Object(ThrowException);

			wcout << L"VARIANT - EMTPY [" << Object.Empty() << L"]." << endl;
		}
		catch(CException& E)
		{
			wcout << L"EXCEPTION [" << E.GetMessage() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		try
		{
			CThrowException										ThrowException{};
			CVariant<CString,int,double,bool,CThrowException>	Object(ThrowException);

			wcout << L"VARIANT - EMTPY [" << Object.Empty() << L"]." << endl;
		}
		catch(CException& E)
		{
			wcout << L"EXCEPTION [" << E.GetMessage() << L"]." << endl;
		}
	}

	PrintLineSeparator();

	{
		try
		{
			CVariant<CString,int,double,bool,CThrowException>	Object(L"Timmy");

			wcout << L"VARIANT - EMTPY [" << Object.Empty() << L"]." << endl;

			CThrowException										ThrowException{};

			Object=ThrowException;

			wcout << L"VARIANT - EMTPY [" << Object.Empty() << L"]." << endl;
		}
		catch(CException& E)
		{
			wcout << L"EXCEPTION [" << E.GetMessage() << L"]." << endl;
		}
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariantVisit(void)
{
	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));

		Object.Visit(CVariantVisitPrinter{});

		Object=100;

		Object.Visit(CVariantVisitPrinter{});
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object(CString(L"Timmy"));

		Object.Visit([](const auto& Value) {wcout << L"LAMBDA FUNCTION - VALUE [" << Value << L"]." << endl;});

		Object=100;

		Object.Visit([](const auto& Value) {wcout << L"LAMBDA FUNCTION - VALUE [" << Value << L"]." << endl;});
	}

	PrintLineSeparator();

	{
		// !!!!! CLASS [CVariantVisitGetter] je mozne pouzit, iba AK existuje COMMON TYPE medzi TEMPLATE TYPE PARAMETERS CLASS [CVariant].
		CVariant<int,double>						Object(123.456);

		auto										Result1=Object.Visit(CVariantVisitGetter{});

		wcout << L"RESULT 1 - TYPE [" << GetTypeInfoName<decltype(Result1)>() << L"] VALUE [" << Result1 << L"]." << endl;


		Object=100;

		auto										Result2=Object.Visit(CVariantVisitGetter{});

		wcout << L"RESULT 2 - TYPE [" << GetTypeInfoName<decltype(Result2)>() << L"] VALUE [" << Result2 << L"]." << endl;

		// !!! RETURN VALUE TYPE je explicitne definovany.
		int											Result3=Object.Visit<int>(CVariantVisitGetter{});

		wcout << L"RESULT 3 - TYPE [" << GetTypeInfoName<decltype(Result3)>() << L"] VALUE [" << Result3 << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariantOperatorVariantConstructors(void)
{
	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						OriginalObject(CString(L"Timmy"));
		CVariant<CString,int,double,bool>						Object(OriginalObject);

		wcout << L"VARIANT - CONSTRUCTOR <CString> - COPY [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						OriginalObject(CString(L"Timmy"));
		CVariant<CString,int,double,bool>						Object(move(OriginalObject));

		wcout << L"VARIANT - CONSTRUCTOR <CString> - MOVE [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,double>								OriginalObject(CString(L"Timmy"));
		CVariant<CString,int,double,bool>						Object(OriginalObject);

		wcout << L"VARIANT - CONSTRUCTOR <CString> - TEMPLATE COPY [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,double>								OriginalObject(CString(L"Timmy"));
		CVariant<CString,int,double,bool>						Object(std::move(OriginalObject));

		wcout << L"VARIANT - CONSTRUCTOR <CString> - TEMPLATE MOVE [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,short>									OriginalObject(short(100));

		// !!! Vykona sa CONVERSION so SHORT na INT.
		CVariant<CString,int,double,bool>						Object(OriginalObject);

		wcout << L"VARIANT - CONSTRUCTOR <int> - TEMPLATE COPY - PROMOTE [" << Object.Get<int>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,short>									OriginalObject(short(100));
		CVariant<CString,int,double,bool>						Object(std::move(OriginalObject));

		wcout << L"VARIANT - CONSTRUCTOR <int> - TEMPLATE MOVE - PROMOTE [" << Object.Get<int>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestVariantOperatorVariantAssignment(void)
{
	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						OriginalObject1(CString(L"Timmy"));
		CVariant<CString,int,double,bool>						OriginalObject2(123.456);
		CVariant<CString,int,double,bool>						Object;

		// !!! Vola sa COPY OPERATOR [OPERATOR=].
		Object=OriginalObject1;

		wcout << L"VARIANT - ASSIGNMENT OBJECT 1 <CString> - COPY [" << Object.Get<CString>() << L"]." << endl;

		// !!! Vola sa COPY OPERATOR [OPERATOR=].
		Object=OriginalObject2;

		wcout << L"VARIANT - ASSIGNMENT OBJECT 2 <double> - COPY [" << Object.Get<double>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						OriginalObject;
		CVariant<CString,int,double,bool>						Object(123.456);

		wcout << L"VARIANT - ASSIGNMENT OBJECT <double> - COPY [" << Object.Get<double>() << L"]." << endl;

		OriginalObject.Destroy();

		// !!! Vola sa COPY OPERATOR [OPERATOR=].
		Object=OriginalObject;

		wcout << L"VARIANT - ASSIGNMENT OBJECT - COPY - EMPTY [" << Object.Empty() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object;

		// !!! Vola sa MOVE OPERATOR [OPERATOR=].
		Object=CVariant<CString,int,double,bool>(CString(L"Timmy"));

		wcout << L"VARIANT - ASSIGNMENT OBJECT <CString> - MOVE [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,double>								OriginalObject(CString(L"Timmy"));
		CVariant<CString,int,double,bool>						Object;

		// !!! Vola sa TEMPLATE COPY OPERATOR [OPERATOR=].
		Object=OriginalObject;

		wcout << L"VARIANT - ASSIGNMENT OBJECT <CString> - TEMPLATE COPY [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object;

		// !!! Vola sa TEMPLATE MOVE OPERATOR [OPERATOR=].
		Object=CVariant<CString,double>(CString(L"Timmy"));

		wcout << L"VARIANT - ASSIGNMENT OBJECT <CString> - TEMPLATE MOVE [" << Object.Get<CString>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,short>									OriginalObject(short(100));
		CVariant<CString,int,double,bool>						Object;

		// !!! Vola sa TEMPLATE COPY OPERATOR [OPERATOR=].
		// !!! Vykona sa CONVERSION so SHORT na INT.
		Object=OriginalObject;

		wcout << L"VARIANT - ASSIGNMENT OBJECT <int> - TEMPLATE COPY - PROMOTION [" << Object.Get<int>() << L"]." << endl;
	}

	PrintLineSeparator();

	{
		CVariant<CString,int,double,bool>						Object;

		// !!! Vola sa TEMPLATE MOVE OPERATOR [OPERATOR=].
		// !!! Vykona sa CONVERSION so SHORT na INT.
		Object=CVariant<CString,short>(short(100));

		wcout << L"VARIANT - ASSIGNMENT OBJECT <int> - TEMPLATE MOVE - PROMOTION [" << Object.Get<int>() << L"]." << endl;
	}

	PrintLineSeparator();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestVariantStorage();
	//TestVariantEmptyIsGet();
	//TestVariantConstructionAndDestruction();
	//TestVariantOperatorAssignment();
	//TestVariantOperatorAssignmentExceptions();
	//TestVariantVisit();
	//TestVariantOperatorVariantConstructors();
	TestVariantOperatorVariantAssignment();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------