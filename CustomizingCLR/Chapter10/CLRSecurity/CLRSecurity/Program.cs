using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Security;
using System.Security.Policy;
using System.Security.Permissions;
using System.Security.AccessControl;
//------------------------------------------------------------------------------------------------------
namespace CLRSecurity
{
//------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void CallbackCalledInRemoteAppDomain()
		{
			Console.WriteLine(string.Format("Code is EXECUTED in APP DOMAIN [{0}] !",AppDomain.CurrentDomain.FriendlyName));
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		private static void PrintAssemblyEvidences()
		{
			Assembly											ExecutingAssembly=Assembly.GetExecutingAssembly();
			Evidence											ExecutingAssemblyEvidence=ExecutingAssembly.Evidence;

			Console.WriteLine(string.Format("ExecutingAssembly: [{0}] !",ExecutingAssembly.FullName));
			Console.WriteLine();

			/*
			// !!! DEPRECATED, ale FUNGUJE.
			IEnumerator											Evidences=ExecutingAssemblyEvidence.GetEnumerator();

			while(Evidences.MoveNext()==true)
			{
				Console.WriteLine(string.Format("EVIDENCE: [{0}] !",Evidences.Current));
			}
			*/

			// !!! Vracia zoznam CLR a HOST EVIDENCES.
			IEnumerator											AssemblyEvidences=ExecutingAssemblyEvidence.GetAssemblyEnumerator();

			while(AssemblyEvidences.MoveNext()==true)
			{
				Console.WriteLine(string.Format("ASSEMBLY EVIDENCE: [{0}] !",AssemblyEvidences.Current));
			}

			// !!! Vracia zoznam ASSEMBLY EVIDENCES.
			IEnumerator											HostEvidences=ExecutingAssemblyEvidence.GetHostEnumerator();

			while(HostEvidences.MoveNext()==true)
			{
				Console.WriteLine(string.Format("HOST EVIDENCE: [{0}] !",HostEvidences.Current));
			}
		}
//------------------------------------------------------------------------------------------------------
		private static void PermissionsDemand()
		{
			try
			{
				RegistryPermission									PermissionsToCheck=new RegistryPermission(RegistryPermissionAccess.AllAccess,AccessControlActions.Change,@"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\.NETFramework");

				PermissionsToCheck.Demand();

				Console.WriteLine("PERMISSION was GRANTED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}

			try
			{
				FileIOPermission								PermissionsToCheck=new FileIOPermission(FileIOPermissionAccess.AllAccess,AccessControlActions.Change,@"C:\pagefile.sys");

				PermissionsToCheck.Demand();

				Console.WriteLine("PERMISSION was GRANTED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}

			try
			{
				PrincipalPermission								PermissionsToCheck=new PrincipalPermission("XXX","YYY",true);

				PermissionsToCheck.Demand();

				Console.WriteLine("PERMISSION was GRANTED !");
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}
		}
//------------------------------------------------------------------------------------------------------
		private static void LoadAssemblyAndSetEvidence()
		{
			try
			{
				Evidence										MyEvidence=new Evidence();

				// !!! Pridam CUSTOM EVIDENCES do EVIDENCE.
				MyEvidence.AddAssemblyEvidence(new CAssemblyCustomEvidence());
				MyEvidence.AddHostEvidence(new CHostCustomEvidence());

				// !!! Pri citani ASSEMBLY nastavim CUSTOM EVIDENCE.
				// !!!!! METHOD je OBSOLETE a bezi IBA ak je v AP.CONFIG nastaveny ELEMENT 'NetFx40_LegacySecurityPolicy'.
				Assembly										DummyAssembly=Assembly.Load("DummyAssembly",MyEvidence);
				
				Console.WriteLine("ASSEMBLY LOADED !");

				Evidence										AssemblyEvidence=DummyAssembly.Evidence;

				// !!! Vracia zoznam CLR a HOST EVIDENCES.
				IEnumerator										AssemblyEvidences=AssemblyEvidence.GetAssemblyEnumerator();

				while(AssemblyEvidences.MoveNext()==true)
				{
					Console.WriteLine(string.Format("ASSEMBLY EVIDENCE: [{0}] !",AssemblyEvidences.Current));
				}

				// !!! Vracia zoznam ASSEMBLY EVIDENCES.
				IEnumerator										HostEvidences=AssemblyEvidence.GetHostEnumerator();

				while(HostEvidences.MoveNext()==true)
				{
					Console.WriteLine(string.Format("HOST EVIDENCE: [{0}] !",HostEvidences.Current));
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}
		}
//------------------------------------------------------------------------------------------------------
		private static void AppDomainEvidence()
		{
			Evidence											CustomEvidence=new Evidence();

			// !!! Dostatocne PERMISSIONS.
			//CustomEvidence.AddHostEvidence<Zone>(new Zone(SecurityZone.MyComputer));

			// !!! Nedostatocne PERMISSIONS - HODI sa EXCEPTION SecurityException.
			CustomEvidence.AddHostEvidence<Zone>(new Zone(SecurityZone.Untrusted));

			AppDomain											Domain=AppDomain.CreateDomain("CustomDomain",CustomEvidence);

			// !!!!! METHOD AppDomain.DoCallBack() spusta CALLBACK METHOD v REMOTE APP DOMAIN.
			Domain.DoCallBack(CallbackCalledInRemoteAppDomain);
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				//PrintAssemblyEvidences();
				//PermissionsDemand();
				//LoadAssemblyAndSetEvidence();
				AppDomainEvidence();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION [{0}] !",E.Message));
			}

			Console.WriteLine("Press any KEY to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------