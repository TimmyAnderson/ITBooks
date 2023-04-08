using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Security;
using System.Security.Principal;
using System.Security.Permissions;
//-------------------------------------------------------------------------------------------------------
namespace CustomRoleBasedSecurity
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		// !!!!! VYZADUJEM aby dany Principal MAL PERSMISSION - preto DEMAND.
		[PrincipalPermission(SecurityAction.Demand,Name="Timmy")]
		private static void ProtectedForUser()
		{
			IPrincipal		CP=Thread.CurrentPrincipal;

			Console.WriteLine(string.Format("User: [{0}] ACCESSED: [{1}] !",CP.Identity.Name,"ProtectedForUser()"));
		}
//-------------------------------------------------------------------------------------------------------
		// Timmy je v skupine 'Boys'.
		[PrincipalPermission(SecurityAction.Demand,Role="Boys")]
		private static void ProtectedForGroup()
		{
			IPrincipal		CP=Thread.CurrentPrincipal;

			Console.WriteLine(string.Format("User: [{0}] ACCESSED: [{1}] !",CP.Identity.Name,"ProtectedForGroup()"));
		}
//-------------------------------------------------------------------------------------------------------
		// Timmy nie je v skupine 'Girls'.
		[PrincipalPermission(SecurityAction.Demand,Role="Girls")]
		private static void ProtectedForUNKNOWNGroup()
		{
			IPrincipal		CP=Thread.CurrentPrincipal;

			Console.WriteLine(string.Format("User: [{0}] ACCESSED: [{1}] !",CP.Identity.Name,"ProtectedForUNKNOWNGroup()"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private static void CallAllMethods()
		{
			try
			{
				ProtectedForUser();
			}
			catch(SecurityException E)
			{
				Console.WriteLine(string.Format("ProtectedForUser() - SECURITY EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				ProtectedForGroup();
			}
			catch(SecurityException E)
			{
				Console.WriteLine(string.Format("ProtectedForGroup() - SECURITY EXCEPTION: [{0}] !",E.Message));
			}

			try
			{
				ProtectedForUNKNOWNGroup();
			}
			catch(SecurityException E)
			{
				Console.WriteLine(string.Format("ProtectedForUNKNOWNGroup() - SECURITY EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestDefaultPrincipal()
		{
			CallAllMethods();
		}
//-------------------------------------------------------------------------------------------------------
		private static void TestCustomPrincipal()
		{
			CMyCustomIdentity		I1=new CMyCustomIdentity("Timmy",true);
			CMyCustomPrincipal		P1=new CMyCustomPrincipal(I1, new string[]{"Boys"});

			// !!!!! Nastavim CUSTOM PRINCIPAL.
			Thread.CurrentPrincipal=P1;

			CallAllMethods();

			Console.WriteLine("\n\n\n");


			// !!! Nastavim FALSE na IsAuthenticated.
			CMyCustomIdentity		I2=new CMyCustomIdentity("Timmy",false);
			CMyCustomPrincipal		P2=new CMyCustomPrincipal(I2, new string[]{"Boys"});

			// !!!!! Nastavim CUSTOM PRINCIPAL.
			Thread.CurrentPrincipal=P2;

			CallAllMethods();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//TestDefaultPrincipal();
			TestCustomPrincipal();

			Console.WriteLine(string.Format("Press any key to EXIT !"));
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------