using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Security.Permissions;
using System.Security.Principal;
using System.ServiceModel.Security;
//-------------------------------------------------------------------------------------------------------
namespace SharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CMSWindowsService : IMSWindowsService
	{
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Name="WORK\\Administrator")]
		public void JustForAdministrator()
		{
			CHelperClass.ShowWindowsAuthentificationInfo("JustForAdministrator");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Administrators")]
		public void JustForAdministrators()
		{
			CHelperClass.ShowWindowsAuthentificationInfo("JustForAdministrators");
		}
//-------------------------------------------------------------------------------------------------------
		// Nie je potrebny ziaden permission.
		public void ForAll()
		{
			CHelperClass.ShowWindowsAuthentificationInfo("ForAll");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------