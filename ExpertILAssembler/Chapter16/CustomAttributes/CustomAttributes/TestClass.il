//-------------------------------------------------------------------------------------------------------
.namespace CustomAttributes
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CTestClass extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!! Tento ATTRIBUTE je aplikovany v SCOPE CLASS a teda sa aplikuje na CLASS.
		.custom instance void [System.Runtime.Serialization]System.Runtime.Serialization.DataContractAttribute::.ctor()=
		{
			// Nastavuje hodnotu [Name] cez PROPERTY.
			property											string Name=string('MySuperClass')
			// Nastavuje hodnotu [Namespace] cez PROPERTY.
			property											string Namespace=string('MySuperNamespace')
			// Nastavuje hodnotu [IsReference] cez PROPERTY.
			property											bool IsReference=bool(false)
		}
//-------------------------------------------------------------------------------------------------------
		.field private string									MMyField1
		// !!!!! CUSTOM ATTRIBUTE MUSI byt aplikovany HNED za FIELD.
		// !!! CUSTOM ATTRIBUTE je typu [DataMemberAttribute] a nastavuje nasledujuce MEMBERS.
		// [EmitDefaultValue=false].
		// [IsRequired=true].
		// [Name="MyField"].
		// [Order=4].
		// Vyznam jednotlivych BYTES je nasledujuci.
		// VALUE [01 00] reprezentuje PREFIX VALUE CUSTOM ATTRIBUTE.
		// !!! VALUE [04 00] reprezentuje 4 KEY-VALUE PAIRS. Kedze ATTRIBUTE NEMA CONSTRUCTOR s PARAMETERS, tak OKAMZITE nasleduju KEY-VALUE PAIRS.
		// VALUE [54] reprezentuje PROPERTY. To znamena, ze KEY nastavuje PROPERTY.
		// VALUE [02] reprezentuje TYPE BOOLEAN.
		// VALUE [10 45 6D 69 74 44 65 66 61 75 6C 74 56 61 6C 75 65] reprezentuje 16 BYTES dlhy STRING s hodnotou [EmitDefaultValue].
		// VALUE [00] reprezentuje hodnotu BOOLEAN (FALSE).
		// VALUE [54] reprezentuje PROPERTY. To znamena, ze KEY nastavuje PROPERTY.
		// VALUE [02] reprezentuje TYPE BOOLEAN.
		// VALUE [0A 49 73 52 65 71 75 69 72 65 64] reprezentuje 10 BYTES dlhy STRING s hodnotou [IsRequired].
		// VALUE [01] reprezentuje hodnotu BOOLEAN (TRUE).
		// VALUE [54] reprezentuje PROPERTY. To znamena, ze KEY nastavuje PROPERTY.
		// VALUE [0E] reprezentuje TYPE STRING.
		// VALUE [04 4E 61 6D 65] reprezentuje 4 BYTES dlhy STRING s hodnotou [Name].
		// VALUE [07 4D 79 46 69 65 6C 64] reprezentuje hodnotu STRING (MyField).
		// VALUE [54] reprezentuje PROPERTY. To znamena, ze KEY nastavuje PROPERTY.
		// VALUE [08] reprezentuje TYPE INT32.
		// VALUE [05 4F 72 64 65 72] reprezentuje 5 BYTES dlhy STRING s hodnotou [Order].
		// VALUE [04 00 00 00] reprezentuje hodnotu INT32 (4).
		.custom instance void [System.Runtime.Serialization]System.Runtime.Serialization.DataMemberAttribute::.ctor() = ( 01 00 04 00 54 02 10 45 6D 69 74 44 65 66 61 75 6C 74 56 61 6C 75 65 00 54 02 0A 49 73 52 65 71 75 69 72 65 64 01 54 0E 04 4E 61 6D 65 07 4D 79 46 69 65 6C 64 54 08 05 4F 72 64 65 72 04 00 00 00 )
