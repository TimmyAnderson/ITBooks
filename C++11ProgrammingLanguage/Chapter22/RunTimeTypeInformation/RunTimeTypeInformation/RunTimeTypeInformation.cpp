//-----------------------------------------------------------------------------
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include "MyDebug.h"
#include "CDerivedClass.h"
#include "CVirtualBaseClass2.h"
#include "CNonUniqueConversionDerived.h"
#include "CTypeidNonVirtualDerived.h"
#include "CTypeidVirtualDerived.h"
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable:4540)
#endif
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastDerivedToBaseConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CDerivedClass*												PointerToDerivedClass=&DerivedClass;
	CDerivedClass&												ReferenceToDerivedClass=DerivedClass;

	// CONVERSION uspesne prejde, pretoze CLASS 'CDerivedClass' JE DERIVED z CLASS 'CVirtualBaseClass1'.
	if (dynamic_cast<CVirtualBaseClass1*>(PointerToDerivedClass)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CVirtualBaseClass1*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CVirtualBaseClass1*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// CONVERSION uspesne prejde, pretoze CLASS 'CDerivedClass' JE DERIVED z CLASS 'CVirtualBaseClass1'.
		dynamic_cast<CVirtualBaseClass1&>(ReferenceToDerivedClass).VirtualMethod();

		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [CVirtualBaseClass1&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [CVirtualBaseClass1&] FAILED !" << endl;
	}

	PrintLineSeparator();

	// !!!!! CONVERSION ZLYHA, pretoze CLASS 'CDerivedClass' NIE JE DERIVED z CLASS 'CVirtualBaseClass2'.
	if (dynamic_cast<CVirtualBaseClass2*>(PointerToDerivedClass)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CVirtualBaseClass2*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CVirtualBaseClass2*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! CONVERSION ZLYHA, pretoze CLASS 'CDerivedClass' NIE JE DERIVED z CLASS 'CVirtualBaseClass2'.
		dynamic_cast<CVirtualBaseClass2&>(ReferenceToDerivedClass).VirtualMethod();

		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [CVirtualBaseClass2&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [CVirtualBaseClass2&] FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastBaseToDerivedConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CVirtualBaseClass1											BaseClass1;
	CVirtualBaseClass2											BaseClass2;
	CVirtualBaseClass1*											PointerToBaseClass1=&DerivedClass;
	CVirtualBaseClass1&											ReferenceToBaseClass1=DerivedClass;
	CVirtualBaseClass2*											PointerToBaseClass2=&BaseClass2;
	CVirtualBaseClass2&											ReferenceToBaseClass2=BaseClass2;
	CVirtualBaseClass1*											DirectPointerToBaseClass1=&BaseClass1;
	CVirtualBaseClass1&											DirectReferenceToBaseClass1=BaseClass1;

	// CONVERSION uspesne prejde, pretoze VARIABLE 'PointerToBaseClass1' ukazuje na OBJECT TYPE 'CDerivedClass'.
	if (dynamic_cast<CDerivedClass*>(PointerToBaseClass1)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1*] to TYPE [CDerivedClass*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1*] to TYPE [CDerivedClass*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// CONVERSION uspesne prejde, pretoze VARIABLE 'ReferenceToBaseClass1' ukazuje na OBJECT TYPE 'CDerivedClass'.
		dynamic_cast<CDerivedClass&>(ReferenceToBaseClass1).VirtualMethod();

		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1&] to TYPE [CDerivedClass&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1&] to TYPE [CDerivedClass&] FAILED !" << endl;
	}

	PrintLineSeparator();

	// !!!!! CONVERSION ZLYHA, pretoze VARIABLE 'PointerToBaseClass2' ukazuje na OBJECT TYPE 'CVirtualBaseClass2', ktory NIE JE BASE CLASS voci CLASS 'CDerivedClass'.
	if (dynamic_cast<CDerivedClass*>(PointerToBaseClass2)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass2*] to TYPE [CDerivedClass*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass2*] to TYPE [CDerivedClass*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! CONVERSION ZLYHA, pretoze VARIABLE 'ReferenceToBaseClass2' ukazuje na OBJECT TYPE 'CVirtualBaseClass2', ktory NIE JE BASE CLASS voci CLASS 'CDerivedClass'.
		dynamic_cast<CDerivedClass&>(ReferenceToBaseClass2).VirtualMethod();

		wcout << L"CONVERSION of TYPE [CVirtualBaseClass2&] to TYPE [CDerivedClass&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass2&] to TYPE [CDerivedClass&] FAILED !" << endl;
	}

	PrintLineSeparator();

	// !!!!! CONVERSION ZLYHA, pretoze VARIABLE 'DirectPointerToBaseClass1' ukazuje na OBJECT TYPE 'CVirtualBaseClass1'.
	if (dynamic_cast<CDerivedClass*>(DirectPointerToBaseClass1)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1*] to TYPE [CDerivedClass*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1*] to TYPE [CDerivedClass*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! CONVERSION ZLYHA, pretoze VARIABLE 'DirectReferenceToBaseClass1' ukazuje na OBJECT TYPE 'CVirtualBaseClass1'.
		dynamic_cast<CDerivedClass&>(DirectReferenceToBaseClass1).VirtualMethod();

		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1&] to TYPE [CDerivedClass&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1&] to TYPE [CDerivedClass&] FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastNonUniqueConversion(void)
{
	PrintLineSeparator();

#ifdef _MSC_VER
	// !!!!! Podla knihy COMPILER by MAL umoznit NON-UNIQUE CONVERSION. Visual C++ to umoznuje, zatial co GCC hodi COMPILATION ERROR.
	CNonUniqueConversionDerived									Derived;
	CNonUniqueConversionBase1*									PointerToBase1=&Derived;
	CNonUniqueConversionDerived*								PointerToDerived=&Derived;

	if (dynamic_cast<CNonUniqueConversionSuperBase*>(PointerToDerived)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CNonUniqueConversionDerived*] to TYPE [CNonUniqueConversionSuperBase*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CNonUniqueConversionDerived*] to TYPE [CNonUniqueConversionSuperBase*] FAILED !" << endl;
	}

	PrintLineSeparator();

	CNonUniqueConversionDerived&								ReferenceToDerived=Derived;

	try
	{
		// !!!!! Podla knihy COMPILER by MAL umoznit NON-UNIQUE CONVERSION. Visual C++ to umoznuje, zatial co GCC hodi COMPILATION ERROR.
		dynamic_cast<CNonUniqueConversionSuperBase&>(ReferenceToDerived);

		wcout << L"CONVERSION of TYPE [CNonUniqueConversionDerived&] to TYPE [CNonUniqueConversionSuperBase&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CNonUniqueConversionDerived&] to TYPE [CNonUniqueConversionSuperBase&] FAILED !" << endl;
	}
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastSiblingConversion(void)
{
	PrintLineSeparator();

	CNonUniqueConversionDerived									Derived;
	CNonUniqueConversionBase1*									PointerToBase1=&Derived;
	CNonUniqueConversionBase1&									ReferenceToBase1=Derived;

	// !!! CONVERSION medzi SIBLING CLASSES prebehne USPESNE.
	if (dynamic_cast<CNonUniqueConversionBase2*>(PointerToBase1)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CNonUniqueConversionBase1*] to TYPE [CNonUniqueConversionBase2*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CNonUniqueConversionBase1*] to TYPE [CNonUniqueConversionBase2*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! CONVERSION medzi SIBLING CLASSES prebehne USPESNE.
		dynamic_cast<CNonUniqueConversionBase2&>(ReferenceToBase1).PublicMethod();

		wcout << L"CONVERSION of TYPE [CNonUniqueConversionBase1&] to TYPE [CNonUniqueConversionBase2&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CNonUniqueConversionBase1&] to TYPE [CNonUniqueConversionBase2&] FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastPolymorficNonPolymorficTypesConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CVirtualBaseClass1*											PointerToBaseClass1=&DerivedClass;
	CVirtualBaseClass1&											ReferenceToBaseClass1=DerivedClass;

	// !!!!! CONVERSION uspesne prejde a to aj NAPRIEK TOMU, ze TARGET TYPE NIE JE POLYMORPHIC CLASS. C++ vyzaduje aby IBA SOURCE TYPE bol POLYMORPHIC TYPE.
	if (dynamic_cast<CNonVirtualBaseClass*>(PointerToBaseClass1)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1*] to TYPE [CNonVirtualBaseClass*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1*] to TYPE [CNonVirtualBaseClass*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! CONVERSION uspesne prejde a to aj NAPRIEK TOMU, ze TARGET TYPE NIE JE POLYMORPHIC CLASS. C++ vyzaduje aby IBA SOURCE TYPE bol POLYMORPHIC TYPE.
		dynamic_cast<CNonVirtualBaseClass&>(ReferenceToBaseClass1).NonVirtualMethod();

		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1&] to TYPE [CNonVirtualBaseClass&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CVirtualBaseClass1&] to TYPE [CNonVirtualBaseClass&] FAILED !" << endl;
	}

	/*
	PrintLineSeparator();

	CNonVirtualBaseClass*										PointerToNonVirtualBaseClass=&DerivedClass;

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze VARIABLE 'PointerToNonVirtualBaseClass' NEUKAZUJE na POLYMORPHIC TYPE a EXPRESSION, ktore NEUKAZUJE na POLYMORPHIC TYPE NEMOZE byt SOURCE TYPE pre DYNAMIC CAST CONVERSION.
	if (dynamic_cast<CDerivedClass*>(PointerToNonVirtualBaseClass)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CNonVirtualBaseClass*] to TYPE [CDerivedClass*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CNonVirtualBaseClass*] to TYPE [CDerivedClass*] FAILED !" << endl;
	}
	*/

	/*
	PrintLineSeparator();

	CNonVirtualBaseClass&										ReferenceToNonVirtualBaseClass=DerivedClass;

	try
	{
		// !!! COMPILER hodi ERROR, pretoze VARIABLE 'ReferenceToNonVirtualBaseClass' NEUKAZUJE na POLYMORPHIC TYPE a EXPRESSION, ktore NEUKAZUJE na POLYMORPHIC TYPE NEMOZE byt SOURCE TYPE pre DYNAMIC CAST CONVERSION.
		dynamic_cast<CDerivedClass&>(ReferenceToNonVirtualBaseClass);

		wcout << L"CONVERSION of TYPE [CNonVirtualBaseClass&] to TYPE [CDerivedClass&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CNonVirtualBaseClass&] to TYPE [CDerivedClass&] FAILED !" << endl;
	}
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastPrivateInheritanceConversions(void)
{
	PrintLineSeparator();

#ifdef _MSC_VER
	CDerivedClass												DerivedClass;
	CDerivedClass*												PointerToDerivedClass=&DerivedClass;
	CDerivedClass&												ReferenceToDerivedClass=DerivedClass;

	// !!!!! GCC COMPILER hodi ERROR, pretoze CLASS 'CDerivedClass' je DERIVED z CLASS 'CPrivateBaseClass' cez PRIVATE INHERITANCE.
	// !!!!! VISUAL C++ COMPILER vrati NULL POINTER, pretoze CLASS 'CDerivedClass' je DERIVED z CLASS 'CPrivateBaseClass' cez PRIVATE INHERITANCE.
	// !!!!! Podla knihy by COMPILER CONVERSION MAL UMOZNOVAT, ale GCC hodi COMPILATION ERROR.
	if (dynamic_cast<CPrivateBaseClass*>(PointerToDerivedClass)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CPrivateBaseClass*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CPrivateBaseClass*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!!!! GCC COMPILER hodi ERROR, pretoze CLASS 'CDerivedClass' je DERIVED z CLASS 'CPrivateBaseClass' cez PRIVATE INHERITANCE.
		// !!!!! VISUAL C++ COMPILER hodi EXCEPTION [bad_cast], pretoze CLASS 'CDerivedClass' je DERIVED z CLASS 'CPrivateBaseClass' cez PRIVATE INHERITANCE.
		// !!!!! Podla knihy by COMPILER CONVERSION MAL UMOZNOVAT, ale GCC hodi COMPILATION ERROR.
		dynamic_cast<CPrivateBaseClass&>(ReferenceToDerivedClass).PublicMethod();

		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [CPrivateBaseClass&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [CPrivateBaseClass&] FAILED !" << endl;
	}
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastConstConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CDerivedClass*												PointerToDerivedClass=&DerivedClass;
	CDerivedClass&												ReferenceToDerivedClass=DerivedClass;

	// !!! CONVERSION prejde, pretoze DYNAMIC CAST CONVERSIONS UMOZNUJU pridat CONST a VOLATILE SPECIFIERS.
	if (dynamic_cast<const CVirtualBaseClass1*>(PointerToDerivedClass)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CVirtualBaseClass1*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [CVirtualBaseClass1*] FAILED !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! CONVERSION prejde, pretoze DYNAMIC CAST CONVERSIONS UMOZNUJU pridat CONST a VOLATILE SPECIFIERS.
		dynamic_cast<const CVirtualBaseClass1&>(ReferenceToDerivedClass).VirtualMethod();

		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [const CVirtualBaseClass1&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass&] to TYPE [const CVirtualBaseClass1&] FAILED !" << endl;
	}

	/*
	PrintLineSeparator();

	const CVirtualBaseClass1*									ConstPointerToBaseClass1=&DerivedClass;

	// !!!!! CONVERSION ZLYHA, pretoze DYNAMIC CAST CONVERSIONS NEUMOZNUJU ODOBERAT CONST a VOLATILE SPECIFIERS.
	if (dynamic_cast<CDerivedClass*>(ConstPointerToBaseClass1)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [const CVirtualBaseClass1*] to TYPE [CDerivedClass*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [const CVirtualBaseClass1*] to TYPE [CDerivedClass*] FAILED !" << endl;
	}

	PrintLineSeparator();

	const CVirtualBaseClass1&									ConstReferenceToBaseClass1=DerivedClass;

	try
	{
		// !!!!! CONVERSION ZLYHA, pretoze DYNAMIC CAST CONVERSIONS NEUMOZNUJU ODOBERAT CONST a VOLATILE SPECIFIERS.
		dynamic_cast<CDerivedClass&>(ConstReferenceToBaseClass1).MethodInDerivedClass();

		wcout << L"CONVERSION of TYPE [const CVirtualBaseClass1&] to TYPE [CDerivedClass&] SUCCEEDED !" << endl;
	}
	catch(const bad_cast&)
	{
		wcout << L"CONVERSION of TYPE [const CVirtualBaseClass1&] to TYPE [CDerivedClass&] FAILED !" << endl;
	}
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDynamicCastVoidConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CDerivedClass*												PointerToDerivedClass=&DerivedClass;

	// CONVERSION uspesne prejde, pretoze DYNAMIC CAST CONVERSION podporuje CONVERSIONS na TYPE [void*].
	if (dynamic_cast<void*>(PointerToDerivedClass)!=nullptr)
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [void*] SUCCEEDED !" << endl;
	}
	else
	{
		wcout << L"CONVERSION of TYPE [CDerivedClass*] to TYPE [void*] FAILED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStaticCastDerivedToBaseConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CDerivedClass*												PointerToDerivedClass=&DerivedClass;
	CDerivedClass&												ReferenceToDerivedClass=DerivedClass;

	// !!! STATIC CAST OPERATORS UMOZNUJU UPCAST CONVERSIONS z DERIVED CLASSES na BASE CLASSES.
	static_cast<CVirtualBaseClass1*>(PointerToDerivedClass)->VirtualMethod();

	PrintLineSeparator();

	// !!! STATIC CAST OPERATORS UMOZNUJU UPCAST CONVERSIONS z DERIVED CLASSES na BASE CLASSES.
	static_cast<CVirtualBaseClass1&>(ReferenceToDerivedClass).VirtualMethod();

	/*
	PrintLineSeparator();

	// !!!!! COMPILER vrati COMPILATION ERROR, pretoze CLASS 'CDerivedClass' NIE JE DERIVED z CLASS 'CVirtualBaseClass2'.
	static_cast<CVirtualBaseClass2*>(PointerToDerivedClass)->VirtualMethod();

	PrintLineSeparator();

	// !!!!! COMPILER vrati COMPILATION ERROR, pretoze CLASS 'CDerivedClass' NIE JE DERIVED z CLASS 'CVirtualBaseClass2'.
	static_cast<CVirtualBaseClass2&>(ReferenceToDerivedClass).VirtualMethod();
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStaticCastBaseToDerivedConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CVirtualBaseClass1*											PointerToBaseClass1=&DerivedClass;
	CVirtualBaseClass1&											ReferenceToBaseClass1=DerivedClass;

	// !!! STATIC CAST OPERATORS UMOZNUJU DOWNCAST CONVERSIONS z BASE CLASSES na DERIVED CLASSES.
	// !!!!! Na ROZDIEL od DYNAMIC CAST OPERATORS STATIC CAST OPERATORS NEVYKONAVAJU KONTROLU ci CONVERSION bola uspesna.
	static_cast<CDerivedClass*>(PointerToBaseClass1)->MethodInDerivedClass();

	PrintLineSeparator();

	// !!! STATIC CAST OPERATORS UMOZNUJU DOWNCAST CONVERSIONS z BASE CLASSES na DERIVED CLASSES.
	// !!!!! Na ROZDIEL od DYNAMIC CAST OPERATORS STATIC CAST OPERATORS NEVYKONAVAJU KONTROLU ci CONVERSION bola uspesna.
	static_cast<CDerivedClass&>(ReferenceToBaseClass1).MethodInDerivedClass();

	/*
	PrintLineSeparator();

	CVirtualBaseClass1											BaseClass1;
	CVirtualBaseClass1*											DirectPointerToBaseClass1=&BaseClass1;
	CVirtualBaseClass1&											DirectReferenceToBaseClass1=BaseClass1;

	// !!!!! Tato CONVERSION sposobi RUNTIME ERROR, pretoze VARIABLE 'DirectPointerToBaseClass1' odkazuje na OBJECT TYPE 'CVirtualBaseClass1' a NIE na OBJECT TYPE 'CDerivedClass'.
	static_cast<CDerivedClass*>(DirectPointerToBaseClass1)->MethodInDerivedClass();

	PrintLineSeparator();

	// !!!!! Tato CONVERSION sposobi RUNTIME ERROR, pretoze VARIABLE 'DirectReferenceToBaseClass1' odkazuje na OBJECT TYPE 'CVirtualBaseClass1' a NIE na OBJECT TYPE 'CDerivedClass'.
	static_cast<CDerivedClass&>(DirectReferenceToBaseClass1).MethodInDerivedClass();
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStaticCastPolymorficNonPolymorficTypesConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CDerivedClass*												PointerToDerivedClass=&DerivedClass;
	CDerivedClass&												ReferenceToDerivedClass=DerivedClass;
	CNonVirtualBaseClass*										PointerToNonVirtualBaseClass=&DerivedClass;
	CNonVirtualBaseClass&										ReferenceToNonVirtualBaseClass=DerivedClass;

	// !!! CONVERSION prejde, pretoze CLASS 'CDerivedClass' je DERIVED z NON-VIRTUAL CLASS 'CNonVirtualBaseClass'.
	static_cast<CNonVirtualBaseClass*>(PointerToDerivedClass)->NonVirtualMethod();

	PrintLineSeparator();

	// !!! CONVERSION prejde, pretoze CLASS 'CDerivedClass' je DERIVED z NON-VIRTUAL CLASS 'CNonVirtualBaseClass'.
	static_cast<CNonVirtualBaseClass&>(ReferenceToDerivedClass).NonVirtualMethod();

	PrintLineSeparator();

	// !!!!! STATIC CAST CONVERSION PREJDE, pretoze STATIC CAST CONVERSION NEVYZADUJE, aby SOURCE EXPRESSION obsahovala POINTER/REFERENCE na POLYMORPHIC CLASS.
	static_cast<CDerivedClass*>(PointerToNonVirtualBaseClass)->MethodInDerivedClass();

	PrintLineSeparator();

	// !!!!! STATIC CAST CONVERSION PREJDE, pretoze STATIC CAST CONVERSION NEVYZADUJE, aby SOURCE EXPRESSION obsahovala POINTER/REFERENCE na POLYMORPHIC CLASS.
	static_cast<CDerivedClass&>(ReferenceToNonVirtualBaseClass).MethodInDerivedClass();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStaticCastPrivateInheritanceConversions(void)
{
	PrintLineSeparator();

	/*
	// !!! COMPILER vrati COMPILATION ERROR, pretoze CLASS 'CDerivedClass' je DERIVED z CLASS 'CPrivateBaseClass' cez PRIVATE INHERITANCE.
	static_cast<CPrivateBaseClass*>(PointerToDerivedClass)->PublicMethod();

	PrintLineSeparator();

	// !!! COMPILER vrati COMPILATION ERROR, pretoze CLASS 'CDerivedClass' je DERIVED z CLASS 'CPrivateBaseClass' cez PRIVATE INHERITANCE.
	static_cast<CPrivateBaseClass&>(ReferenceToDerivedClass).PublicMethod();
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStaticCastConstConversions(void)
{
	PrintLineSeparator();

	CDerivedClass												DerivedClass;
	CDerivedClass*												PointerToDerivedClass=&DerivedClass;
	CDerivedClass&												ReferenceToDerivedClass=DerivedClass;

	// !!! CONVERSION prejde, pretoze STATIC CAST CONVERSIONS UMOZNUJU pridat CONST a VOLATILE SPEFICIERS.
	static_cast<const CVirtualBaseClass1*>(PointerToDerivedClass)->VirtualMethod();

	PrintLineSeparator();

	// !!! CONVERSION prejde, pretoze STATIC CAST CONVERSIONS UMOZNUJU pridat CONST a VOLATILE SPEFICIERS.
	static_cast<const CVirtualBaseClass1&>(ReferenceToDerivedClass).VirtualMethod();

	/*
	PrintLineSeparator();

	const CVirtualBaseClass1*									ConstPointerToBaseClass1=&DerivedClass;

	// !!!!! CONVERSION ZLYHA, pretoze STATIC CAST CONVERSIONS NEUMOZNUJU ODOBERAT CONST a VOLATILE SPEFICIERS.
	static_cast<CDerivedClass*>(ConstPointerToBaseClass1)->VirtualMethod();

	const CVirtualBaseClass1&									ConstReferenceToBaseClass1=DerivedClass;

	// !!!!! CONVERSION ZLYHA, pretoze STATIC CAST CONVERSIONS NEUMOZNUJU ODOBERAT CONST a VOLATILE SPEFICIERS.
	static_cast<CDerivedClass&>(ConstReferenceToBaseClass1).VirtualMethod();
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeidForSimpleTypes(void)
{
	PrintLineSeparator();

	int															IntValueVariable;
	int*														IntPointerVariable=&IntValueVariable;
	int&														IntReferenceVariable=IntValueVariable;
	int&&														IntRValueReferenceVariable=move(IntValueVariable);
	wstring														StringValueVariable;
	wstring*													StringPointerVariable=&StringValueVariable;
	wstring&													StringReferenceVariable=StringValueVariable;
	wstring&&													StringRValueReferenceVariable=move(StringValueVariable);

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(IntValueVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(IntValueVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(IntPointerVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(IntPointerVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(IntReferenceVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(IntReferenceVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(IntRValueReferenceVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(IntRValueReferenceVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(100) [" << ConvertStringToWideString(GetTypeInfoName(typeid(100))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(StringValueVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(StringValueVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(StringPointerVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(StringPointerVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(StringReferenceVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(StringReferenceVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(StringRValueReferenceVariable) [" << ConvertStringToWideString(GetTypeInfoName(typeid(StringRValueReferenceVariable))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre EXPRESSION.
	wcout << L"TYPEID(wstring::c_str()) [" << ConvertStringToWideString(GetTypeInfoName(typeid(wstring(L"XXX").c_str()))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(int) [" << ConvertStringToWideString(GetTypeInfoName(typeid(int))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(int*) [" << ConvertStringToWideString(GetTypeInfoName(typeid(int*))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(int&) [" << ConvertStringToWideString(GetTypeInfoName(typeid(int&))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(int&&) [" << ConvertStringToWideString(GetTypeInfoName(typeid(int&&))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(wstring) [" << ConvertStringToWideString(GetTypeInfoName(typeid(wstring))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(wstring*) [" << ConvertStringToWideString(GetTypeInfoName(typeid(wstring*))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(wstring&) [" << ConvertStringToWideString(GetTypeInfoName(typeid(wstring&))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(wstring&&) [" << ConvertStringToWideString(GetTypeInfoName(typeid(wstring&&))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(int[100]) [" << ConvertStringToWideString(GetTypeInfoName(typeid(int[100]))) << L"] !" << endl;

	PrintLineSeparator();

	// Vracia TYPE INFORMATION pre TYPE.
	wcout << L"TYPEID(int[]) [" << ConvertStringToWideString(GetTypeInfoName(typeid(int[]))) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeidForNonVirtualInheritance(void)
{
	PrintLineSeparator();

	CTypeidNonVirtualDerived									NonVirtualDerived;
	CTypeidNonVirtualDerived*									PointerToNonVirtualDerived=&NonVirtualDerived;
	CTypeidNonVirtualDerived&									ReferenceToNonVirtualDerived=NonVirtualDerived;
	CTypeidNonVirtualBase*										PointerToNonVirtualBase=&NonVirtualDerived;
	CTypeidNonVirtualBase&										ReferenceToNonVirtualBase=NonVirtualDerived;

	wcout << L"TYPEID(NonVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(NonVirtualDerived))) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToNonVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToNonVirtualDerived))) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(ReferenceToNonVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToNonVirtualDerived))) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! CONVERSION NIE je POLYMORPHIC.
	// !!!!! VRATI TYPE INFORMATION o CLASS [CTypeidNonVirtualBase] NAMIESTO CLASS [CTypeidNonVirtualDerived] na ktory POINTER 'PointerToNonVirtualBase' referuje. Je to dosledok toho, ze CLASS [CTypeidNonVirtualBase] NIE JE POLYMORPHIC TYPE.
	wcout << L"TYPEID(*PointerToNonVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(*PointerToNonVirtualBase))) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! CONVERSION NIE je POLYMORPHIC.
	// !!!!! VRATI TYPE INFORMATION o CLASS [CTypeidNonVirtualBase*] NAMIESTO CLASS [CTypeidNonVirtualDerived*] na ktory POINTER 'PointerToNonVirtualBase' referuje. Je to dosledok toho, ze CLASS [CTypeidNonVirtualBase] NIE JE POLYMORPHIC TYPE.
	wcout << L"TYPEID(PointerToNonVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToNonVirtualBase))) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! CONVERSION NIE je POLYMORPHIC.
	// !!!!! VRATI TYPE INFORMATION o CLASS [CTypeidNonVirtualBase] NAMIESTO CLASS [CTypeidNonVirtualDerived] na ktory POINTER 'ReferenceToNonVirtualBase' referuje. Je to dosledok toho, ze CLASS [CTypeidNonVirtualBase] NIE JE POLYMORPHIC TYPE.
	wcout << L"TYPEID(ReferenceToNonVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToNonVirtualBase))) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeidForVirtualInheritance(void)
{
	PrintLineSeparator();

	CTypeidVirtualDerived										VirtualDerived;
	CTypeidVirtualDerived*										PointerToVirtualDerived=&VirtualDerived;
	CTypeidVirtualDerived&										ReferenceToVirtualDerived=VirtualDerived;
	CTypeidVirtualBase*											PointerToVirtualBase=&VirtualDerived;
	CTypeidVirtualBase&											ReferenceToVirtualBase=VirtualDerived;

	wcout << L"TYPEID(VirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(VirtualDerived))) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToVirtualDerived))) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(ReferenceToVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToVirtualDerived))) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! CONVERSION je POLYMORPHIC.
	// !!!!! VRATI TYPE INFORMATION o CLASS [CTypeidVirtualDerived] na ktory POINTER 'ReferenceToVirtualBase' referuje. Je to dosledok toho, ze CLASS [CTypeidVirtualBase] JE POLYMORPHIC a tym padom DOCHADZA k POLYMORPHIC TYPE IDENTIFICATION.
	wcout << L"TYPEID(*PointerToVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(*PointerToVirtualBase))) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! CONVERSION NIE je POLYMORPHIC.
	// !!!!! VRATI TYPE INFORMATION o CLASS [CTypeidVirtualBase*] NAMIESTO CLASS [CTypeidVirtualDerived*] na ktory POINTER 'PointerToVirtualBase' referuje a to AJ NAPRIEK TOMU, ze CLASS [CTypeidVirtualBase] JE POLYMORPHIC CLASS.
	// !!!!! Toto je SPECIALNE chovanie C++ pre POINTERS. Pre REFERERENCES sa vracia KOREKTNY TYPE INFORMATION o CLASS [CTypeidVirtualDerived].
	wcout << L"TYPEID(PointerToVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToVirtualBase))) << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! CONVERSION je POLYMORPHIC.
	// !!!!! VRATI TYPE INFORMATION o CLASS [CTypeidVirtualDerived] na ktory POINTER 'ReferenceToVirtualBase' referuje. Je to dosledok toho, ze CLASS [CTypeidVirtualBase] JE POLYMORPHIC a tym padom DOCHADZA k POLYMORPHIC TYPE IDENTIFICATION.
	wcout << L"TYPEID(ReferenceToVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToVirtualBase))) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TypeidForNullPointers(CTypeidNonVirtualBase* PointerToNonVirtualBase)
{
	wcout << L"TYPEID(PointerToNonVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToNonVirtualBase))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TypeidForNullPointers(CTypeidVirtualBase* PointerToVirtualBase)
{
	wcout << L"TYPEID(PointerToVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToVirtualBase))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TypeidForNullPointers(CTypeidNonVirtualDerived* PointerToNonVirtualDerived)
{
	wcout << L"TYPEID(PointerToNonVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToNonVirtualDerived))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TypeidForNullPointers(CTypeidVirtualDerived* PointerToVirtualDerived)
{
	wcout << L"TYPEID(PointerToVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToVirtualDerived))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TypeidForNullPointersByReference(CTypeidNonVirtualBase& ReferenceToNonVirtualBase)
{
	wcout << L"TYPEID(ReferenceToNonVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToNonVirtualBase))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TypeidForNullPointersByReference(CTypeidVirtualBase& ReferenceToVirtualBase)
{
	wcout << L"TYPEID(ReferenceToVirtualBase) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToVirtualBase))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TypeidForNullPointersByReference(CTypeidNonVirtualDerived& ReferenceToNonVirtualDerived)
{
	wcout << L"TYPEID(ReferenceToNonVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToNonVirtualDerived))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TypeidForNullPointersByReference(CTypeidVirtualDerived& ReferenceToVirtualDerived)
{
	wcout << L"TYPEID(ReferenceToVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(ReferenceToVirtualDerived))) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestTypeidForNullPointers(void)
{
	PrintLineSeparator();

	// !!! NEHODI EXCEPTION, ale vracia CLASS [nullptr_t].
	wcout << L"TYPEID(nullptr) [" << ConvertStringToWideString(GetTypeInfoName(typeid(nullptr))) << L"] !" << endl;

	PrintLineSeparator();

	// !!! NEHODI EXCEPTION, ale vracia TYPE [int].
	wcout << L"TYPEID(NULL) [" << ConvertStringToWideString(GetTypeInfoName(typeid(NULL))) << L"] !" << endl;

	PrintLineSeparator();

	CTypeidNonVirtualDerived*									PointerToNonVirtualDerived=nullptr;
	CTypeidVirtualDerived*										PointerToVirtualDerived=nullptr;

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze TYPEID pre POINTERS bez ohladu na to ci referuju na POLYMORPHIC, alebo NON-POLYMORPHIC TYPE je vykonavany v COMPILE TIME.
		wcout << L"TYPEID(PointerToNonVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToNonVirtualDerived))) << L"] !" << endl;
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze TYPEID pre POINTERS bez ohladu na to ci referuju na POLYMORPHIC, alebo NON-POLYMORPHIC TYPE je vykonavany v COMPILE TIME.
		wcout << L"TYPEID(PointerToVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(PointerToVirtualDerived))) << L"] !" << endl;
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze TYPEID pre POINTERS bez ohladu na to ci referuju na POLYMORPHIC, alebo NON-POLYMORPHIC TYPE je vykonavany v COMPILE TIME.
		TypeidForNullPointers(static_cast<CTypeidNonVirtualBase*>(PointerToNonVirtualDerived));
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze TYPEID pre POINTERS bez ohladu na to ci referuju na POLYMORPHIC, alebo NON-POLYMORPHIC TYPE je vykonavany v COMPILE TIME.
		TypeidForNullPointers(static_cast<CTypeidVirtualBase*>(PointerToVirtualDerived));
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze TYPEID pre POINTERS bez ohladu na to ci referuju na POLYMORPHIC, alebo NON-POLYMORPHIC TYPE je vykonavany v COMPILE TIME.
		TypeidForNullPointers(PointerToNonVirtualDerived);
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze TYPEID pre POINTERS bez ohladu na to ci referuju na POLYMORPHIC, alebo NON-POLYMORPHIC TYPE je vykonavany v COMPILE TIME.
		TypeidForNullPointers(PointerToVirtualDerived);
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze aj ked v EXPRESSION [typeid(*PointerToNonVirtualDerived)] VARIABLE 'PointerToNonVirtualDerived' ukazuje na NULL POINTER, CLASS [CTypeidNonVirtualDerived] je NON-POLYMORPHIC a TYPEID pre NON-POLYMORPHIC CLASSES je vykonavany v COMPILE TIME.
		wcout << L"TYPEID(PointerToNonVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(*PointerToNonVirtualDerived))) << L"] !" << endl;
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! HODI EXCEPTION [bad_cast], pretoze EXPRESSION [typeid(*PointerToVirtualDerived)] je vykonana v RUN TIME a VARIABLE 'PointerToVirtualDerived' odkazuje na NULL POINTER.
		wcout << L"TYPEID(PointerToVirtualDerived) [" << ConvertStringToWideString(GetTypeInfoName(typeid(*PointerToVirtualDerived))) << L"] !" << endl;
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze aj ked v EXPRESSION [*static_cast<CTypeidNonVirtualBase*>(nullptr)] referuje na NULL POINTER, CLASS [CTypeidNonVirtualDerived] je NON-POLYMORPHIC a TYPEID pre NON-POLYMORPHIC CLASSES je vykonavany v COMPILE TIME.
		TypeidForNullPointersByReference(*static_cast<CTypeidNonVirtualBase*>(nullptr));
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		// !!!!! Vo VISUAL STUDIO HODI EXCEPTION [bad_cast], pretoze EXPRESSION [*static_cast<CTypeidVirtualBase*>(nullptr)] je vykonana v RUN TIME.
		// !!!!! V GCC CODE hodi RUNTIME ERROR.
		TypeidForNullPointersByReference(*static_cast<CTypeidVirtualBase*>(nullptr));
#endif
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
		// !!!!! NEHODI EXCEPTION, pretoze aj ked v EXPRESSION [*PointerToNonVirtualDerived] VARIABLE 'PointerToNonVirtualDerived' ukazuje na NULL POINTER, lebo CLASS [CTypeidNonVirtualDerived] je NON-POLYMORPHIC a TYPEID pre NON-POLYMORPHIC CLASSES je vykonavany v COMPILE TIME.
		TypeidForNullPointersByReference(*PointerToNonVirtualDerived);
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();

	try
	{
#ifdef _MSC_VER
		// !!!!! Vo VISUAL STUDIO HODI EXCEPTION [bad_cast], pretoze EXPRESSION [*PointerToVirtualDerived] je vykonana v RUN TIME a VARIABLE 'PointerToVirtualDerived' odkazuje na NULL POINTER.
		// !!!!! V GCC CODE hodi RUNTIME ERROR.
		TypeidForNullPointersByReference(*PointerToVirtualDerived);
#endif
	}
	catch(const bad_typeid&)
	{
		wprintf_s(L"BAD TYPEID EXCEPTION !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeidTypeInfoComparison1(void)
{
	PrintLineSeparator();

	CTypeidNonVirtualDerived									NonVirtualDerived1;
	CTypeidNonVirtualDerived									NonVirtualDerived2;
	CTypeidNonVirtualBase										NonVirtualBase1;
	CTypeidNonVirtualBase										NonVirtualBase2;
	CTypeidNonVirtualBase*										PointerToNonVirtualBasePointingToDerived1=&NonVirtualDerived1;
	CTypeidNonVirtualBase*										PointerToNonVirtualBasePointingToDerived2=&NonVirtualDerived2;
	CTypeidNonVirtualBase*										PointerToNonVirtualBasePointingToBase1=&NonVirtualBase1;
	CTypeidNonVirtualBase*										PointerToNonVirtualBasePointingToBase2=&NonVirtualBase2;
	CTypeidNonVirtualBase&										ReferenceToNonVirtualBasePointingToDerived1=NonVirtualDerived1;
	CTypeidNonVirtualBase&										ReferenceToNonVirtualBasePointingToDerived2=NonVirtualDerived2;
	CTypeidNonVirtualBase&										ReferenceToNonVirtualBasePointingToBase1=NonVirtualBase1;
	CTypeidNonVirtualBase&										ReferenceToNonVirtualBasePointingToBase2=NonVirtualBase2;

	wcout << L"TYPEID(NonVirtualBase1)==TYPEID(NonVirtualBase2) [" << (typeid(NonVirtualBase1)==typeid(NonVirtualBase2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(NonVirtualBase1)!=TYPEID(NonVirtualBase2) [" << (typeid(NonVirtualBase1)!=typeid(NonVirtualBase2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToNonVirtualBasePointingToDerived1)==TYPEID(PointerToNonVirtualBasePointingToDerived2) [" << (typeid(PointerToNonVirtualBasePointingToDerived1)==typeid(PointerToNonVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToNonVirtualBasePointingToBase1)==TYPEID(PointerToNonVirtualBasePointingToBase2) [" << (typeid(PointerToNonVirtualBasePointingToDerived1)==typeid(PointerToNonVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(ReferenceToNonVirtualBasePointingToDerived1)==TYPEID(ReferenceToNonVirtualBasePointingToDerived2) [" << (typeid(ReferenceToNonVirtualBasePointingToDerived1)==typeid(ReferenceToNonVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(ReferenceToNonVirtualBasePointingToBase1)==TYPEID(ReferenceToNonVirtualBasePointingToBase2) [" << (typeid(ReferenceToNonVirtualBasePointingToDerived1)==typeid(ReferenceToNonVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToNonVirtualBasePointingToDerived1)==TYPEID(PointerToNonVirtualBasePointingToBase1) [" << (typeid(PointerToNonVirtualBasePointingToDerived1)==typeid(PointerToNonVirtualBasePointingToBase1)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToNonVirtualBasePointingToDerived2)==TYPEID(PointerToNonVirtualBasePointingToBase2) [" << (typeid(PointerToNonVirtualBasePointingToDerived2)==typeid(PointerToNonVirtualBasePointingToBase2)) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vrati TRUE aj ked OBE VARIABLES refereuju na INY OBJECT. Je to dosledok toho, ze obe CLASSES su NON-POLYMORPHIC.
	wcout << L"TYPEID(ReferenceToNonVirtualBasePointingToDerived1)==TYPEID(ReferenceToNonVirtualBasePointingToBase1) [" << (typeid(ReferenceToNonVirtualBasePointingToDerived1)==typeid(ReferenceToNonVirtualBasePointingToBase1)) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vrati TRUE aj ked OBE VARIABLES refereuju na INY OBJECT. Je to dosledok toho, ze obe CLASSES su NON-POLYMORPHIC.
	wcout << L"TYPEID(ReferenceToNonVirtualBasePointingToDerived2)==TYPEID(ReferenceToNonVirtualBasePointingToBase2) [" << (typeid(ReferenceToNonVirtualBasePointingToDerived2)==typeid(ReferenceToNonVirtualBasePointingToBase2)) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeidTypeInfoComparison2(void)
{
	PrintLineSeparator();

	CTypeidVirtualDerived										VirtualDerived1;
	CTypeidVirtualDerived										VirtualDerived2;
	CTypeidVirtualBase											VirtualBase1;
	CTypeidVirtualBase											VirtualBase2;
	CTypeidVirtualBase*											PointerToVirtualBasePointingToDerived1=&VirtualDerived1;
	CTypeidVirtualBase*											PointerToVirtualBasePointingToDerived2=&VirtualDerived2;
	CTypeidVirtualBase*											PointerToVirtualBasePointingToBase1=&VirtualBase1;
	CTypeidVirtualBase*											PointerToVirtualBasePointingToBase2=&VirtualBase2;
	CTypeidVirtualBase&											ReferenceToVirtualBasePointingToDerived1=VirtualDerived1;
	CTypeidVirtualBase&											ReferenceToVirtualBasePointingToDerived2=VirtualDerived2;
	CTypeidVirtualBase&											ReferenceToVirtualBasePointingToBase1=VirtualBase1;
	CTypeidVirtualBase&											ReferenceToVirtualBasePointingToBase2=VirtualBase2;

	wcout << L"TYPEID(VirtualBase1)==TYPEID(VirtualBase2) [" << (typeid(VirtualBase1)==typeid(VirtualBase2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(VirtualBase1)!=TYPEID(VirtualBase2) [" << (typeid(VirtualBase1)!=typeid(VirtualBase2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToVirtualBasePointingToDerived1)==TYPEID(PointerToVirtualBasePointingToDerived2) [" << (typeid(PointerToVirtualBasePointingToDerived1)==typeid(PointerToVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToVirtualBasePointingToBase1)==TYPEID(PointerToVirtualBasePointingToBase2) [" << (typeid(PointerToVirtualBasePointingToDerived1)==typeid(PointerToVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(ReferenceToVirtualBasePointingToDerived1)==TYPEID(ReferenceToVirtualBasePointingToDerived2) [" << (typeid(ReferenceToVirtualBasePointingToDerived1)==typeid(ReferenceToVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(ReferenceToVirtualBasePointingToBase1)==TYPEID(ReferenceToVirtualBasePointingToBase2) [" << (typeid(ReferenceToVirtualBasePointingToDerived1)==typeid(ReferenceToVirtualBasePointingToDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToVirtualBasePointingToDerived1)==TYPEID(PointerToVirtualBasePointingToBase1) [" << (typeid(PointerToVirtualBasePointingToDerived1)==typeid(PointerToVirtualBasePointingToBase1)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPEID(PointerToVirtualBasePointingToDerived2)==TYPEID(PointerToVirtualBasePointingToBase2) [" << (typeid(PointerToVirtualBasePointingToDerived2)==typeid(PointerToVirtualBasePointingToBase2)) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vrati FALSE, lebo obe CLASSES su POLYMORPHIC a obe VARIABLES referuju na OBJECT INEHO TYPE.
	wcout << L"TYPEID(ReferenceToVirtualBasePointingToDerived1)==TYPEID(ReferenceToVirtualBasePointingToBase1) [" << (typeid(ReferenceToVirtualBasePointingToDerived1)==typeid(ReferenceToVirtualBasePointingToBase1)) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vrati FALSE, lebo obe CLASSES su POLYMORPHIC a obe VARIABLES referuju na OBJECT INEHO TYPE.
	wcout << L"TYPEID(ReferenceToVirtualBasePointingToDerived2)==TYPEID(ReferenceToVirtualBasePointingToBase2) [" << (typeid(ReferenceToVirtualBasePointingToDerived2)==typeid(ReferenceToVirtualBasePointingToBase2)) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring CompareTypeInfo(const type_info& TypeInfo1, const type_info& TypeInfo2)
{
	if (TypeInfo1.before(TypeInfo2)==false)
	{
		if (TypeInfo2.before(TypeInfo1)==false)
		{
			return(L"==");
		}
		else
		{
			return(L">");
		}
	}
	else
	{
		return(L"<");
	}
}
//-----------------------------------------------------------------------------
void TestTypeidTypeInfoSorting(void)
{
	PrintLineSeparator();

	CTypeidVirtualDerived										VirtualDerived1;
	CTypeidVirtualDerived										VirtualDerived2;
	CTypeidVirtualBase											VirtualBase1;
	CTypeidVirtualBase											VirtualBase2;

 	wcout << L"COMPARE(TYPEID(VirtualDerived1),TYPEID(VirtualDerived2)) [" << CompareTypeInfo(typeid(VirtualDerived1),typeid(VirtualDerived2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"COMPARE(TYPEID(VirtualBase1),TYPEID(VirtualBase2)) [" << CompareTypeInfo(typeid(VirtualBase1),typeid(VirtualBase2)) << L"] !" << endl;

	PrintLineSeparator();

 	wcout << L"COMPARE(TYPEID(VirtualDerived1),TYPEID(VirtualBase1)) [" << CompareTypeInfo(typeid(VirtualDerived1),typeid(VirtualBase1)) << L"] !" << endl;

	PrintLineSeparator();

 	wcout << L"COMPARE(TYPEID(VirtualBase1),TYPEID(VirtualDerived1)) [" << CompareTypeInfo(typeid(VirtualBase1),typeid(VirtualDerived1)) << L"] !" << endl;

	PrintLineSeparator();

 	wcout << L"COMPARE(TYPEID(VirtualDerived2),TYPEID(VirtualBase2)) [" << CompareTypeInfo(typeid(VirtualDerived2),typeid(VirtualBase2)) << L"] !" << endl;

	PrintLineSeparator();

 	wcout << L"COMPARE(TYPEID(VirtualBase2),TYPEID(VirtualDerived2)) [" << CompareTypeInfo(typeid(VirtualBase2),typeid(VirtualDerived2)) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeidTypeInfoHashCode(void)
{
	PrintLineSeparator();

	CTypeidNonVirtualDerived									NonVirtualDerived1;
	CTypeidNonVirtualDerived									NonVirtualDerived2;
	CTypeidNonVirtualBase										NonVirtualBase1;
	CTypeidNonVirtualBase										NonVirtualBase2;
	CTypeidVirtualDerived										VirtualDerived1;
	CTypeidVirtualDerived										VirtualDerived2;
	CTypeidVirtualBase											VirtualBase1;
	CTypeidVirtualBase											VirtualBase2;
	CTypeidNonVirtualDerived*									PointerToNonVirtualDerived1=&NonVirtualDerived1;
	CTypeidNonVirtualDerived*									PointerToNonVirtualDerived2=&NonVirtualDerived2;
	CTypeidNonVirtualBase*										PointerToNonVirtualBase1=&NonVirtualBase1;
	CTypeidNonVirtualBase*										PointerToNonVirtualBase2=&NonVirtualBase2;
	CTypeidVirtualDerived*										PointerToVirtualDerived1=&VirtualDerived1;
	CTypeidVirtualDerived*										PointerToVirtualDerived2=&VirtualDerived2;
	CTypeidVirtualBase*											PointerToVirtualBase1=&VirtualBase1;
	CTypeidVirtualBase*											PointerToVirtualBase2=&VirtualBase2;
	CTypeidNonVirtualDerived&									ReferenceToNonVirtualDerived1=NonVirtualDerived1;
	CTypeidNonVirtualDerived&									ReferenceToNonVirtualDerived2=NonVirtualDerived2;
	CTypeidNonVirtualBase&										ReferenceToNonVirtualBase1=NonVirtualDerived2;
	CTypeidNonVirtualBase&										ReferenceToNonVirtualBase2=NonVirtualDerived2;
	CTypeidVirtualDerived&										ReferenceToVirtualDerived1=VirtualDerived1;
	CTypeidVirtualDerived&										ReferenceToVirtualDerived2=VirtualDerived2;
	CTypeidVirtualBase&											ReferenceToVirtualBase1=VirtualBase1;
	CTypeidVirtualBase&											ReferenceToVirtualBase2=VirtualBase2;

 	wcout << L"HASH_CODE(TYPEID(NonVirtualDerived1)) [" << typeid(NonVirtualDerived1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(NonVirtualDerived2)) [" << typeid(NonVirtualDerived2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(NonVirtualBase1)) [" << typeid(NonVirtualBase1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(NonVirtualBase2)) [" << typeid(NonVirtualBase2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

 	wcout << L"HASH_CODE(TYPEID(VirtualDerived1)) [" << typeid(VirtualDerived1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(VirtualDerived2)) [" << typeid(VirtualDerived2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(VirtualBase1)) [" << typeid(VirtualBase1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(VirtualBase2)) [" << typeid(VirtualBase2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToNonVirtualDerived1)) [" << typeid(PointerToNonVirtualDerived1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToNonVirtualDerived2)) [" << typeid(PointerToNonVirtualDerived2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToNonVirtualBase1)) [" << typeid(PointerToNonVirtualBase1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToNonVirtualBase2)) [" << typeid(PointerToNonVirtualBase2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToVirtualDerived1)) [" << typeid(PointerToVirtualDerived1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToVirtualDerived2)) [" << typeid(PointerToVirtualDerived2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToVirtualBase1)) [" << typeid(PointerToVirtualBase1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(PointerToVirtualBase2)) [" << typeid(PointerToVirtualBase2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToNonVirtualDerived1)) [" << typeid(ReferenceToNonVirtualDerived1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToNonVirtualDerived2)) [" << typeid(ReferenceToNonVirtualDerived2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToNonVirtualBase1)) [" << typeid(ReferenceToNonVirtualBase1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToNonVirtualBase2)) [" << typeid(ReferenceToNonVirtualBase2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToVirtualDerived1)) [" << typeid(ReferenceToVirtualDerived1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToVirtualDerived2)) [" << typeid(ReferenceToVirtualDerived2).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToVirtualBase1)) [" << typeid(ReferenceToVirtualBase1).hash_code() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH_CODE(TYPEID(ReferenceToVirtualBase2)) [" << typeid(ReferenceToVirtualBase2).hash_code() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeIndex(void)
{
	PrintLineSeparator();

	wcout << L"INT HASH [" << typeid(int).hash_code() << L"] !\n";
	wcout << L"INT HASH TYPE INFO [" << type_index(typeid(int)).hash_code() << L"] !\n";
	wcout << L"INT==INT [" << ((type_index(typeid(int))==type_index(typeid(int))) ? "TRUE" : "FALSE") << L"] !\n";
	wcout << L"INT<DOUBLE [" << ((type_index(typeid(int))<type_index(typeid(double))) ? "TRUE" : "FALSE") << L"] !\n";
	wcout << L"INT>DOUBLE [" << ((type_index(typeid(int))>type_index(typeid(double))) ? "TRUE" : "FALSE") << L"] !\n";

	PrintLineSeparator();

	// !!! CLASS [type_info] je mozne pouzit ako KEY v MAP.
    map<type_index,wstring>										Map;
 
    Map[type_index(typeid(int))]=ConvertStringToWideString(GetTypeInfoName(typeid(int)));
    Map[type_index(typeid(double))]=ConvertStringToWideString(GetTypeInfoName(typeid(double)));
    Map[type_index(typeid(CTypeidVirtualDerived))]=ConvertStringToWideString(GetTypeInfoName(typeid(CTypeidVirtualDerived)));
    Map[type_index(typeid(wstring))]=ConvertStringToWideString(GetTypeInfoName(typeid(wstring)));

	for(const map<type_index,wstring>::value_type& Value : Map)
	{
		wcout << L"HASH [" << Value.first.hash_code()  << "] VALUE [" << Map[Value.first].c_str() << L"] !\n";
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestDynamicCastDerivedToBaseConversions();
	//TestDynamicCastBaseToDerivedConversions();
	//TestDynamicCastNonUniqueConversion();
	//TestDynamicCastSiblingConversion();
	//TestDynamicCastPolymorficNonPolymorficTypesConversions();
	//TestDynamicCastPrivateInheritanceConversions();
	//TestDynamicCastConstConversions();
	//TestDynamicCastVoidConversions();
	//TestStaticCastDerivedToBaseConversions();
	//TestStaticCastBaseToDerivedConversions();
	//TestStaticCastPolymorficNonPolymorficTypesConversions();
	//TestStaticCastPrivateInheritanceConversions();
	//TestStaticCastConstConversions();
	//TestTypeidForSimpleTypes();
	//TestTypeidForNonVirtualInheritance();
	//TestTypeidForVirtualInheritance();
	//TestTypeidForNullPointers();
	//TestTypeidTypeInfoComparison1();
	//TestTypeidTypeInfoComparison2();
	//TestTypeidTypeInfoSorting();
	//TestTypeidTypeInfoHashCode();
	TestTypeIndex();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------