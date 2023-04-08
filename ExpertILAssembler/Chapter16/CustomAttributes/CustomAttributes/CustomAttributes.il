//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly extern System.Runtime.Serialization {auto}
.assembly CustomAttributes {}
.module CustomAttributes.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
#include "TestClass.il"
#include "MyCustomAttribute.il"
//-------------------------------------------------------------------------------------------------------
.namespace CustomAttributes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CCustomAttributes extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
            .locals							init (class CustomAttributes.CTestClass TestClass)

			newobj							instance void CustomAttributes.CTestClass::.ctor()
			stloc							TestClass

			ldloc							TestClass
			call							instance void CustomAttributes.CTestClass::Test1()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
            .locals							init (class CustomAttributes.CTestClass TestClass)

			newobj							instance void CustomAttributes.CTestClass::.ctor()
			stloc							TestClass

			ldloc							TestClass
			call							instance void CustomAttributes.CTestClass::Test2()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
            .locals							init (class CustomAttributes.CTestClass TestClass)

			newobj							instance void CustomAttributes.CTestClass::.ctor()
			stloc							TestClass

			ldloc							TestClass
			call							instance void CustomAttributes.CTestClass::Test3()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
            .locals							init (class CustomAttributes.CTestClass TestClass)

			newobj							instance void CustomAttributes.CTestClass::.ctor()
			stloc							TestClass

			ldloc							TestClass
			call							instance void CustomAttributes.CTestClass::Test4()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test5() cil managed
		{
            .locals							init (class CustomAttributes.CTestClass TestClass)

			newobj							instance void CustomAttributes.CTestClass::.ctor()
			stloc							TestClass

			ldloc							TestClass
			call							instance void CustomAttributes.CTestClass::Test5()

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test6() cil managed
		{
            .locals							init (class CustomAttributes.CTestClass TestClass)

			newobj							instance void CustomAttributes.CTestClass::.ctor()
			stloc							TestClass

			ldloc							TestClass
			call							instance void CustomAttributes.CTestClass::Test6()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void CustomAttributes.CCustomAttributes::Test1()
			//call							void CustomAttributes.CCustomAttributes::Test2()
			//call							void CustomAttributes.CCustomAttributes::Test3()
			//call							void CustomAttributes.CCustomAttributes::Test4()
			call							void CustomAttributes.CCustomAttributes::Test5()
			//call							void CustomAttributes.CCustomAttributes::Test6()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
