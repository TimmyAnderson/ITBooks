//-------------------------------------------------------------------------------------------------------
.namespace CustomAttributes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CMyCustomAttribute extends [mscorlib]System.Attribute
	{
//-------------------------------------------------------------------------------------------------------
		// CUSTOM ATTRIBUTE [AttributeUsageAttribute] ucuje kedy je mozne ATTRIBUTE [CMyCustomAttribute] pouzit.
		.custom instance void [mscorlib]System.AttributeUsageAttribute::.ctor(valuetype [mscorlib]System.AttributeTargets)=
		{
			// ATTRIBUTE sa da aplikovat iba na FIELDS.
			int32(0x100)
			property											bool AllowMultiple=bool(false)
			property											bool Inherited=bool(true)
		}
//-------------------------------------------------------------------------------------------------------
		.field private string									MField1
		.field private int32									MField2
		.field private string									MField3
		.field private int32									MField4
		.field private int32[]									MField5
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor(string Field1, int32 Field2) cil managed
		{
			ldarg							0
			call							instance void [mscorlib]System.Attribute::.ctor()

			ldarg							0
			ldarg							Field1
			stfld							string CustomAttributes.CMyCustomAttribute::MField1
			ldarg							0
			ldarg							Field2
			stfld							int32 CustomAttributes.CMyCustomAttribute::MField2

			// Vytvori EMPTY ARRAY.
			ldarg							0
			ldc.i4							0
			newarr							[mscorlib]System.Int32
			stfld							int32[] CustomAttributes.CMyCustomAttribute::MField5

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.property instance string Field1()
		{
			.get instance string CustomAttributes.CMyCustomAttribute::GetField1()
			.set instance void CustomAttributes.CMyCustomAttribute::SetField1(string)
		}
//-------------------------------------------------------------------------------------------------------
		.property instance int32 Field2()
		{
			.get instance int32 CustomAttributes.CMyCustomAttribute::GetField2()
			.set instance void CustomAttributes.CMyCustomAttribute::SetField2(int32)
		}
//-------------------------------------------------------------------------------------------------------
		.property instance string Field3()
		{
			.get instance string CustomAttributes.CMyCustomAttribute::GetField3()
			.set instance void CustomAttributes.CMyCustomAttribute::SetField3(string)
		}
//-------------------------------------------------------------------------------------------------------
		.property instance int32 Field4()
		{
			.set instance void CustomAttributes.CMyCustomAttribute::SetField4(int32)
			.get instance int32 CustomAttributes.CMyCustomAttribute::GetField4()
		}
//-------------------------------------------------------------------------------------------------------
		.property instance int32[] Field5()
		{
			.get instance int32[] CustomAttributes.CMyCustomAttribute::GetField5()
			.set instance void CustomAttributes.CMyCustomAttribute::SetField5(int32[])
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance string GetField1() cil managed
		{
			ldarg							0
			ldfld							string CustomAttributes.CMyCustomAttribute::MField1

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance void SetField1(string Value) cil managed
		{
			ldarg							0
			ldarg							Value
			stfld							string CustomAttributes.CMyCustomAttribute::MField1
			
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance int32 GetField2() cil managed
		{
			ldarg							0
			ldfld							int32 CustomAttributes.CMyCustomAttribute::MField2

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance void SetField2(int32 Value) cil managed
		{
			ldarg							0
			ldarg							Value
			stfld							int32 CustomAttributes.CMyCustomAttribute::MField2
		
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance string GetField3() cil managed
		{
			ldarg							0
			ldfld							string CustomAttributes.CMyCustomAttribute::MField3

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance void SetField3(string Value) cil managed
		{
			ldarg							0
			ldarg							Value
			stfld							string CustomAttributes.CMyCustomAttribute::MField3

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance int32 GetField4() cil managed
		{
			ldarg							0
			ldfld							int32 CustomAttributes.CMyCustomAttribute::MField4
		
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance void SetField4(int32 Value) cil managed
		{
			ldarg							0
			ldarg							Value
			stfld							int32 CustomAttributes.CMyCustomAttribute::MField4
		
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance int32[] GetField5() cil managed
		{
			ldarg							0
			ldfld							int32[] CustomAttributes.CMyCustomAttribute::MField5
		
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public hidebysig specialname instance void SetField5(int32[] Value) cil managed
		{
			ldarg							0
			ldarg							Value
			stfld							int32[] CustomAttributes.CMyCustomAttribute::MField5
		
			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------