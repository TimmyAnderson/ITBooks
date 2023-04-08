﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security.Principal;
//-------------------------------------------------------------------------------------------------------
namespace CustomRoleBasedSecurity
{
//-------------------------------------------------------------------------------------------------------
	public class CMyCustomIdentity : IIdentity
	{
//-------------------------------------------------------------------------------------------------------
		private string											MName;
		private bool											MIsAuthenticated;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyCustomIdentity(string Name, bool IsAuthenticated)
		{
			MName=Name;
			MIsAuthenticated=IsAuthenticated;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											AuthenticationType
		{
			get
			{
				return("CMyCustomIdentity");
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											Name
		{
			get
			{
				return(MName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsAuthenticated
		{
			get
			{
				return(MIsAuthenticated);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------