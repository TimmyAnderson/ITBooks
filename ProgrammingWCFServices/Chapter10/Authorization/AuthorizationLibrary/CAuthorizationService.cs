using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Transactions;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using System.Security.Principal;
using System.Security.Permissions;
using System.ServiceModel.Security;
//-------------------------------------------------------------------------------------------------------
// 1. Autorizaciu je mozne robit bud deklarativne, alebo manualne.
// 2. Deklarativne sa urcuje definovanim atributu [PrincipalPermission] na metodu service, kde definuje rolu, ktora moze pristupovat k daje metode. Ak chcem viac roly potom mozem pridat viac atributov, pricom pristup bude umozneny hocktorej role z deklarovanych. V mene role je treba definovan pri Windows autnetifikacii aj meno domeny.
// 3. Manualna autrizacia sa robi zistenim ci prihlaseny user je v danej role. To sa da urobit ziskanim IPrincipal objektu z Thread.CurrentPrincipal a volanim jeho metody IsInRole().
// 4. Autorizaciu je potrebne vyziadat na host objekte nastavenim ServiceHost.Authorization.PrincipalPermissionMode.
// !!! 5. Ak zlyha DEKLARATIVNA autorizacia metody tak proxy ZIJE DALEJ a nedostane sa do Faulted state.
// !!! 6. NEVYHODA MANUALNEJ autorizacie je, ze ak neoverim uzivatela musim hodit exception a TATO EXCEPTION MUSI BYT SUCASTOU Fault contract.
// !!! 7. Autorizacia podla mena MI NEFUNGUJE. Nechce sa mi s tym babrat, ze preco aj tak sa to nebude pouzivat.
//-------------------------------------------------------------------------------------------------------
namespace AuthorizationLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CAuthorizationService : IAuthorizationContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CAuthorizationService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Administrators")]
		[PrincipalPermission(SecurityAction.Demand,Role="Users")]
		public void AutoAuthorization1()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("AUTORIZHED");
		}
//-------------------------------------------------------------------------------------------------------
		// Autorizacia na User Name.
		[PrincipalPermission(SecurityAction.Demand,Name="Test")]
		public void AutoAuthorization2()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("AUTORIZHED");
		}
//-------------------------------------------------------------------------------------------------------
		// Autorizacia na User Name.
		[PrincipalPermission(SecurityAction.Demand,Role="Administrators")]
		public void AutoAuthorization3()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("AUTORIZHED");
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualAuthorization1()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			IPrincipal			Principal=Thread.CurrentPrincipal;
			WindowsIdentity		WI=(WindowsIdentity) Principal.Identity;

			Console.WriteLine(string.Format("Name: {0} !",WI.Name));

			// Test na rolu.
			if (Principal.IsInRole("Users")==false)
			{
				SecurityAccessDeniedException					SADE=new SecurityAccessDeniedException("You are not part of Users role !!!");
				FaultException<SecurityAccessDeniedException>	E=new FaultException<SecurityAccessDeniedException>(SADE,new FaultReason(SADE.Message));

				throw(E);
			}

			Console.WriteLine("AUTORIZHED");

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualAuthorization2()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			IPrincipal			Principal=Thread.CurrentPrincipal;
			WindowsIdentity		WI=(WindowsIdentity) Principal.Identity;

			Console.WriteLine(string.Format("Name: {0} !",WI.Name));

			// Test na rolu.
			if (Principal.IsInRole("Administrators")==false)
			{
				SecurityAccessDeniedException					SADE=new SecurityAccessDeniedException("You are not part of Administrators role !!!");
				FaultException<SecurityAccessDeniedException>	E=new FaultException<SecurityAccessDeniedException>(SADE,new FaultReason(SADE.Message));

				throw(E);
			}

			Console.WriteLine("AUTORIZHED");

			Console.WriteLine(CDebugHelper.GetMethodCallString(2));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------