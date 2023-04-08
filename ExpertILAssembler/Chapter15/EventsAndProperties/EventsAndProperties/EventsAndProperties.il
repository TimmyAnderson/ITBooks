//-------------------------------------------------------------------------------------------------------
.assembly extern mscorlib {auto}
.assembly EventsAndProperties {}
.module EventsAndProperties.exe
//-------------------------------------------------------------------------------------------------------
// Vklada iny .IL FILE do CURRENT .IL FILE.
#include "Helpers.il"
#include "Events.il"
#include "Properties.il"
//-------------------------------------------------------------------------------------------------------
.namespace EventsAndProperties
{
//-------------------------------------------------------------------------------------------------------
    .class public auto ansi CEventsAndProperties extends [mscorlib]System.Object
	{
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test1() cil managed
		{
            .locals							init (class EventsAndProperties.CEvents Events)
			.locals							init (method void * (string,int32) CallbackFunctionPointer1)
			.locals							init (method void * (string,int32) CallbackFunctionPointer2)
            .locals							init (class EventsAndProperties.DMyDelegate Delegate1)
            .locals							init (class EventsAndProperties.DMyDelegate Delegate2)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vytvori sa instancia CEvent CLASS.
			newobj							instance void EventsAndProperties.CEvents::.ctor()
			stloc							Events

			// !!! Ziska sa POINTER na NON-STATIC FUNCTION.
			ldloc							Events
			ldftn							instance void EventsAndProperties.CEvents::NonStaticDelegateEventHandler1(string,int32)
			stloc							CallbackFunctionPointer1

			// !!! Ziska sa POINTER na NON-STATIC FUNCTION.
			ldloc							Events
			ldftn							instance void EventsAndProperties.CEvents::NonStaticDelegateEventHandler2(string,int32)
			stloc							CallbackFunctionPointer2

			// !!! Vytvori sa DELEGATE.
			// !!! Prvy PARAMETER je THIS na OBJECT, ktory vlastni CALLBACK METHOD.
			ldloc							Events
			// !!! Druhy PARAMETER je POINTER na CALLBACK METHOD.
			ldloc							CallbackFunctionPointer1
			newobj							instance void EventsAndProperties.DMyDelegate::.ctor(object,native int)
			stloc							Delegate1

			// !!! Vytvori sa DELEGATE.
			// !!! Prvy PARAMETER je THIS na OBJECT, ktory vlastni CALLBACK METHOD.
			ldloc							Events
			// !!! Druhy PARAMETER je POINTER na CALLBACK METHOD.
			ldloc							CallbackFunctionPointer2
			newobj							instance void EventsAndProperties.DMyDelegate::.ctor(object,native int)
			stloc							Delegate2

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! PRVY DELEGATE sa prida do EVENT.
			ldloc							Events
			ldloc							Delegate1
			// !!!!! DELEGATES sa pridavaju do EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Subscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! DRUHY DELEGATE sa prida do EVENT.
			ldloc							Events
			ldloc							Delegate2
			// !!!!! DELEGATES sa pridavaju do EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Subscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! PRVY DELEGATE sa odstrani z EVENT.
			ldloc							Events
			ldloc							Delegate1
			// !!!!! DELEGATES sa odstranuju z EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Unsubscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! DRUHY DELEGATE sa odstrani z EVENT.
			ldloc							Events
			ldloc							Delegate2
			// !!!!! DELEGATES sa odstranuju z EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Unsubscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test2() cil managed
		{
            .locals							init (class EventsAndProperties.CEvents Events)
			.locals							init (method void * (string,int32) CallbackFunctionPointer1)
			.locals							init (method void * (string,int32) CallbackFunctionPointer2)
            .locals							init (class EventsAndProperties.DMyDelegate Delegate1)
            .locals							init (class EventsAndProperties.DMyDelegate Delegate2)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vytvori sa instancia CEvent CLASS.
			newobj							instance void EventsAndProperties.CEvents::.ctor()
			stloc							Events

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Ziska sa POINTER na NON-STATIC FUNCTION.
			ldloc							Events
			ldftn							instance void EventsAndProperties.CEvents::NonStaticDelegateEventHandler1(string,int32)
			stloc							CallbackFunctionPointer1

			// !!! Ziska sa POINTER na NON-STATIC FUNCTION.
			ldloc							Events
			ldftn							instance void EventsAndProperties.CEvents::NonStaticDelegateEventHandler2(string,int32)
			stloc							CallbackFunctionPointer2

			// !!! Vytvori sa DELEGATE.
			// !!! Prvy PARAMETER je THIS na OBJECT, ktory vlastni CALLBACK METHOD.
			ldloc							Events
			// !!! Druhy PARAMETER je POINTER na CALLBACK METHOD.
			ldloc							CallbackFunctionPointer1
			newobj							instance void EventsAndProperties.DMyDelegate::.ctor(object,native int)
			stloc							Delegate1

			// !!! Vytvori sa DELEGATE.
			// !!! Prvy PARAMETER je THIS na OBJECT, ktory vlastni CALLBACK METHOD.
			ldloc							Events
			// !!! Druhy PARAMETER je POINTER na CALLBACK METHOD.
			ldloc							CallbackFunctionPointer2
			newobj							instance void EventsAndProperties.DMyDelegate::.ctor(object,native int)
			stloc							Delegate2

			// !!! PRVY DELEGATE sa prida do EVENT.
			ldloc							Events
			ldloc							Delegate1
			// !!!!! DELEGATES sa pridavaju do EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Subscribe(class EventsAndProperties.DMyDelegate)

			// !!! DRUHY DELEGATE sa prida do EVENT.
			ldloc							Events
			ldloc							Delegate2
			// !!!!! DELEGATES sa pridavaju do EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Subscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Spusti sa vyvolanie EVENT.
			ldloc							Events
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							instance void EventsAndProperties.CEvents::Raise(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! PRVY DELEGATE sa odstrani z EVENT.
			ldloc							Events
			ldloc							Delegate1
			// !!!!! DELEGATES sa odstranuju z EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Unsubscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Spusti sa vyvolanie EVENT.
			ldloc							Events
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							instance void EventsAndProperties.CEvents::Raise(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! DRUHY DELEGATE sa odstrani z EVENT.
			ldloc							Events
			ldloc							Delegate2
			// !!!!! DELEGATES sa odstranuju z EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Unsubscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Spusti sa vyvolanie EVENT.
			ldloc							Events
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							instance void EventsAndProperties.CEvents::Raise(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test3() cil managed
		{
            .locals							init (class EventsAndProperties.CEvents Events)
			.locals							init (method void * (string,int32) CallbackFunctionPointer1)
			.locals							init (method void * (string,int32) CallbackFunctionPointer2)
            .locals							init (class EventsAndProperties.DMyDelegate Delegate1)
            .locals							init (class EventsAndProperties.DMyDelegate Delegate2)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vytvori sa instancia CEvent CLASS.
			newobj							instance void EventsAndProperties.CEvents::.ctor()
			stloc							Events

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Ziska sa POINTER na STATIC FUNCTION.
			ldftn							void EventsAndProperties.CEvents::StaticDelegateEventHandler1(string,int32)
			stloc							CallbackFunctionPointer1

			// !!! Ziska sa POINTER na STATIC FUNCTION.
			ldloc							Events
			ldftn							void EventsAndProperties.CEvents::StaticDelegateEventHandler2(string,int32)
			stloc							CallbackFunctionPointer2

			// !!! Vytvori sa DELEGATE.
			// !!! Prvy PARAMETER je THIS na OBJECT, ktory vlastni CALLBACK METHOD.
			ldloc							Events
			// !!! Druhy PARAMETER je POINTER na CALLBACK METHOD.
			ldloc							CallbackFunctionPointer1
			newobj							instance void EventsAndProperties.DMyDelegate::.ctor(object,native int)
			stloc							Delegate1

			// !!! Vytvori sa DELEGATE.
			// !!! Prvy PARAMETER je THIS na OBJECT, ktory vlastni CALLBACK METHOD.
			ldloc							Events
			// !!! Druhy PARAMETER je POINTER na CALLBACK METHOD.
			ldloc							CallbackFunctionPointer2
			newobj							instance void EventsAndProperties.DMyDelegate::.ctor(object,native int)
			stloc							Delegate2

			// !!! PRVY DELEGATE sa prida do EVENT.
			ldloc							Events
			ldloc							Delegate1
			// !!!!! DELEGATES sa pridavaju do EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Subscribe(class EventsAndProperties.DMyDelegate)

			// !!! DRUHY DELEGATE sa prida do EVENT.
			ldloc							Events
			ldloc							Delegate2
			// !!!!! DELEGATES sa pridavaju do EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Subscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Spusti sa vyvolanie EVENT.
			ldloc							Events
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							instance void EventsAndProperties.CEvents::Raise(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! PRVY DELEGATE sa odstrani z EVENT.
			ldloc							Events
			ldloc							Delegate1
			// !!!!! DELEGATES sa odstranuju z EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Unsubscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Spusti sa vyvolanie EVENT.
			ldloc							Events
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							instance void EventsAndProperties.CEvents::Raise(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! DRUHY DELEGATE sa odstrani z EVENT.
			ldloc							Events
			ldloc							Delegate2
			// !!!!! DELEGATES sa odstranuju z EVENT NIE cez EVENT (.event [KEYWORD]), ale priamou pracou s DELEGATE OBJECTS.
			call							instance void EventsAndProperties.CEvents::Unsubscribe(class EventsAndProperties.DMyDelegate)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Spusti sa vyvolanie EVENT.
			ldloc							Events
			ldstr							"Timmy Anderson"
			ldc.i4							12
			call							instance void EventsAndProperties.CEvents::Raise(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
        .method public hidebysig static void Test4() cil managed
		{
            .locals							init (class EventsAndProperties.CProperties Properties)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!! Vytvori sa instancia CProperty CLASS.
			newobj							instance void EventsAndProperties.CProperties::.ctor()
			stloc							Properties

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			// !!!!! Vola sa SETTER METHOD. Kedze MSIL ani CLR NEMA ZIADNU PODPORU PROPERTIES na urovni MSIL INSTRUCTION, je nutne pracovat s PROPERTIES pomocou jej METHODS.
			ldloc							Properties
			// !!! 1. PARAMETER SETTER METHOD.
			ldstr							"Timmy Anderson"
			// !!! 2. PARAMETER SETTER METHOD.
			ldc.i4							12
			call							instance void EventsAndProperties.CProperties::SetMyProperty(string,int32)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"MAIN - PROPERTY [{0}] !"
			ldloc							Properties
			call							instance string EventsAndProperties.CProperties::GetMyProperty()
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldloc							Properties
			call							instance void EventsAndProperties.CProperties::ResetMyProperty()

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"MAIN - PROPERTY [{0}] !"
			ldloc							Properties
			call							instance string EventsAndProperties.CProperties::GetMyProperty()
			call							string [mscorlib]System.String::Format(string,object)
			call							void [mscorlib]System.Console::WriteLine(string)

			ldstr							"-------------------------------------------------------------------------------"
			call							void [mscorlib]System.Console::WriteLine(string)

			ret
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        .method public static void Execute() cil managed
		{
            .entrypoint

			//call							void EventsAndProperties.CEventsAndProperties::Test1()
			//call							void EventsAndProperties.CEventsAndProperties::Test2()
			//call							void EventsAndProperties.CEventsAndProperties::Test3()
			call							void EventsAndProperties.CEventsAndProperties::Test4()

            ret
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------