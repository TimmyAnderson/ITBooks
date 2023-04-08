using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DomainNeutralAssembliesByCode
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void CallbackCalledInRemoteAppDomain()
		{
			Console.WriteLine(string.Format("Code is EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void CallbackAppDomains()
		{
			AppDomainSetup										Setup1=new AppDomainSetup();
			AppDomainSetup										Setup2=new AppDomainSetup();

			// !!!!! Nastavim, aby sa ASSEMBLIES nacitavali ako DOMAIN-NEUTRAL ASSEMBLIES.
			Setup1.LoaderOptimization=LoaderOptimization.MultiDomain;
			Setup2.LoaderOptimization=LoaderOptimization.MultiDomain;

			AppDomain											Domain1=AppDomain.CreateDomain("Domain1",null,Setup1);
			AppDomain											Domain2=AppDomain.CreateDomain("Domain2",null,Setup2);

			// !!!!! METHOD AppDomain.DoCallBack() spusta CALLBACK METHOD v REMOTE APP DOMAIN.
			Domain1.DoCallBack(CallbackCalledInRemoteAppDomain);
			Domain2.DoCallBack(CallbackCalledInRemoteAppDomain);
		}
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				CallbackAppDomains();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------