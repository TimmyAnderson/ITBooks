#pragma once
//-------------------------------------------------------------------------------------------------------
using namespace System;
using namespace SimpleWCFLibrary;
using namespace System::ServiceModel;
using namespace System::ServiceModel::Channels;
//-------------------------------------------------------------------------------------------------------
ref class CSimpleWCFProxy : ClientBase<ISimpleWCFContract^>, ISimpleWCFContract
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!!!! Pokial som tuto KVAZI IMPLEMENTACIU EVENT NEPRIDAL, tak mi C++ NECHCEL KOMPILOVAT PROJEKT.
		event EventHandler^ Opening
		{
			public:
			virtual void add (EventHandler^ name)
			{
			}
			virtual void remove(EventHandler^ name)
			{
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Pokial som tuto KVAZI IMPLEMENTACIU EVENT NEPRIDAL, tak mi C++ NECHCEL KOMPILOVAT PROJEKT.
		event EventHandler^ Opened
		{
			public:
			virtual void add (EventHandler^ name)
			{
			}
			virtual void remove(EventHandler^ name)
			{
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Pokial som tuto KVAZI IMPLEMENTACIU EVENT NEPRIDAL, tak mi C++ NECHCEL KOMPILOVAT PROJEKT.
		event EventHandler^ Closing
		{
			public:
			virtual void add (EventHandler^ name)
			{
			}
			virtual void remove(EventHandler^ name)
			{
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Pokial som tuto KVAZI IMPLEMENTACIU EVENT NEPRIDAL, tak mi C++ NECHCEL KOMPILOVAT PROJEKT.
		event EventHandler^ Closed
		{
			public:
			virtual void add (EventHandler^ name)
			{
			}
			virtual void remove(EventHandler^ name)
			{
			}
		}
//-------------------------------------------------------------------------------------------------------
		// !!!!! Pokial som tuto KVAZI IMPLEMENTACIU EVENT NEPRIDAL, tak mi C++ NECHCEL KOMPILOVAT PROJEKT.
		event EventHandler^ Faulted
		{
			public:
			virtual void add (EventHandler^ name)
			{
			}
			virtual void remove(EventHandler^ name)
			{
			}
		}
//-------------------------------------------------------------------------------------------------------
	public:
		virtual String^ SayHello(String^ Name);
//-------------------------------------------------------------------------------------------------------
	public:
		CSimpleWCFProxy(Binding^ ProxyBinding, String^ EA);
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------