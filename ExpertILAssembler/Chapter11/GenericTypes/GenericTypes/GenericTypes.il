//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly GenericTypes {}
.module GenericTypes.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
#include "SimpleGenericClass.il"
#include "SimpleGenericValueType.il"
#include "MultiParameterGenericClass.il"
#include "GenericInheritance.il"
#include "Constraints1.il"
#include "Constraints2.il"
#include "GenericTypeVariableParametersMethods.il"
#include "GenericClassMembers.il"
#include "GenericNestedClasses1.il"
#include "GenericNestedClasses2.il"
#include "GenericNestedClasses3.il"
//-------------------------------------------------------------------------------------------------------
.namespace GenericTypes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CGenericTypes extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void TryGenericClassWithVariableParameterMethods() cil managed
		{
			.locals							init (class GenericTypes.CGenericTypeVariableParametersMethods<string> Object)

			// !!! GENERIC TYPES NESMU mat METHODS s VARIABLE PARAMETERS, inak je generovana EXCEPTION [TypeLoadException].
			newobj							instance void class GenericTypes.CGenericTypeVariableParametersMethods<string>::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CGenericTypeVariableParametersMethods<string>::SetField(!0)

			ldloc							Object
			call							instance void class GenericTypes.CGenericTypeVariableParametersMethods<string>::PrintField()
		}		
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
            .locals							init (class GenericTypes.CGenericClass<string> Object)

			newobj							instance void class GenericTypes.CGenericClass<string>::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CGenericClass<string>::SetField(!0)

			ldloc							Object
			call							instance void class GenericTypes.CGenericClass<string>::PrintField()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
            .locals							init (class GenericTypes.CGenericClass<int32> Object)

			newobj							instance void class GenericTypes.CGenericClass<int32>::.ctor()
			stloc							Object

			ldloc							Object
			ldc.i4							12
			call							instance void class GenericTypes.CGenericClass<int32>::SetField(!0)

			ldloc							Object
			call							instance void class GenericTypes.CGenericClass<int32>::PrintField()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
            .locals							init (valuetype GenericTypes.CGenericValueType<string> ValueType)

			ldloca							ValueType
			call							instance void valuetype GenericTypes.CGenericValueType<string>::.ctor()

			ldloca							ValueType
			ldstr							"Timmy Anderson"
			call							instance void valuetype GenericTypes.CGenericValueType<string>::SetField(!0)

			ldloca							ValueType
			call							instance void valuetype GenericTypes.CGenericValueType<string>::PrintField()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
            .locals							init (valuetype GenericTypes.CGenericValueType<int32> ValueType)

			ldloca							ValueType
			call							instance void valuetype GenericTypes.CGenericValueType<int32>::.ctor()

			ldloca							ValueType
			ldc.i4							12
			call							instance void valuetype GenericTypes.CGenericValueType<int32>::SetField(!0)

			ldloca							ValueType
			call							instance void valuetype GenericTypes.CGenericValueType<int32>::PrintField()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test5() cil managed
		{
            .locals							init (class GenericTypes.CMultiParameterGenericClass<string,int32> Object)

			newobj							instance void class GenericTypes.CMultiParameterGenericClass<string,int32>::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CMultiParameterGenericClass<string,int32>::SetField1(!0)

			ldloc							Object
			ldc.i4							12
			call							instance void class GenericTypes.CMultiParameterGenericClass<string,int32>::SetField2(!1)

			ldloc							Object
			call							instance void class GenericTypes.CMultiParameterGenericClass<string,int32>::PrintFields()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test6() cil managed
		{
            .locals							init (class GenericTypes.CMultiParameterGenericClass<string,int32> Object)

			newobj							instance void class GenericTypes.CMultiParameterGenericClass<string,int32>::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Jenny Thompson"
			ldc.i4							13
			// !!! PARAMETER TYPES, ktore su TYPE PARAMETERS sa definuju cez ORDINAL NUMBERS.
			call							instance void class GenericTypes.CMultiParameterGenericClass<string,int32>::SetFields(!0,!1)

			ldloc							Object
			call							instance void class GenericTypes.CMultiParameterGenericClass<string,int32>::PrintFields()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test7() cil managed
		{
            .locals							init (class GenericTypes.CGenericDerivedClass<string> Derived, class GenericTypes.CGenericBaseClass<string> Base, class GenericTypes.IGenericInterface1<string> Interface1, class GenericTypes.IGenericInterface2<string> Interface2, class GenericTypes.IGenericInterface3<string> Interface3, class GenericTypes.IGenericInterface4<string> Interface4)

			newobj							instance void class GenericTypes.CGenericDerivedClass<string>::.ctor()
			stloc							Derived

			ldloc							Derived
			castclass						class GenericTypes.CGenericBaseClass<string>
			stloc							Base

			ldloc							Derived
			castclass						class GenericTypes.IGenericInterface1<string>
			stloc							Interface1

			ldloc							Derived
			castclass						class GenericTypes.IGenericInterface2<string>
			stloc							Interface2

			ldloc							Derived
			castclass						class GenericTypes.IGenericInterface3<string>
			stloc							Interface3

			ldloc							Derived
			castclass						class GenericTypes.IGenericInterface4<string>
			stloc							Interface4

			ldloc							Base
			ldstr							"Timmy Anderson"
			// !!! METHOD GenericTypes.CGenericBaseClass<string>::SetField(!0) je definovana v BASE CLASS.
			call							instance void class GenericTypes.CGenericBaseClass<string>::SetField(!0)

			ldloc							Derived
			call							instance void class GenericTypes.CGenericClass<string>::PrintField()

			ldloc							Interface1
			ldstr							"Jenny Thompson"
			// !!! METHOD GenericTypes.IGenericInterface1<string>::PrintField1(!0) je definovana v INTERFACE 1.
			call							instance void class GenericTypes.IGenericInterface1<string>::PrintField1(!0)

			ldloc							Interface2
			ldstr							"Atreyu"
			// !!! METHOD GenericTypes.IGenericInterface2<string>::PrintField2(!0) je definovana v INTERFACE 2.
			call							instance void class GenericTypes.IGenericInterface2<string>::PrintField2(!0)

			ldloc							Interface3
			ldstr							"Bubu"
			// !!! METHOD GenericTypes.IGenericInterface3<string>::PrintField3(!0) je definovana v INTERFACE 3.
			call							instance void class GenericTypes.IGenericInterface3<string>::PrintField3(!0)

			ldloc							Interface4
			ldstr							"XCOM"
			// !!! METHOD GenericTypes.IGenericInterface4<string>::PrintField4(!0) je definovana v INTERFACE 4.
			call							instance void class GenericTypes.IGenericInterface4<string>::PrintField4(!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test8() cil managed
		{
			// !!! Prvy PARAMETER musi implementovat ICloneable. TYPE [string] implementuje IClonable.
			// !!! Druhy PARAMETER musi implementovat IFormattable. TYPE [int32] implementuje IFormattable.
            .locals							init (class GenericTypes.CContraints1<string,int32> Object)

			newobj							instance void class GenericTypes.CContraints1<string,int32>::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CContraints1<string,int32>::SetField1(!0)

			ldloc							Object
			ldc.i4							12
			call							instance void class GenericTypes.CContraints1<string,int32>::SetField2(!1)

			ldloc							Object
			call							instance void class GenericTypes.CContraints1<string,int32>::PrintFields()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test9() cil managed
		{
			// !!! Prvy PARAMETER musi implementovat ICloneable. TYPE [string] implementuje IClonable.
			// !!! Druhy PARAMETER musi implementovat IComparable'1<int32>. TYPE [string] implementuje IComparable'1<int32>.
			// !!!!! EXTREMNE DOLEZITY je fakt, ze zakladne GENERIC INTERFACES maju v nazve [XXX'ARITY]. Je to iba MENNA KONVENCIA, ktoru .NET zaviedol. CUSTOM CLASSES a INTERFACES ju nemusia dodrziavat.
            .locals							init (class GenericTypes.CContraints2<string,int32> Object)

			newobj							instance void class GenericTypes.CContraints2<string,int32>::.ctor()
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CContraints2<string,int32>::SetField1(!0)

			ldloc							Object
			ldc.i4							12
			call							instance void class GenericTypes.CContraints2<string,int32>::SetField2(!1)

			ldloc							Object
			call							instance void class GenericTypes.CContraints2<string,int32>::PrintFields()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test10() cil managed
		{
			.try
			{
				call						void GenericTypes.CGenericTypes::TryGenericClassWithVariableParameterMethods()
				leave						Exit
			}
			catch [mscorlib]System.Exception
			{
				call						void Helpers.CHelpers::PrintException(class [mscorlib]System.Exception Exception)
				leave						Exit
			}

		Exit:
			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test11() cil managed
		{
            .locals							init (class GenericTypes.CGenericClassMembers<string,int32,float32> Object, float32 Value)

			ldc.r4							123.456
			// !!! Mimo GENERIC TYPE je k MEMBERS nutne pristupovat tak, ze sa pouzije PLNA SIGNATURE, pricom TYPE PARAMETERS sa definuju cez SYNTAX [!PARAMETER_ORDINAL_NUMBER].
			newobj							instance void class GenericTypes.CGenericClassMembers<string,int32,float32>::.ctor(!2)
			stloc							Object

			ldloc							Object
			ldstr							"Timmy Anderson"
			ldc.i4							12
			// !!! Mimo GENERIC TYPE je k MEMBERS nutne pristupovat tak, ze sa pouzije PLNA SIGNATURE, pricom TYPE PARAMETERS sa definuju cez SYNTAX [!PARAMETER_ORDINAL_NUMBER].
			call							instance !2 class GenericTypes.CGenericClassMembers<string,int32,float32>::SetFieldsAndPrint(!0,!1)
			// Ulozi sa RETURN VALUE.
			stloc							Value

			ldstr							"RETURN VALUE [{0}] !"
			ldloc							Value
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test12() cil managed
		{
            .locals							init (class GenericTypes.CEnclosingNonGenericGeneric EnclosingObject)
            .locals							init (class GenericTypes.CEnclosingNonGenericGeneric/CNestedNonGenericGeneric<string> NestedObject)

			newobj							instance void class GenericTypes.CEnclosingNonGenericGeneric::.ctor()
			stloc							EnclosingObject

			newobj							instance void class GenericTypes.CEnclosingNonGenericGeneric/CNestedNonGenericGeneric<string>::.ctor()
			stloc							NestedObject

			ldloc							EnclosingObject
			call							instance void class GenericTypes.CEnclosingNonGenericGeneric::Test()

			ldloc							NestedObject
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CEnclosingNonGenericGeneric/CNestedNonGenericGeneric<string>::Test(!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test13() cil managed
		{
            .locals							init (class GenericTypes.CEnclosingGenericNonGeneric<string> EnclosingObject)
            .locals							init (class GenericTypes.CEnclosingGenericNonGeneric/CNestedGenericNonGeneric NestedObject)

			newobj							instance void class GenericTypes.CEnclosingNonGenericGeneric::.ctor()
			stloc							EnclosingObject

			newobj							instance void class GenericTypes.CEnclosingGenericNonGeneric/CNestedGenericNonGeneric::.ctor()
			stloc							NestedObject

			ldloc							EnclosingObject
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CEnclosingGenericNonGeneric<string>::Test(!0)

			ldloc							NestedObject
			call							instance void class GenericTypes.CEnclosingGenericNonGeneric/CNestedGenericNonGeneric::Test()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test14() cil managed
		{
            .locals							init (class GenericTypes.CEnclosingGenericGeneric<string> EnclosingObject)
            .locals							init (class GenericTypes.CEnclosingGenericGeneric/CNestedGenericGeneric<string> NestedObject)

			newobj							instance void class GenericTypes.CEnclosingGenericGeneric<string>::.ctor()
			stloc							EnclosingObject

			newobj							instance void class GenericTypes.CEnclosingGenericGeneric/CNestedGenericGeneric<string>::.ctor()
			stloc							NestedObject

			ldloc							EnclosingObject
			ldstr							"Timmy Anderson"
			call							instance void class GenericTypes.CEnclosingGenericGeneric<string>::Test(!0)

			ldloc							NestedObject
			ldstr							"Jenny Thompson"
			call							instance void class GenericTypes.CEnclosingGenericGeneric/CNestedGenericGeneric<string>::Test(!0)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void GenericTypes.CGenericTypes::Test1()
			//call							void GenericTypes.CGenericTypes::Test2()
			//call							void GenericTypes.CGenericTypes::Test3()
			//call							void GenericTypes.CGenericTypes::Test4()
			//call							void GenericTypes.CGenericTypes::Test5()
			//call							void GenericTypes.CGenericTypes::Test6()
			//call							void GenericTypes.CGenericTypes::Test7()
			//call							void GenericTypes.CGenericTypes::Test8()
			//call							void GenericTypes.CGenericTypes::Test9()
			//call							void GenericTypes.CGenericTypes::Test10()
			//call							void GenericTypes.CGenericTypes::Test11()
			//call							void GenericTypes.CGenericTypes::Test12()
			//call							void GenericTypes.CGenericTypes::Test13()
			call							void GenericTypes.CGenericTypes::Test14()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------