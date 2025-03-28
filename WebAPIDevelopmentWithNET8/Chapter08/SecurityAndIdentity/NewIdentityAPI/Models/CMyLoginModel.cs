﻿using Newtonsoft.Json;
//----------------------------------------------------------------------------------------------------------------------
namespace NewIdentityAPI
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS sa MUSI zhodovat s NEW IDENTITY API, ktory sa da zistit pomocou SWAGGER.
	public sealed class CMyLoginModel
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MEMail;
		private string											MPassword;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CMyLoginModel()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CMyLoginModel(string EMail, string Password)
		{
			MEMail=EMail;
			MPassword=Password;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("email")]
		public string											EMail
		{
			get
			{
				return(MEMail);
			}
			set
			{
				MEMail=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("password")]
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