//-------------------------------------------------------------------------------------------------------
.namespace EventsAndProperties
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CProperties extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!! FIELD do ktoreho sa bude ukladat hodnota PROPERTY.
		.field private string									MMyProperty
//-------------------------------------------------------------------------------------------------------
		// !!!!! PROPERTIES NEMAJU ZIADNU podporu v MSIL a KEYWORDS [.property] sa v MSIL NEDAJU NIJAKO POUZIT. Jediny zmysel ich pouzitia je ulozenie informacii do METADATA.
		.property string										MyProperty(string,int32)
		{
			.get												instance string EventsAndProperties.CProperties::GetMyProperty()
			.set												instance void EventsAndProperties.CProperties::SetMyProperty(string,int32)
			.other												instance void EventsAndProperties.CProperties::ResetMyProperty()
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ldarg							0
			ldstr							""
			stfld							string EventsAndProperties.CProperties::MMyProperty

			ldstr							"PROPERTY was INITIALIZED ! PROPERTY [{0}] !"
			ldarg							0
			ldfld							string EventsAndProperties.CProperties::MMyProperty
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// PROPERTY GETTER.
		.method public string GetMyProperty()
		{
			ldarg							0
			ldfld							string EventsAndProperties.CProperties::MMyProperty

			ret
		}
//-------------------------------------------------------------------------------------------------------
		// PROPERTY SETTER.
		.method public void SetMyProperty(string Name, int32 Age)
		{
            .locals							init (string Value)

			ldstr							"NAME [{0}], AGE [{1}]"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
			stloc							Value

			ldarg							0
			ldloc							Value
			stfld							string EventsAndProperties.CProperties::MMyProperty

			ldstr							"PROPERTY was SET ! PROPERTY [{0}] !"
			ldarg							0
			ldfld							string EventsAndProperties.CProperties::MMyProperty
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public void ResetMyProperty()
		{
			ldarg							0
			ldstr							""
			stfld							string EventsAndProperties.CProperties::MMyProperty

			ldstr							"PROPERTY was RESET ! PROPERTY [{0}] !"
			ldarg							0
			ldfld							string EventsAndProperties.CProperties::MMyProperty
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------