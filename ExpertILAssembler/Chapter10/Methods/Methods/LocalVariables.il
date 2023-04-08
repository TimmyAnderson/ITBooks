//-------------------------------------------------------------------------------------------------------
.namespace Methods
{
//-------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje VALUE TYPE s VIRTUAL METHODS.
    .class public auto ansi sealed CLocalVariables extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldstr							"CLocalVariables CONSTRUCTOR CALLED !"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! DERIVED CLASSES MUSIA EXPLICITNE volat BASE CONSTRUCTOR.
			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void TestLocalVariables() cil managed
		{
			.locals							init(int32 IntValue, float32 FloatValue, string StringValue, object ObjectValue)

			ldc.i4							123
			stloc							0

			ldc.r4							123.45
			stloc							1

			ldstr							"Timmy Anderson"
			stloc							2

			ldstr							"Jenny Thompson"
			stloc							3

			ldstr							"ACCESS through INDEX - IntValue [{0}] !"
			ldloc							0
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)
			
			ldstr							"ACCESS through INDEX - FloatValue [{0}] !"
			ldloc							1
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"ACCESS through INDEX - StringValue [{0}] !"
			ldloc							2
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"ACCESS through INDEX - ObjectValue [{0}] !"
			ldloc							3
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"ACCESS through NAME - IntValue [{0}] !"
			ldloc							IntValue
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)
			
			ldstr							"ACCESS through NAME - FloatValue [{0}] !"
			ldloc							FloatValue
			box								[mscorlib]System.Single
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"ACCESS through NAME - StringValue [{0}] !"
			ldloc							StringValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"ACCESS through NAME - ObjectValue [{0}] !"
			ldloc							ObjectValue
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void TestNestedLocalVariables() cil managed
		{
			.locals							init(string Name, int32 Age)

			ldstr							"Timmy Anderson"
			stloc							Name

			ldc.i4							12
			stloc							Age

			ldstr							"NAME [{0}], AGE [{1}] !"
			ldloc							Name
			ldloc							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			{
				// !!! LOCAL VARIABLES je mozne definovat aj v NESTED BLOCKS.
				.locals						init(string Name1, int32 Age1)

				ldstr						"Timmy Anderson"
				stloc						Name1

				ldc.i4						12
				stloc						Age1

				ldstr						"NESTED 1 - NAME [{0}], AGE [{1}] !"
				ldloc						Name1
				ldloc						Age1
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object,object)
				call						void [mscorlib]System.Console::WriteLine(string)
			}

			{
				// !!! LOCAL VARIABLES je mozne definovat aj v NESTED BLOCKS.
				.locals						init(string Name2, int32 Age2)

				ldstr						"Timmy Anderson"
				stloc						Name2

				ldc.i4						12
				stloc						Age2

				ldstr						"NESTED 2 - NAME [{0}], AGE [{1}] !"
				ldloc						Name2
				ldloc						Age2
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object,object)
				call						void [mscorlib]System.Console::WriteLine(string)
			}

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void TestNestedVariablesWithCustomIndexes() cil managed
		{
			// !!! LOCAL VARIABLES mozu mat zmenene INDEXES, ale MUSIA mat definovane INDEXES od 0-N.
			.locals							init([1] string Name, [0] int32 Age)
			// !!! Sposobi COMPILATION ERROR, pretoze LOCAL VARIABLES s INDEXES 0,1 a 2 nie su definovane.
			//.locals						init([3] string Name, [4] int32 Age)

			ldstr							"Timmy Anderson"
			stloc							Name

			ldc.i4							12
			stloc							Age

			ldstr							"NAME [{0}], AGE [{1}] !"
			ldloc							Name
			ldloc							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig void TestNestedLocalVariablesWithSameIndexes() cil managed
		{
			.locals							init(string Name, int32 Age)

			ldstr							"Timmy Anderson"
			stloc							Name

			ldc.i4							12
			stloc							Age

			ldstr							"NAME [{0}], AGE [{1}] !"
			ldloc							Name
			ldloc							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			{
				// !!!!! Kedze VARIABLES maju TIE ISTE INDEXES ako LOCAL VARIABLES definovane na urovni METHOD, budu zdielat tu istu MEMORY LOCATION.
				// !!! COMPILER vsak GENERUJE WARINING.
				.locals						init([0] string Name1, [1] int32 Age1)

				// !!! Hodnoty NETREBA nastavovat, pretoze su ZDIELANE s LOCAL VARIABLES definovanymi na urovni METHOD.
				/*
				ldstr						"Timmy Anderson"
				stloc						Name1

				ldc.i4						12
				stloc						Age1
				*/

				ldstr						"NESTED 1 - NAME [{0}], AGE [{1}] !"
				ldloc						Name1
				ldloc						Age1
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object,object)
				call						void [mscorlib]System.Console::WriteLine(string)
			}

			{
				// !!!!! Kedze VARIABLES maju TIE ISTE INDEXES ako LOCAL VARIABLES definovane na urovni METHOD, budu zdielat tu istu MEMORY LOCATION.
				// !!! COMPILER vsak GENERUJE WARINING.
				.locals						init([0] string Name2, [1] int32 Age2)

				// !!! Hodnoty NETREBA nastavovat, pretoze su ZDIELANE s LOCAL VARIABLES definovanymi na urovni METHOD.
				/*
				ldstr						"Timmy Anderson"
				stloc						Name2

				ldc.i4						12
				stloc						Age2
				*/

				ldstr						"NESTED 2 - NAME [{0}], AGE [{1}] !"
				ldloc						Name2
				ldloc						Age2
				box							[mscorlib]System.Int32
				call						string [mscorlib]System.String::Format(string,object,object)
				call						void [mscorlib]System.Console::WriteLine(string)
			}

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------