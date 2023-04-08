#include "stdafx.h"
#include "CSimpleWCFProxy.h"
//-------------------------------------------------------------------------------------------------------
using namespace System;
using namespace SimpleWCFLibrary;
//-------------------------------------------------------------------------------------------------------
int main(array<System::String ^> ^args)
{
	Console::WriteLine("Press any key to START !");
	Console::ReadLine();

	CSimpleWCFProxy^					SimpleWCFProxy=nullptr;

	// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
	Binding^							TCPBinding=gcnew NetTcpBinding();

	try
	{
		String^							Answer=nullptr;



		SimpleWCFProxy=gcnew CSimpleWCFProxy(TCPBinding,"net.tcp://localhost:9001/ISimpleWCFContract");

		Console::WriteLine("SayHello() called !");
		Answer=SimpleWCFProxy->SayHello("Timmy");
		Console::WriteLine(String::Format("SayHello() answered: [{0}] !",Answer));
	}
	catch(Exception^ E)
	{
		Console::WriteLine(String::Format("Exception: [{0}] !",E->Message));
	}
	finally
	{
		if (SimpleWCFProxy!=nullptr)
		{
			SimpleWCFProxy->Close();
			SimpleWCFProxy=nullptr;
		}
	}

	Console::WriteLine("Press any key to EXIT !");
	Console::ReadLine();
    return(0);
}
//-------------------------------------------------------------------------------------------------------