//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly ClassesAndValueTypesInSignatures {}
.module ClassesAndValueTypesInSignatures.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
//-------------------------------------------------------------------------------------------------------
.namespace ClassesAndValueTypesInSignatures
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CClassesAndValueTypesInSignatures extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! Pri prenose CLASSES, VALUE TYPES, STRINGS a OBJECTS je NUTNE pouzit SPECIALNU SYNTAX.
        .method public static void Signatures(object Object, string String, class [mscorlib]System.Text.StringBuilder Class, valuetype [mscorlib]System.DateTime ValueType) cil managed
		{
			ldstr							"OBJECT [{0}] !"
			ldarg							Object
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"STRING [{0}] !"
			ldarg							String
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CLASS [{0}] !"
			ldarg							Class
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"VALUE TYPE [{0}] !"
			ldarga							ValueType
			constrained.					[mscorlib]System.DateTime
			callvirt						instance string [mscorlib]System.Object::ToString()
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}		
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			ldstr							"PARAM 1"
			ldstr							"PARAM 2"
			ldstr							"PARAM 3"
			newobj							instance void [mscorlib]System.Text.StringBuilder::.ctor(string)
			ldc.i4							2013
			ldc.i4							10
			ldc.i4							26
			newobj							instance void [mscorlib]System.DateTime::.ctor(int32,int32,int32)

			call							void ClassesAndValueTypesInSignatures.CClassesAndValueTypesInSignatures::Signatures(object,string,class [mscorlib]System.Text.StringBuilder,valuetype [mscorlib]System.DateTime)

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------