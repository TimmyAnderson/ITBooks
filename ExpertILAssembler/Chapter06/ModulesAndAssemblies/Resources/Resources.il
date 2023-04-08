//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly Resources {}
.module Resources.exe
// !!! Vlozi do ASSEMBLY RESOURCE [SimpleResource.txt].
// !!!!! FILE [SimpleResource.txt] MUSI byt v COMPILE TIME PRISTUPNY, inak MSIL COMPILER hodi ERROR.
.mresource public SimpleResource.txt {}
.mresource public SimpleXMLResource.resources {}
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace Resources
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CResources extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint
			.locals init ([0] class [mscorlib]System.Resources.ResourceManager RM, [1] string ValueFromResource)

//			ldstr							"Hello WORLD !"
//			call							void [mscorlib]System.Console::WriteLine(string)


			ldstr							"SimpleXMLResource"
			ldtoken							Resources.CResources
			call							class [mscorlib]System.Type [mscorlib]System.Type::GetTypeFromHandle(valuetype [mscorlib]System.RuntimeTypeHandle)
			callvirt						instance class [mscorlib]System.Reflection.Assembly [mscorlib]System.Type::get_Assembly()
			newobj							instance void [mscorlib]System.Resources.ResourceManager::.ctor(string,class [mscorlib]System.Reflection.Assembly)
			// Ulozi RESOURCE MANAGER do LOCAL VARIABLE 0.
			stloc.0

			ldloc.0
			ldstr							"StringResource"
			callvirt						instance string [mscorlib]System.Resources.ResourceManager::GetString(string)

			// Ulozi hodnotu RESOURCE do LOCAL VARIABLE 1.
			stloc.1

			ldloc.1
			call							void [mscorlib]System.Console::WriteLine(string)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------