//-------------------------------------------------------------------------------------------------------
		.field private string									MMyField2
		// !!! CUSTOM ATTRIBUTE je typu [CMyCustomAttribute] a nastavuje nasledujuce MEMBERS.
		// [Field1="Timmy Anderson"]. Cez CONSTRUCTOR.
		// [Field2=12]. Cez CONSTRUCTOR.
		// [Field3="Jenny Thompson"].
		// [Field4=13].
		// [Field5=new int[]{10,20,30}].
		// !!! CONSTRUCTOR ma 2 PARAMETERS. Ostatne CUSTOM ATTRIBUTE FIELDS su nastavovane cez KEY-VALUE PAIRS.
		// Vyznam jednotlivych BYTES je nasledujuci.
		// VALUE [01 00] reprezentuje PREFIX VALUE CUSTOM ATTRIBUTE.
		// VALUE [0E 54 69 6D 6D 79 20 41 6E 64 65 72 73 6F 6E] reprezentuje 1. PARAMETER CONSTRUCTOR, ktory obsahuje 14 BYTES dlhy STRING obsahujuci hodnotu [Timmy Anderson].
		// VALUE [0C 00 00 00] reprezentuje 2. PARAMETER CONSTRUCTOR, ktory obsahuje INT32 obsahujuci hodnotu [12].
		// !!! VALUE [03 00] reprezentuje 3 KEY-VALUE PAIRS.
		// VALUE [54] reprezentuje PROPERTY. To znamena, ze KEY nastavuje PROPERTY.
		// VALUE [0E] reprezentuje TYPE STRING.
		// VALUE [06 46 69 65 6C 64 33] reprezentuje 6 BYTES dlhy STRING s hodnotou [Field3].
		// VALUE [0E 4A 65 6E 6E 79 20 54 68 6F 6D 70 73 6F 6E] reprezentuje hodnotu STRING (Jenny Thompson).
		// VALUE [54] reprezentuje PROPERTY. To znamena, ze KEY nastavuje PROPERTY.
		// VALUE [08] reprezentuje TYPE INT32.
		// VALUE [06 46 69 65 6C 64 34] reprezentuje 6 BYTES dlhy STRING s hodnotou [Field4].
		// VALUE [0D 00 00 00] reprezentuje hodnotu INT32 (13).
		// VALUE [54] reprezentuje PROPERTY. To znamena, ze KEY nastavuje PROPERTY.
		// VALUE [1D 08] reprezentuje TYPE INT32[].
		// VALUE [06 46 69 65 6C 64 35] reprezentuje 6 BYTES dlhy STRING s hodnotou [Field5].
		// VALUE [03 00 00 00] reprezentuje pocet ITEMS v ARRAY (3).
		// VALUE [0A 00 00 00] reprezentuje 1. ITEM ARRAY (10).
		// VALUE [14 00 00 00] reprezentuje 2. ITEM ARRAY (20).
		// VALUE [1E 00 00 00] reprezentuje 3. ITEM ARRAY (30).
		.custom instance void CustomAttributes.CMyCustomAttribute::.ctor(string,int32) = ( 01 00 0E 54 69 6D 6D 79 20 41 6E 64 65 72 73 6F 6E 0C 00 00 00 03 00 54 0E 06 46 69 65 6C 64 33 0E 4A 65 6E 6E 79 20 54 68 6F 6D 70 73 6F 6E 54 08 06 46 69 65 6C 64 34 0D 00 00 00 54 1D 08 06 46 69 65 6C 64 35 03 00 00 00 0A 00 00 00 14 00 00 00 1E 00 00 00 )
//-------------------------------------------------------------------------------------------------------
		.field private string									MMyField3
		// !!!!! ALTERNATIVNA VERBAL SYNTAX pre definovanie CUSTOM ATTRIBUTE.
		.custom instance void CustomAttributes.CMyCustomAttribute::.ctor(string,int32)=
		{
			// !!! Definuje 1. PARAMETER CONSTRUCTOR.
			string('Jenny Thompson')
			// !!! Definuje 2. PARAMETER CONSTRUCTOR.
			int32(13)
			// Nastavuje hodnotu [Field3] cez PROPERTY.
			property											string Field3=string('Timmy Anderson')
			// Nastavuje hodnotu [Field4] cez PROPERTY.
			property											int32 Field4=int32(12)
			// Nastavuje hodnotu [Field5] cez PROPERTY.
			property											int32[] Field5=int32[3](30 20 10)
		}
