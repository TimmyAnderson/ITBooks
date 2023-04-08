﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesUsingCookies.Model
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje DATA pre vymazavanie existujucich USERS v RAZOR PAGES.
	public sealed class CUserDelete
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MID;
		private string											MUserName;
		private string											MEmail;
		private string											MDescription;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CUserDelete()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CUserDelete(string ID, string UserName, string Email, string Description)
		{
			MID=ID;
			MUserName=UserName;
			MEmail=Email;
			MDescription=Description;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											ID
		{
			get
			{
				return(MID);
			}
			set
			{
				MID=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[Required]
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
		[Required]
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
		[Required]
		public string											Description
		{
			get
			{
				return(MDescription);
			}
			set
			{
				MDescription=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------