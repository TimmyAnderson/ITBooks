﻿using System.ComponentModel.DataAnnotations;
using Newtonsoft.Json;
//----------------------------------------------------------------------------------------------------------------------
namespace NewIdentityAPI
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS sa MUSI zhodovat s NEW IDENTITY API, ktory sa da zistit pomocou SWAGGER.
	public sealed class CMyUserModel
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MEmail;
		private string											MPassword;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CMyUserModel()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CMyUserModel(string Email, string Password)
		{
			MEmail=Email;
			MPassword=Password;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[JsonProperty("email")]
		public string											Email
		{
			get
			{
				return(MEmail);
			}
			set
			{
				MEmail=value;
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