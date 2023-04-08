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
namespace MySecurityProviderLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CMySecurityProviderService : IMySecurityProviderContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CMySecurityProviderService()
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
		[PrincipalPermission(SecurityAction.Demand,Role="MySQLRole1")]
		public void AutoAuthorization()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("AUTORIZHED");
		}
//-------------------------------------------------------------------------------------------------------
		public void ManualAuthorization()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString(1));

			// V skutocnosti vracia RoleProviderPrincipal, ale to je skryta trieda.
			IPrincipal			Principal=Thread.CurrentPrincipal;
			GenericIdentity		GI=(GenericIdentity) Principal.Identity;

			Console.WriteLine(string.Format("Name: {0} !",GI.Name));

			// Test na rolu.
			if (Principal.IsInRole("MySQLRole1")==false)
			{
				SecurityAccessDeniedException					SADE=new SecurityAccessDeniedException("You are not part of Users role !!!");
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