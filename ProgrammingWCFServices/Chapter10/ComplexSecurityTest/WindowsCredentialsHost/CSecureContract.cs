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
namespace WindowsCredentialsHost
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
			Console.WriteLine(string.Format("Is ADMINISTRATOR: [{0}] !",CP.IsInRole("Administrators").ToString().ToUpper()));
			Console.WriteLine(string.Format("-------------------- {0} --------------------",FunctionName));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Administrators")]
		public void JustAdministrators()
		{
			PrintLoggedUser("JustAdministrators");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Boys")]
		public void JustBoys()
		{
			PrintLoggedUser("JustBoys");
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