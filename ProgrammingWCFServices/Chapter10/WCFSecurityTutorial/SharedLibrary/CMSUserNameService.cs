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
	public class CMSUserNameService : IMSUserNameService
	{
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Girls")]
		public void JustForGirlsByAttribute()
		{
			CHelperClass.ShowUserNameAuthentificationInfo("JustForGirlsByAttribute");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Boys")]
		public void JustForBoysByAttribute()
		{
			CHelperClass.ShowUserNameAuthentificationInfo("JustForBoysByAttribute");
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

			CHelperClass.ShowUserNameAuthentificationInfo("JustForBoyTimmyByCode");
		}
//-------------------------------------------------------------------------------------------------------
		[PrincipalPermission(SecurityAction.Demand,Role="Boys")]
		[PrincipalPermission(SecurityAction.Demand,Role="Girls")]
		public void ForBoysAndGirlsByAttribute()
		{
			CHelperClass.ShowUserNameAuthentificationInfo("ForBoysAndGirlsByAttribute");
		}
//-------------------------------------------------------------------------------------------------------
		// Nie je potrebny ziaden permission.
		public void ForAll()
		{
			CHelperClass.ShowUserNameAuthentificationInfo("ForAll");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------