//-------------------------------------------------------------------------------------------------------
		// !!! CUSTOM ATTRIBUTES sa na nich aplikuju az na KONCI CLASS cez FULL SYNTAX.
		.field private string									MMyField4
		.field private string									MMyField5
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		.method public instance void Test1()
		{
			.locals							init (class [mscorlib]System.Type ThisType)
			.locals							init (class [mscorlib]System.Reflection.FieldInfo MyFieldInfo)
			.locals							init (class [System.Runtime.Serialization]System.Runtime.Serialization.DataMemberAttribute CustomAttribute)
			// Hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			.locals							init (bool EmitDefaultValue)
			.locals							init (bool IsRequired)
			.locals							init (string Name)
			.locals							init (int32 Order)

			ldstr							"Test1() is CALLED !"
	        call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Do [ThisType] sa ulozi this.GetType().
			ldarg							0
			call							instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
			stloc							ThisType

			// !!! Do [MyFieldInfo] sa ulozi ThisType.GetField("MMyField1",BindingFlags.NonPublic | BindingFlags.Instance).
			ldloc							ThisType
			ldstr							"MMyField1"
			// Je to hodnota [BindingFlags.NonPublic | BindingFlags.Instance].
			ldc.i4							36
			callvirt						instance class [mscorlib]System.Reflection.FieldInfo [mscorlib]System.Type::GetField(string,valuetype [mscorlib]System.Reflection.BindingFlags)
			stloc							MyFieldInfo

			// !!! Do [CustomAttribute] sa ulozi MyFieldInfo.GetCustomAttribute<DataMemberAttribute>().
			ldloc							MyFieldInfo
			call							!!0 [mscorlib]System.Reflection.CustomAttributeExtensions::GetCustomAttribute<class [System.Runtime.Serialization]System.Runtime.Serialization.DataMemberAttribute>(class [mscorlib]System.Reflection.MemberInfo)
			stloc							CustomAttribute

			// !!! Nacitaju sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldloc							CustomAttribute
			callvirt						instance bool [System.Runtime.Serialization]System.Runtime.Serialization.DataMemberAttribute::get_EmitDefaultValue()
			stloc							EmitDefaultValue
			
			ldloc							CustomAttribute
			callvirt						instance bool [System.Runtime.Serialization]System.Runtime.Serialization.DataMemberAttribute::get_IsRequired()
			stloc						    IsRequired
			
			ldloc							CustomAttribute
			callvirt						instance string [System.Runtime.Serialization]System.Runtime.Serialization.DataMemberAttribute::get_Name()
			stloc							Name
			
			ldloc							CustomAttribute
			callvirt						instance int32 [System.Runtime.Serialization]System.Runtime.Serialization.DataMemberAttribute::get_Order()
			stloc							Order

			// !!! Vypisu sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldstr							"DataMemberAttribute.EmitDefaultValue [{0}] !"
			ldloc							EmitDefaultValue
			box								[mscorlib]System.Boolean
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DataMemberAttribute.IsRequired [{0}] !"
			ldloc							IsRequired
			box								[mscorlib]System.Boolean
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DataMemberAttribute.Name [{0}] !"
			ldloc							Name
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DataMemberAttribute.Order [{0}] !"
			ldloc							Order
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public instance void Test2()
		{
			.locals							init (class [mscorlib]System.Type ThisType)
			.locals							init (class [mscorlib]System.Reflection.FieldInfo MyFieldInfo)
			.locals							init (class CustomAttributes.CMyCustomAttribute CustomAttribute)
			.locals							init (int32 Index)
			.locals							init (int32 Field5Length)
			.locals							init (int32 Temp)
			// Hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			.locals							init (string Field1)
			.locals							init (int32 Field2)
			.locals							init (string Field3)
			.locals							init (int32 Field4)
			.locals							init (int32[] Field5)

			ldstr							"Test2() is CALLED !"
	        call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Do [ThisType] sa ulozi this.GetType().
			ldarg							0
			call							instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
			stloc							ThisType

			// !!! Do [MyFieldInfo] sa ulozi ThisType.GetField("MMyField2",BindingFlags.NonPublic | BindingFlags.Instance).
			ldloc							ThisType
			ldstr							"MMyField2"
			// Je to hodnota [BindingFlags.NonPublic | BindingFlags.Instance].
			ldc.i4							36
			callvirt						instance class [mscorlib]System.Reflection.FieldInfo [mscorlib]System.Type::GetField(string,valuetype [mscorlib]System.Reflection.BindingFlags)
			stloc							MyFieldInfo

			// !!! Do [CustomAttribute] sa ulozi MyFieldInfo.GetCustomAttribute<CMyCustomAttribute>().
			ldloc							MyFieldInfo
			call							!!0 [mscorlib]System.Reflection.CustomAttributeExtensions::GetCustomAttribute<class CustomAttributes.CMyCustomAttribute>(class [mscorlib]System.Reflection.MemberInfo)
			stloc							CustomAttribute

			// !!! Nacitaju sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField1()
			stloc							Field1
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField2()
			stloc							Field2
			
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField3()
			stloc							Field3
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField4()
			stloc							Field4
			
			ldloc							CustomAttribute
			callvirt						instance int32[] CustomAttributes.CMyCustomAttribute::GetField5()
			stloc							Field5

			// !!! Vypisu sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldstr							"CMyCustomAttribute.Field1 [{0}] !"
			ldloc							Field1
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field2 [{0}] !"
			ldloc							Field2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field3 [{0}] !"
			ldloc							Field3
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field4 [{0}] !"
			ldloc							Field4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Field5
			ldlen
			stloc							Field5Length

			ldc.i4							0
			stloc							Index

		BEGIN_FOR:
			// !!! Ukonci cyklus, ak Index>=Field5Length.
			ldloc							Index
			ldloc							Field5Length
			bge								END_FOR

			ldloc							Field5
			ldloc							Index
			ldelem.i4
			stloc							Temp

			ldstr							"CMyCustomAttribute.Field5[{0}] [{1}] !"
			ldloc							Index
			box								[mscorlib]System.Int32
			ldloc							Temp
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index
			br								BEGIN_FOR

		END_FOR:
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public instance void Test3()
		{
			.locals							init (class [mscorlib]System.Type ThisType)
			.locals							init (class [mscorlib]System.Reflection.FieldInfo MyFieldInfo)
			.locals							init (class CustomAttributes.CMyCustomAttribute CustomAttribute)
			.locals							init (int32 Index)
			.locals							init (int32 Field5Length)
			.locals							init (int32 Temp)
			// Hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			.locals							init (string Field1)
			.locals							init (int32 Field2)
			.locals							init (string Field3)
			.locals							init (int32 Field4)
			.locals							init (int32[] Field5)

			ldstr							"Test3() is CALLED !"
	        call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Do [ThisType] sa ulozi this.GetType().
			ldarg							0
			call							instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
			stloc							ThisType

			// !!! Do [MyFieldInfo] sa ulozi ThisType.GetField("MMyField3",BindingFlags.NonPublic | BindingFlags.Instance).
			ldloc							ThisType
			ldstr							"MMyField3"
			// Je to hodnota [BindingFlags.NonPublic | BindingFlags.Instance].
			ldc.i4							36
			callvirt						instance class [mscorlib]System.Reflection.FieldInfo [mscorlib]System.Type::GetField(string,valuetype [mscorlib]System.Reflection.BindingFlags)
			stloc							MyFieldInfo

			// !!! Do [CustomAttribute] sa ulozi MyFieldInfo.GetCustomAttribute<CMyCustomAttribute>().
			ldloc							MyFieldInfo
			call							!!0 [mscorlib]System.Reflection.CustomAttributeExtensions::GetCustomAttribute<class CustomAttributes.CMyCustomAttribute>(class [mscorlib]System.Reflection.MemberInfo)
			stloc							CustomAttribute

			// !!! Nacitaju sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField1()
			stloc							Field1
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField2()
			stloc							Field2
			
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField3()
			stloc							Field3
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField4()
			stloc							Field4
			
			ldloc							CustomAttribute
			callvirt						instance int32[] CustomAttributes.CMyCustomAttribute::GetField5()
			stloc							Field5

			// !!! Vypisu sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldstr							"CMyCustomAttribute.Field1 [{0}] !"
			ldloc							Field1
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field2 [{0}] !"
			ldloc							Field2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field3 [{0}] !"
			ldloc							Field3
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field4 [{0}] !"
			ldloc							Field4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Field5
			ldlen
			stloc							Field5Length

			ldc.i4							0
			stloc							Index

		BEGIN_FOR:
			// !!! Ukonci cyklus, ak Index>=Field5Length.
			ldloc							Index
			ldloc							Field5Length
			bge								END_FOR

			ldloc							Field5
			ldloc							Index
			ldelem.i4
			stloc							Temp

			ldstr							"CMyCustomAttribute.Field5[{0}] [{1}] !"
			ldloc							Index
			box								[mscorlib]System.Int32
			ldloc							Temp
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index
			br								BEGIN_FOR

		END_FOR:
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public instance void Test4()
		{
			.locals							init (class [mscorlib]System.Type ThisType)
			.locals							init (class [mscorlib]System.Reflection.FieldInfo MyFieldInfo)
			.locals							init (class CustomAttributes.CMyCustomAttribute CustomAttribute)
			.locals							init (int32 Index)
			.locals							init (int32 Field5Length)
			.locals							init (int32 Temp)
			// Hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			.locals							init (string Field1)
			.locals							init (int32 Field2)
			.locals							init (string Field3)
			.locals							init (int32 Field4)
			.locals							init (int32[] Field5)

			ldstr							"Test4() is CALLED !"
	        call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Do [ThisType] sa ulozi this.GetType().
			ldarg							0
			call							instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
			stloc							ThisType

			// !!! Do [MyFieldInfo] sa ulozi ThisType.GetField("MMyField4",BindingFlags.NonPublic | BindingFlags.Instance).
			ldloc							ThisType
			ldstr							"MMyField4"
			// Je to hodnota [BindingFlags.NonPublic | BindingFlags.Instance].
			ldc.i4							36
			callvirt						instance class [mscorlib]System.Reflection.FieldInfo [mscorlib]System.Type::GetField(string,valuetype [mscorlib]System.Reflection.BindingFlags)
			stloc							MyFieldInfo

			// !!! Do [CustomAttribute] sa ulozi MyFieldInfo.GetCustomAttribute<CMyCustomAttribute>().
			ldloc							MyFieldInfo
			call							!!0 [mscorlib]System.Reflection.CustomAttributeExtensions::GetCustomAttribute<class CustomAttributes.CMyCustomAttribute>(class [mscorlib]System.Reflection.MemberInfo)
			stloc							CustomAttribute

			// !!! Nacitaju sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField1()
			stloc							Field1
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField2()
			stloc							Field2
			
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField3()
			stloc							Field3
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField4()
			stloc							Field4
			
			ldloc							CustomAttribute
			callvirt						instance int32[] CustomAttributes.CMyCustomAttribute::GetField5()
			stloc							Field5

			// !!! Vypisu sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldstr							"CMyCustomAttribute.Field1 [{0}] !"
			ldloc							Field1
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field2 [{0}] !"
			ldloc							Field2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field3 [{0}] !"
			ldloc							Field3
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field4 [{0}] !"
			ldloc							Field4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Field5
			ldlen
			stloc							Field5Length

			ldc.i4							0
			stloc							Index

		BEGIN_FOR:
			// !!! Ukonci cyklus, ak Index>=Field5Length.
			ldloc							Index
			ldloc							Field5Length
			bge								END_FOR

			ldloc							Field5
			ldloc							Index
			ldelem.i4
			stloc							Temp

			ldstr							"CMyCustomAttribute.Field5[{0}] [{1}] !"
			ldloc							Index
			box								[mscorlib]System.Int32
			ldloc							Temp
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index
			br								BEGIN_FOR

		END_FOR:
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public instance void Test5()
		{
			.locals							init (class [mscorlib]System.Type ThisType)
			.locals							init (class [mscorlib]System.Reflection.FieldInfo MyFieldInfo)
			.locals							init (class CustomAttributes.CMyCustomAttribute CustomAttribute)
			.locals							init (int32 Index)
			.locals							init (int32 Field5Length)
			.locals							init (int32 Temp)
			// Hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			.locals							init (string Field1)
			.locals							init (int32 Field2)
			.locals							init (string Field3)
			.locals							init (int32 Field4)
			.locals							init (int32[] Field5)

			ldstr							"Test5() is CALLED !"
	        call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Do [ThisType] sa ulozi this.GetType().
			ldarg							0
			call							instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
			stloc							ThisType

			// !!! Do [MyFieldInfo] sa ulozi ThisType.GetField("MMyField5",BindingFlags.NonPublic | BindingFlags.Instance).
			ldloc							ThisType
			ldstr							"MMyField5"
			// Je to hodnota [BindingFlags.NonPublic | BindingFlags.Instance].
			ldc.i4							36
			callvirt						instance class [mscorlib]System.Reflection.FieldInfo [mscorlib]System.Type::GetField(string,valuetype [mscorlib]System.Reflection.BindingFlags)
			stloc							MyFieldInfo

			// !!! Do [CustomAttribute] sa ulozi MyFieldInfo.GetCustomAttribute<CMyCustomAttribute>().
			ldloc							MyFieldInfo
			call							!!0 [mscorlib]System.Reflection.CustomAttributeExtensions::GetCustomAttribute<class CustomAttributes.CMyCustomAttribute>(class [mscorlib]System.Reflection.MemberInfo)
			stloc							CustomAttribute

			// !!! Nacitaju sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField1()
			stloc							Field1
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField2()
			stloc							Field2
			
			ldloc							CustomAttribute
			callvirt						instance string CustomAttributes.CMyCustomAttribute::GetField3()
			stloc							Field3
			
			ldloc							CustomAttribute
			callvirt						instance int32 CustomAttributes.CMyCustomAttribute::GetField4()
			stloc							Field4
			
			ldloc							CustomAttribute
			callvirt						instance int32[] CustomAttributes.CMyCustomAttribute::GetField5()
			stloc							Field5

			// !!! Vypisu sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldstr							"CMyCustomAttribute.Field1 [{0}] !"
			ldloc							Field1
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field2 [{0}] !"
			ldloc							Field2
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field3 [{0}] !"
			ldloc							Field3
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"CMyCustomAttribute.Field4 [{0}] !"
			ldloc							Field4
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Field5
			ldlen
			stloc							Field5Length

			ldc.i4							0
			stloc							Index

		BEGIN_FOR:
			// !!! Ukonci cyklus, ak Index>=Field5Length.
			ldloc							Index
			ldloc							Field5Length
			bge								END_FOR

			ldloc							Field5
			ldloc							Index
			ldelem.i4
			stloc							Temp

			ldstr							"CMyCustomAttribute.Field5[{0}] [{1}] !"
			ldloc							Index
			box								[mscorlib]System.Int32
			ldloc							Temp
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			// Inkrementuje Index.
			ldloc							Index
			ldc.i4							1
			add
			stloc							Index
			br								BEGIN_FOR

		END_FOR:
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public instance void Test6()
		{
			.locals							init (class [mscorlib]System.Type ThisType)
			.locals							init (class [System.Runtime.Serialization]System.Runtime.Serialization.DataContractAttribute CustomAttribute)
			// Hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			.locals							init (string Name)
			.locals							init (string Namespace)
			.locals							init (bool IsReference)

			ldstr							"Test6() is CALLED !"
	        call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Do [ThisType] sa ulozi this.GetType().
			ldarg							0
			call							instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
			stloc							ThisType

			// !!! Do [CustomAttribute] sa ulozi ThisType.GetCustomAttribute<DataContractAttribute>().
			ldloc							ThisType
			call							!!0 [mscorlib]System.Reflection.CustomAttributeExtensions::GetCustomAttribute<class [System.Runtime.Serialization]System.Runtime.Serialization.DataContractAttribute>(class [mscorlib]System.Reflection.MemberInfo)
			stloc							CustomAttribute

			// !!! Nacitaju sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldloc							CustomAttribute
			callvirt						instance string [System.Runtime.Serialization]System.Runtime.Serialization.DataContractAttribute::get_Name()
			stloc							Name
			
			ldloc							CustomAttribute
			callvirt						instance string [System.Runtime.Serialization]System.Runtime.Serialization.DataContractAttribute::get_Namespace()
			stloc							Namespace
			
			ldloc							CustomAttribute
			callvirt						instance bool [System.Runtime.Serialization]System.Runtime.Serialization.DataContractAttribute::get_IsReference()
			stloc							IsReference
			
			// !!! Vypisu sa hodnoty PROPERTIES CUSTOM ATTRIBUTE.
			ldstr							"DataContractAttribute.Name [{0}] !"
			ldloc							Name
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DataContractAttribute.Namespace [{0}] !"
			ldloc							Namespace
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"DataContractAttribute.IsReference [{0}] !"
			ldloc							IsReference
			box								[mscorlib]System.Boolean
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!!!! FULL RAW SYNTAX, ktorou sa aplikuje CUSTOM ATTRIBUTE na LUBOVOLNY METADATA ITEM.
		// !!! CUSTOM ATTRIBUTE sa aplikuje na FIELD [MMyField4].
		.custom (field string CustomAttributes.CTestClass::MMyField4) instance void CustomAttributes.CMyCustomAttribute::.ctor(string,int32) = ( 01 00 0E 54 69 6D 6D 79 20 41 6E 64 65 72 73 6F 6E 0C 00 00 00 03 00 54 0E 06 46 69 65 6C 64 33 0E 4A 65 6E 6E 79 20 54 68 6F 6D 70 73 6F 6E 54 08 06 46 69 65 6C 64 34 0D 00 00 00 54 1D 08 06 46 69 65 6C 64 35 03 00 00 00 0A 00 00 00 14 00 00 00 1E 00 00 00 )
		// !!!!! FULL VERBAL SYNTAX, ktorou sa aplikuje CUSTOM ATTRIBUTE na LUBOVOLNY METADATA ITEM.
		// !!! CUSTOM ATTRIBUTE sa aplikuje na FIELD [MMyField5].
		.custom (field string CustomAttributes.CTestClass::MMyField5) instance void CustomAttributes.CMyCustomAttribute::.ctor(string,int32)=
		{
			// !!! Definuje 1. PARAMETER CONSTRUCTOR.
			string('Jenny Thompson')
			// !!! Definuje 2. PARAMETER CONSTRUCTOR.
			int32(13)
			// Nastavuje hodnotu [Field3] cez PROPERTY.
			property											string Field3=string('Timmy Anderson')
			// Nastavuje hodnotu [Field4] cez PROPERTY.
			property											int32 Field4=int32(12)
			// Nastavuje hodnotu [Field5] cez PROPERTY.
			property											int32[] Field5=int32[3](30 20 10)
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------