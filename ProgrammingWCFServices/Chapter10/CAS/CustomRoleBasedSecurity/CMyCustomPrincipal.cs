﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace CustomRoleBasedSecurity
{
//-------------------------------------------------------------------------------------------------------
	public class CMyCustomPrincipal : IPrincipal
	{
//-------------------------------------------------------------------------------------------------------
		private IIdentity										MIdentity;
		private string[]										MIdentityRoles;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyCustomPrincipal(IIdentity Identity, string[] IdentityRoles)
		{
			MIdentity=Identity;
			MIdentityRoles=IdentityRoles;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IIdentity										Identity
		{
			get
			{
				return(MIdentity);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool IsInRole(string Role)
		{
			bool			Ret=MIdentityRoles.Contains(Role);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------