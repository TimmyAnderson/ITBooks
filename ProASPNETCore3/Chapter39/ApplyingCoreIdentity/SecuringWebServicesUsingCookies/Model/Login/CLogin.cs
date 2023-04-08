﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesUsingCookies.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CLogin
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MUserName;
		private string											MPassword;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CLogin()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CLogin(string UserName, string Password)
		{
			MUserName=UserName;
			MPassword=Password;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											UserName
		{
			get
			{
				return(MUserName);
			}
			set
			{
				MUserName=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string											Password
		{
			get
			{
				return(MPassword);
			}
			set
			{
				MPassword=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------