using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace AppDomainTests
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Domain_DomainUnload(object Sender, EventArgs E)
		{
			Console.WriteLine(string.Format("APP DOMAIN [{0}] was UNLOADED !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CallbackCalledInRemoteAppDomain()
		{
			Console.WriteLine(string.Format("Code is EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
		private static void CallbackThrowExceptionInRemoteAppDomain()
		{
			try
			{
				Console.WriteLine(string.Format("Code is EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));

				throw(new Exception("EXCEPTION in REMOTE APP DOMAIN !!!"));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));

				// !!!!! Ak sa EXCEPTION z APP DOMAIN VYHODI VON, tak PROCESS NESKONCI, pretoze APP DOMAIN su NEZAVISLE.
				throw;
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void MultipleAppDomainsThread(object Param)
		{
			AppDomain											Domain=(AppDomain) Param;
			string												DomainName=Domain.FriendlyName;

			try
			{
				Domain.ExecuteAssembly("ExecuteAppDomainAssembly.exe");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,DomainName));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void MultipleAppDomains()
		{
			AppDomain											Domain1=AppDomain.CreateDomain("Domain1");
			AppDomain											Domain2=AppDomain.CreateDomain("Domain2");

			Task												Domain1Task=new Task(MultipleAppDomainsThread,Domain1);
			Task												Domain2Task=new Task(MultipleAppDomainsThread,Domain2);

			Domain1Task.Start();
			Domain2Task.Start();

			Domain1Task.Wait();
			Domain2Task.Wait();
		}
//-------------------------------------------------------------------------------------------------------
		private static void UnloadAppDomains()
		{
			AppDomain											Domain1=AppDomain.CreateDomain("Domain1");
			AppDomain											Domain2=AppDomain.CreateDomain("Domain2");

			Task												Domain1Task=new Task(MultipleAppDomainsThread,Domain1);
			Task												Domain2Task=new Task(MultipleAppDomainsThread,Domain2);

			Domain1Task.Start();
			Domain2Task.Start();

			Domain1Task.Wait();
			Domain2Task.Wait();

			// !!! Vykonam UNLOAD APP DOMAINS.
			AppDomain.Unload(Domain1);
			AppDomain.Unload(Domain2);

			Console.WriteLine("APP DOMAINS UNLOADED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void UnloadAppDomainsPrematurely()
		{
			AppDomain											Domain1=AppDomain.CreateDomain("Domain1");
			AppDomain											Domain2=AppDomain.CreateDomain("Domain2");

			Domain1.DomainUnload+=new EventHandler(Domain_DomainUnload);
			Domain2.DomainUnload+=new EventHandler(Domain_DomainUnload);

			Task												Domain1Task=new Task(MultipleAppDomainsThread,Domain1);
			Task												Domain2Task=new Task(MultipleAppDomainsThread,Domain2);

			Domain1Task.Start();
			Domain2Task.Start();

			Thread.Sleep(1000);

			// !!! Vykonam UNLOAD APP DOMAINS.
			AppDomain.Unload(Domain1);
			AppDomain.Unload(Domain2);

			Console.WriteLine("APP DOMAINS UNLOADED !");
		}
//-------------------------------------------------------------------------------------------------------
		private static void CallbackAppDomains()
		{
			AppDomain											Domain1=AppDomain.CreateDomain("Domain1");
			AppDomain											Domain2=AppDomain.CreateDomain("Domain2");

			// !!!!! METHOD AppDomain.DoCallBack() spusta CALLBACK METHOD v REMOTE APP DOMAIN.
			Domain1.DoCallBack(CallbackCalledInRemoteAppDomain);
			Domain2.DoCallBack(CallbackCalledInRemoteAppDomain);
		}
//-------------------------------------------------------------------------------------------------------
		private static void CrossAppDomainTest()
		{
			Console.WriteLine("NO MARSHALLING !");

			CCrossAppDomainTestNoMarshal						Test1=new CCrossAppDomainTestNoMarshal();

			Test1.CreateAppDomain();

			Console.WriteLine("".PadLeft(79,'-'));

			Console.WriteLine("MARSHALLING by REFERENCE !");

			CCrossAppDomainTestMarshalByReference				Test2=new CCrossAppDomainTestMarshalByReference();

			Test2.CreateAppDomain();

			Console.WriteLine("".PadLeft(79,'-'));

			Console.WriteLine("MARSHALLING by VALUE !");

			CCrossAppDomainTestMarshalByValue					Test3=new CCrossAppDomainTestMarshalByValue();

			Test3.CreateAppDomain();
		}
//-------------------------------------------------------------------------------------------------------
		private static void ThrowExceptionInRemoteAppDomain()
		{
			try
			{
				AppDomain										Domain=AppDomain.CreateDomain("MyAppDomain");

				// !!!!! METHOD AppDomain.DoCallBack() spusta CALLBACK METHOD v REMOTE APP DOMAIN.
				// !!!!! Kedze REMOTE APP DOMAIN hodila UNHANDLED EXCEPTION, tak tato je RETRHOWN v DEFAULT APP DOMAIN.
				Domain.DoCallBack(CallbackThrowExceptionInRemoteAppDomain);
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				//MultipleAppDomains();
				//UnloadAppDomains();
				//UnloadAppDomainsPrematurely();
				//CallbackAppDomains();
				//CrossAppDomainTest();
				ThrowExceptionInRemoteAppDomain();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] in APP DOMAIN [{1}] !",E.Message,AppDomain.CurrentDomain));
			}

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------