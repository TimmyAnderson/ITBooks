using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using System.Security;
using System.Security.Policy;
using System.Security.Permissions;
using System.Security.AccessControl;
//-------------------------------------------------------------------------------------------------------
namespace MyDomainManager
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! INTERFACE IMyDomainAppManager sluzi na komunikaciu z UNMANAGED CODE do MANAGED CODE. UNMANAGED CODE ziska POINTER na CMyDomainAppManager v METHOD CMyHostControl::SetAppDomainManager() a nasledne tento POINTER PRETYPUJE na COM INTERFACE IMyDomainAppManager.
	public sealed class CMyDomainAppManager : AppDomainManager, IMyDomainAppManager
	{
//-------------------------------------------------------------------------------------------------------
		private Mutex											MMutex=new Mutex();
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyDomainAppManager()
		{
			Console.WriteLine("CONSTRUCTOR CMyDomainAppManager() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! METHOD sa vola pri vytvoreni NOVEJ APP DOMAIN.
		private static void AppDomainInitializer(string[] Parameters)
		{
			Console.WriteLine("AppDomainInitializer() - APP DOMAIN [{0} - {1}], Parameter[0]: [{2}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName,Parameters[0]);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override void InitializeNewDomain(AppDomainSetup AppDomainInfo)
		{
			base.InitializeNewDomain(AppDomainInfo);

			// !!! METHOD uz bezi v NOVOVYTVORENEJ APP DOMAIN.
			Console.WriteLine("InitializeNewDomain() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);

			// !!!!! Nastavenie tohto FLAG PRINUTI CLR, aby okolo vytvorenej AppDomainManager (instancia CMyDomainAppManager) vytvoril CCW WRAPPER, ktory zasle do UNMANAGED HOST cez METHOD IHostControl::SetAppDomainManager().
			// !!! Nova instancia AppDomainManager (CMyDomainAppManager) sa vytvara pre KAZDU NOVU APP DOMAIN a kazdy takyto POINTER je zasielany do HOST.
			InitializationFlags=AppDomainManagerInitializationOptions.RegisterWithHost;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void PrintAppCurrentDomainName()
		{
			Console.WriteLine("PrintAppCurrentDomainName() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//-------------------------------------------------------------------------------------------------------
		public void CreateNewDomain(string DomainName)
		{
			Console.WriteLine("!!! BEGIN CreateNewDomain() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);

			AppDomainSetup										Setup=new AppDomainSetup();

			// !!! Spravim nejaku jednoduchu CUSTOMIZATION vytvorenej APP DOMAIN, aby som demonstroval, ze APP DOMAIN MANAGER umoznuje takuto CUSTOMIZATION.
			Setup.AppDomainInitializer=AppDomainInitializer;
			Setup.AppDomainInitializerArguments=new string[]{DomainName.ToUpper()};
			Setup.DisallowCodeDownload=true;

			// !!!!! Kedze bol zaregistrovany CUSTOM APP DOMAIN MANAGER (CLASS CMyDomainAppManager), tak prave TENTO sa pouzije na vytvorenie APP DOMAIN.
			// !!!!! Kedze pre KAZDU APP DOMAIN sa vytvara aj instancia APP DOMAIN MANAGER, okrem APP DOMAIN sa vytvori aj NOVA INSTANCIA CLASS CMyDomainAppManager, ktory sluzi ako CUSTOM APP DOMAIN MANAGER.
			AppDomain											NewDomain=AppDomain.CreateDomain(DomainName,null,Setup);

			// !!! Pre APP DOMAIN ziskam instanciu CUSTOM APP DOMAIN MANAGER, ktore je asociovana s novou APP DOMAIN.
			CMyDomainAppManager									DomainManagerForNewDomain=(CMyDomainAppManager) NewDomain.DomainManager;

			// !!!!! Vypisem nazov ASSEMBLY.
			// !!!!! Tym, ze volam APP DOMAIN cez APP DOMAIN MANAGER, tak kod METHOD PrintAppCurrentDomainName() sa vykona v NOVOVYTVORENEJ APP DOMAIN.
			// !!!!! Namiesto prechodu do NOVEJ APP DOMAIN VOLANIM PrintAppCurrentDomainName() by som mohol vytvorit NOVY THREAD a v NOM vykonat prechod do NOVEJ APP DOMAIN (volanim PrintAppCurrentDomainName()).
			DomainManagerForNewDomain.PrintAppCurrentDomainName();

			// !!! Po skonceni volania METHOD PrintAppCurrentDomainName() sa THREAD vrati do POVODNEJ APP DOMAIN v ktorej bezal PRED VOLANIM METHOD PrintAppCurrentDomainName().
			Console.WriteLine("!!! END CreateNewDomain() - APP DOMAIN [{0} - {1}] !",AppDomain.CurrentDomain.Id,AppDomain.CurrentDomain.FriendlyName);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------