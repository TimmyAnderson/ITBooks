using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Runtime.InteropServices;
//-------------------------------------------------------------------------------------------------------
namespace BagAppDomainManager
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! INTERFACE IBagAppDomainManager sluzi na komunikaciu s UNMANAGED CODE do MANAGED CODE. UNMANAGED CODE ziska POINTER na CBagAppDomainManager v METHOD CBagHostControl::SetAppDomainManager() a nasledne tento POINTER PRETYPUJE na COM INTERFACE IBagAppDomainManager.
	public sealed class CBagAppDomainManager : AppDomainManager, IBagAppDomainManager
	{
//-------------------------------------------------------------------------------------------------------
		public CBagAppDomainManager()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		// !!! METHOD sa vola pri vytvoreni NOVEJ APP DOMAIN.
		private static void AppDomainInitializer(string[] Parameters)
		{
		}
//------------------------------------------------------------------------------------------------------
		// !!! METHOD sa vola pri vytvoreni NOVEJ APP DOMAIN.
		private static void AppDomainInitializerRunBag(string[] Parameters)
		{
			string												BagExecutable=Parameters[0];
			string												RunnableType=Parameters[1];

			try
			{
				Console.WriteLine(string.Format("Trying to LOAD ASSEMBLY [{0}] in APP DOMAIN [{1}] !",BagExecutable,AppDomain.CurrentDomain.FriendlyName));

				Assembly										AssemblyToExecute=Assembly.Load(BagExecutable);

				// !!!!! HODI EXCEPTION BEZ TOHO, aby sa co i len pokusil nacitat ASSEMBLY cez HOST. Vyzera to, ze ExecuteAssembly() NIE JE PODPOROVANE pri implementacii CUSTOM LOADING MANAGER, alebo je potrebne este nieco povolit, ale nezistil som co.
				//AppDomain.CurrentDomain.ExecuteAssembly(BagExecutable);

				Console.WriteLine(string.Format("ASSEMBLY [{0}] was LOADED into APP DOMAIN [{1}] !",BagExecutable,AppDomain.CurrentDomain.FriendlyName));

				Console.WriteLine(string.Format("LOADING TYPE [{0}] into APP DOMAIN [{1}] !",BagExecutable,AppDomain.CurrentDomain.FriendlyName));

				Type											TypeToExecute=AssemblyToExecute.GetType(RunnableType,true,true);

				if (TypeToExecute!=null)
				{
					Console.WriteLine(string.Format("TYPE [{0}] was LOADED into APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));

					// !!! Predpoklada sa, ze Main() je PRIVATE.
					MethodInfo									MI=TypeToExecute.GetMethod("Main",BindingFlags.NonPublic | BindingFlags.Static);

					if (MI!=null)
					{
						Console.WriteLine(string.Format("MAIN METHOD in TYPE [{0}] was FOUND in APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));

						try
						{
							MI.Invoke(null,new object[]{null});

							Console.WriteLine(string.Format("MAIN METHOD in TYPE [{0}] was INVOKED in APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION [{0}] while RUNING CODE from .BAG FILE in APP DOMAIN [{2}] !",E,BagExecutable,AppDomain.CurrentDomain.FriendlyName));
						}
					}
					else
					{
						Console.WriteLine(string.Format("!!! MAIN METHOD in TYPE [{0}] was NOT FOUND in APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));
					}
				}
				else
				{
					Console.WriteLine(string.Format("!!! TYPE [{0}] FAILED to LOAD into APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] while trying to RUN LOAD ASSEMBLY [{1}] in APP DOMAIN [{2}] !",E,BagExecutable,AppDomain.CurrentDomain.FriendlyName));
			}
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
		public void CreateNewDomain(string DomainName)
		{
			AppDomainSetup										Setup=new AppDomainSetup();

			// !!! Spravim nejaku jednoduchu CUSTOMIZATION vytvorenej APP DOMAIN, aby som demonstroval, ze APP DOMAIN MANAGER umoznuje takuto CUSTOMIZATION.
			Setup.AppDomainInitializer=AppDomainInitializer;
			Setup.AppDomainInitializerArguments=new string[]{DomainName.ToUpper()};

			// !!!!! Kedze bol zaregistrovany CUSTOM APP DOMAIN MANAGER (CLASS CBagAppDomainManager), tak prave TENTO sa pouzije na vytvorenie APP DOMAIN.
			// !!!!! Kedze pre KAZDU APP DOMAIN sa vytvara aj instancia APP DOMAIN MANAGER, okrem APP DOMAIN sa vytvori aj NOVA INSTANCIA CLASS CBagAppDomainManager, ktory sluzi ako CUSTOM APP DOMAIN MANAGER.
			AppDomain.CreateDomain(DomainName,null,Setup);
		}
//-------------------------------------------------------------------------------------------------------
		public void CreateNewDomainAndRunBag(string DomainName, string BagExecutable, string RunnableType)
		{
			AppDomainSetup										Setup=new AppDomainSetup();

			Setup.AppDomainInitializer=AppDomainInitializerRunBag;
			Setup.AppDomainInitializerArguments=new string[]{BagExecutable,RunnableType};

			AppDomain.CreateDomain(DomainName,null,Setup);
		}
//-------------------------------------------------------------------------------------------------------
		public void RunBagInDefaultAppDomain(string DomainName, string BagExecutable, string RunnableType)
		{
			try
			{
				Console.WriteLine(string.Format("Trying to LOAD ASSEMBLY [{0}] in APP DOMAIN [{1}] !",BagExecutable,AppDomain.CurrentDomain.FriendlyName));

				// !!!!! MUSIM ZADAT FULLY SPECIFIED NAME. Pri PARTIALLY SPECIFIED NAME to NEFUNGUJE, lebo CLR sa pokusa hladat ASSEMBLY pomocou svojho PROBING MECHANIZMU.
				Assembly										AssemblyToExecute=Assembly.Load(BagExecutable);

				// !!!!! HODI EXCEPTION BEZ TOHO, aby sa co i len pokusil nacitat ASSEMBLY cez HOST. Vyzera to, ze ExecuteAssembly() NIE JE PODPOROVANE pri implementacii CUSTOM LOADING MANAGER, alebo je potrebne este nieco povolit, ale nezistil som co.
				//AppDomain.CurrentDomain.ExecuteAssembly(BagExecutable);

				Console.WriteLine(string.Format("ASSEMBLY [{0}] was LOADED into APP DOMAIN [{1}] !",BagExecutable,AppDomain.CurrentDomain.FriendlyName));

				Console.WriteLine(string.Format("LOADING TYPE [{0}] into APP DOMAIN [{1}] !",BagExecutable,AppDomain.CurrentDomain.FriendlyName));

				Type											TypeToExecute=AssemblyToExecute.GetType(RunnableType,true,true);

				if (TypeToExecute!=null)
				{
					Console.WriteLine(string.Format("TYPE [{0}] was LOADED into APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));

					// !!! Predpoklada sa, ze Main() je PRIVATE.
					MethodInfo									MI=TypeToExecute.GetMethod("Main",BindingFlags.NonPublic | BindingFlags.Static);

					if (MI!=null)
					{
						Console.WriteLine(string.Format("MAIN METHOD in TYPE [{0}] was FOUND in APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));

						try
						{
							MI.Invoke(null,new object[]{null});

							Console.WriteLine(string.Format("MAIN METHOD in TYPE [{0}] was INVOKED in APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION [{0}] while RUNING CODE from .BAG FILE in APP DOMAIN [{2}] !",E,BagExecutable,AppDomain.CurrentDomain.FriendlyName));
						}
					}
					else
					{
						Console.WriteLine(string.Format("!!! MAIN METHOD in TYPE [{0}] was NOT FOUND in APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));
					}
				}
				else
				{
					Console.WriteLine(string.Format("!!! TYPE [{0}] FAILED to LOAD into APP DOMAIN [{1}] !",RunnableType,AppDomain.CurrentDomain.FriendlyName));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] while trying to RUN LOAD ASSEMBLY [{1}] in APP DOMAIN [{2}] !",E,BagExecutable,AppDomain.CurrentDomain.FriendlyName));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------