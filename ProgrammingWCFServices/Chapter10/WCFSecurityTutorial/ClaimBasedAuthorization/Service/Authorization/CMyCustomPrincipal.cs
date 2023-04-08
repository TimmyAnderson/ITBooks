﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace Service
{
//-------------------------------------------------------------------------------------------------------
	// Trieda predstavuje implementaciu CUSTOM Principal.
	public class CMyCustomPrincipal : IPrincipal
	{
//-------------------------------------------------------------------------------------------------------
		private IIdentity										MIdentity;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyCustomPrincipal(IIdentity Identity)
		{
			MIdentity=Identity;
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
			bool		Ret=CRolesStore.AuthorizationStore.IsInRole(MIdentity.Name,Role);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------