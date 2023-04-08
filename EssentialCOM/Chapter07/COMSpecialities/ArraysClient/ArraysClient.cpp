//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\ArraysServer\ArraysServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void Test1(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			if (SUCCEEDED(Interface->Dummy()))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test2(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->JustPointer(Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test3(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->FixedArray(Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test4(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->SizeIs1(_countof(Array),Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test5(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->SizeIs2(_countof(Array),Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test6(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->SizeIs3(_countof(Array),Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test7(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->SizeIsExpression(_countof(Array)*2,_countof(Array),Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test8(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};
			SArray												ArrayStruct;

			ArrayStruct.ArraySize=_countof(Array);
			ArrayStruct.Array=Array;

			if (SUCCEEDED(Interface->SizeIsInStruct(&ArrayStruct)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test9(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->SizeIsConstant((int*) &Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test10(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[10]={9,8,7,6,5,4,3,2,1,0};

			if (SUCCEEDED(Interface->MaxIsConstant((int*) &Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test11(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[1024];

			if (SUCCEEDED(Interface->SizeIsForOutputParameter(_countof(Array),Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");

				for(int Index=0;Index<10;Index++)
				{
					wprintf(L"CLIENT: ITEM[%d]: [%d] !\n",Index,Array[Index]);
				}
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test12(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wchar_t												Array[1024];

			if (SUCCEEDED(Interface->SizeIsForOutputStringParameter(_countof(Array),Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");

				wprintf(L"CLIENT: TEXT [%s] !\n",Array);
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test13(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[20]={19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

			// !!! Prenesie sa len PRVYCH 15 ITEMS.
			if (SUCCEEDED(Interface->LengthIs(15,(int*) &Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test14(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[20]={19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

			// !!! Prenesie sa 10 ITEMS od ITEM s INDEXOM 5.
			if (SUCCEEDED(Interface->FirstIs(5,10,(int*) &Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test15(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[20]={19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

			// !!! Prenesie sa ITEMS od INDEX 5 po INDEX 15 (vratane).
			if (SUCCEEDED(Interface->LastIs(5,15,(int*) &Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test16(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[20]={19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

			// !!! Prenesie sa 10 ITEMS od INDEXU 0.
			if (SUCCEEDED(Interface->LengthIsAndSizeIs(_countof(Array),10,(int*) &Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test17(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[20];
			int													ArrayLength=0;

			// !!! Do COM OBJECT sa prenesie POLE na 20 ITEMS, ale COM OBJECT z neho vyuzije iba 'ArrayLength' ITEMS.
			if (SUCCEEDED(Interface->LengthIsAndSizeIsForOutputParamerter(_countof(Array),&ArrayLength,Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");

				for(int Index=0;Index<ArrayLength;Index++)
				{
					wprintf(L"CLIENT: ITEM[%d]: [%d] !\n",Index,Array[Index]);
				}
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test18(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Value=100;
			int*												PointerToValue=&Value;
			int**												PointerToPointerToValue=&PointerToValue;

			if (SUCCEEDED(Interface->PointerToPointer(PointerToPointerToValue)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test19(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Value1=100;
			int													Value2=200;
			int													Value3=300;
			int*												ArrayOfPointers[]={&Value1,&Value2,&Value3};

			if (SUCCEEDED(Interface->ArrayOfPointers(ArrayOfPointers)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test20(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[4]={100,200,300,400};
			int*												PointerToArray=Array;

			if (SUCCEEDED(Interface->PointerToArray(&PointerToArray)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test21(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array1[4]={11,12,13,14};
			int													Array2[4]={21,22,23,24};
			int													Array3[4]={31,32,33,34};
			int*												ArrayToArray[3]={Array1,Array2,Array3};

			if (SUCCEEDED(Interface->ArrayToArray(ArrayToArray)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test22(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Array[3][4]={{11,12,13,14},{21,22,23,24},{31,32,33,34}};

			if (SUCCEEDED(Interface->Matrix(Array)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test23(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			if (SUCCEEDED(Interface->String(L"Timmy Anderson")))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test24(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			// !!! Kedze PARAMETER je typu OUTPUT, prenesie NULL POINTER.
			wchar_t*											Buffer=NULL;

			// !!! METHOD COM OBJECT NAPLNI POINTER.
			if (SUCCEEDED(Interface->OutputString(&Buffer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");

				wprintf_s(L"TEXT [%s] !\n",Buffer);

				// !!!!! Kedze METHOD COM OBJECT alokovala pamat cez CoTaskMemAlloc() CLIENT ju MUSI uvolnit cez CoTaskMemFree().
				CoTaskMemFree(Buffer);
				Buffer=NULL;
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void Test25(void)
{
	// !!!!! Umyselne CLIENT zavadza SINGLE-TRHEADED APARTMENT, pretoze COM OBJECT pouziva FREE THREADED APARTMENT a kedze APARTMENTS su ROZDIELNE, tak COM SYSTEM realizuje MARSHALING vdaka comu je najlepsie mozne demonstrovat PRENASANIE ARRAYS.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IArraysTest>							Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ArraysObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IArraysTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			// !!! Vytvori JEDNOROZMERNE SAFEARRAY.
			SAFEARRAY*											SA=SafeArrayCreateVector(VT_I4,10,10);
			int*												Data=NULL;
			long												LowerBound;
			long												UpperBound;

			if (SUCCEEDED(HR=SafeArrayGetLBound(SA,1,&LowerBound)))
			{
				if (SUCCEEDED(HR=SafeArrayGetUBound(SA,1,&UpperBound)))
				{
					if (SUCCEEDED(HR=SafeArrayAccessData(SA,(void**) &Data)))
					{
						// !!! Malo by to byt (UpperBound-LowerBound)+1.
						for (long Index=0;Index<(UpperBound-LowerBound)+1;Index++)
						{
							Data[Index]=9-Index;
						}

						// Uvolni sa POINTER na DATA.
						if (FAILED(HR=SafeArrayUnaccessData(SA)))
						{
							wprintf_s(L"Can't UNACCESS DATA !\n");
						}
					}
					else
					{
						wprintf_s(L"Can't ACCESS DATA !\n");
					}
				}
				else
				{
					wprintf_s(L"Can't GET UPPER BOUND !\n");
				}
			}
			else
			{
				wprintf_s(L"Can't GET LOWER BOUND !\n");
			}

			// !!! METHOD COM OBJECT NAPLNI POINTER.
			if (SUCCEEDED(Interface->SafeArrayInt(&SA)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
			}

			// !!! Uvolni SAFE ARRAY.
			if (FAILED(SafeArrayDestroy(SA)))
			{
				wprintf_s(L"SAFE ARRAY DESTROY FAILED !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	//Test17();
	//Test18();
	//Test19();
	//Test20();
	//Test21();
	//Test22();
	//Test23();
	//Test24();
	Test25();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------