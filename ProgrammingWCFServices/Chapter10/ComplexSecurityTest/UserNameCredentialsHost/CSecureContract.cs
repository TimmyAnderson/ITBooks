using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Security;
using System.Security.Permissions;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace UserNameCredentialsHost
{
//-------------------------------------------------------------------------------------------------------
	public class CSecureContract : ISecureContract
	{
//-------------------------------------------------------------------------------------------------------
		private void PrintLoggedUser(string FunctionName)
		{
			IPrincipal			CP=Thread.CurrentPrincipal;

			Console.WriteLine(string.Format("-------------------- {0} --------------------",FunctionName));
			Console.WriteLine(string.Format("IsAuthenticated: [{0}] !",CP.Identity.IsAuthenticated.ToString().ToUpper()));
			Console.WriteLine(string.Format("Name: [{0}] !",CP.Identity.Name.ToUpper()));
			Console.WriteLine(string.Format("Is BOY: [{0}] !",CP.IsInRole("Boys").ToString().ToUpper()));
			Console.WriteLine(string.Format("Is GIRL: [{0}] !",CP.IsInRole("Girls").ToString().ToUpper()));
			Console.WriteLine(string.Format("-------------------- {0} --------------------",FunctionName));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Girls")]
		public void JustForGirlsByAttribute()
		{
			PrintLoggedUser("JustForGirlsByAttribute");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Boys")]
		public void JustForBoysByAttribute()
		{
			PrintLoggedUser("JustForBoysByAttribute");
		}
//-------------------------------------------------------------------------------------------------------
		public void JustForBoyTimmyByCode()
		{
			IPrincipal			CP=Thread.CurrentPrincipal;

			if (CP.IsInRole("Boys")==false || CP.Identity.Name!="Timmy")
			{
				SecurityAccessDeniedException			SADE=new SecurityAccessDeniedException("NOT ENOUGH PERMISSIONS !!!");

				throw(SADE);
			}

			PrintLoggedUser("JustForBoyTimmyByCode");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Boys")]
		[PrincipalPermission(SecurityAction.Demand,Role="Girls")]
		public void ForAllAuthentificatedByAttribute()
		{
			PrintLoggedUser("ForAllAuthentificatedByAttribute");
		}
//-------------------------------------------------------------------------------------------------------
		// Nie je potrebny ziaden permission.
		public void ForAll()
		{
			PrintLoggedUser("ForAll");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------