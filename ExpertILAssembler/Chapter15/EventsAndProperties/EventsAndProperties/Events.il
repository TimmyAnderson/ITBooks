//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Delegates.il"
//-------------------------------------------------------------------------------------------------------
// !!! Je NUTNE definovat TYPEDEF, aby MSIL COMPILER nemal problem pri kompilacii.
.typedef									class [mscorlib]System.Delegate as Delegate
//-------------------------------------------------------------------------------------------------------
.namespace EventsAndProperties
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CEvents extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
		// !!! FIELD obsahuje DELEGATE daneho EVENT.
		.field private class EventsAndProperties.DMyDelegate	MMyEvent
//-------------------------------------------------------------------------------------------------------
		// !!!!! EVENTS NEMAJU ZIADNU podporu v MSIL a KEYWORDS [.event] sa v MSIL NEDAJU NIJAKO POUZIT. Jediny zmysel ich pouzitia je ulozenie informacii do METADATA.
		.event EventsAndProperties.DMyDelegate					MyEvent
		{
			.addon												instance void EventsAndProperties.CEvents::Subscribe(class EventsAndProperties.DMyDelegate)
			.removeon											instance void EventsAndProperties.CEvents::Unsubscribe(class EventsAndProperties.DMyDelegate)
			.fire												instance void EventsAndProperties.CEvents::Raise(string,int32)
			.other												instance bool EventsAndProperties.CEvents::HasSubscribers()
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	    .method public specialname rtspecialname instance void .ctor() cil managed
		{
			ldarg							0
			call							instance void [mscorlib]System.Object::.ctor()

			ldarg							0
			ldnull
			stfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent

			ldstr							"EVENT was INITIALIZED ! DELEGATE [{0}] !"
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD vykonava EVENT SUBSCRIPTION.
		.method public void Subscribe(class EventsAndProperties.DMyDelegate EventHandler)
		{
			// Nacita sa THIS.
			ldarg							0
			// Nacita sa DELEGATE FIELD ako 1. PARAMETER METHOD Delegate.Combine().
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			// Nacita sa DELEGATE FIELD ako 2. PARAMETER METHOD Delegate.Combine().
			ldarg							EventHandler
			// !!! Zavola sa METHOD Delegate.Combine().
			call							Delegate EventsAndProperties.DMyDelegate::Combine(Delegate,Delegate)
			// !!!!! RETURN VALUE METHOD Delegate.Combine() sa ulozi do DELEGATE FIELD.
			stfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent

			ldstr							"DELEGATE was SUBSCRIBED ! DELEGATE [{0}] !"
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public void Unsubscribe(class EventsAndProperties.DMyDelegate EventHandler)
		{
			// Nacita sa THIS.
			ldarg							0
			// Nacita sa DELEGATE FIELD ako 1. PARAMETER METHOD Delegate.Remove().
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			// Nacita sa DELEGATE FIELD ako 2. PARAMETER METHOD Delegate.Remove().
			ldarg							EventHandler
			// !!! Zavola sa METHOD Delegate.Remove().
			call							Delegate EventsAndProperties.DMyDelegate::Remove(Delegate,Delegate)
			// !!!!! RETURN VALUE METHOD Delegate.Remove() sa ulozi do DELEGATE FIELD.
			stfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent

			ldstr							"DELEGATE was UNSUBSCRIBED ! DELEGATE [{0}] !"
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public void Raise(string Name, int32 Age)
		{
			// Zisti sa ci existuju nejake EVENT HANDLERS.
			ldarg							0
			call							instance bool EventsAndProperties.CEvents::HasSubscribers()
			brfalse							NO_ITEMS

			ldstr							"EVENT will be CALLED ! DELEGATE [{0}] !"
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			call							string [mscorlib]System.String::Format(string,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			// Nacita sa DELEGATE FIELD.
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			ldarg							Name
			ldarg							Age
			// !!!!! EVENT sa vyvolava volanim CUSTOM METHOD Invoke(). V tomto pripade sa jedna o METHOD DMyDelegate.Invoke().
			call							instance void EventsAndProperties.DMyDelegate::Invoke(string,int32)
			br								EXIT

		NO_ITEMS:
			ldstr							"NO EVENT HANDLERS to EXECUTE !"
	        call							void [mscorlib]System.Console::WriteLine(string)

		EXIT:
			ret
		}
//-------------------------------------------------------------------------------------------------------
		.method public bool HasSubscribers()
		{
			ldarg							0
			ldfld							class EventsAndProperties.DMyDelegate EventsAndProperties.CEvents::MMyEvent
			brnull							FALSE

			ldc.i4							1
			br								EXIT

		FALSE:
			ldc.i4							0

		EXIT: 
			ret
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public void NonStaticDelegateEventHandler1(string Name, int32 Age) cil managed
		{
			ldstr							"NON STATIC DELEGATE 1 - Name: [{0}], Age [{1}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public void NonStaticDelegateEventHandler2(string Name, int32 Age) cil managed
		{
			ldstr							"NON STATIC DELEGATE 2 - Name: [{0}], Age [{1}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void StaticDelegateEventHandler1(string Name, int32 Age) cil managed
		{
			ldstr							"STATIC DELEGATE 1 - Name: [{0}], Age [{1}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public static void StaticDelegateEventHandler2(string Name, int32 Age) cil managed
		{
			ldstr							"STATIC DELEGATE 2 - Name: [{0}], Age [{1}] !"
			ldarg							Name
			ldarg							Age
			box								[mscorlib]System.Int32
			call							string [mscorlib]System.String::Format(string,object,object)
	        call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------