﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Model
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje DATA pre editaciu existujucich ROLES v RAZOR PAGES.
	public sealed class CRoleEdit
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MID;
		private string											MRoleName;
		private string											MDescription;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CRoleEdit()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CRoleEdit(string ID, string RoleName, string Description)
		{
			MID=ID;
			MRoleName=RoleName;
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
		public string											RoleName
		{
			get
			{
				return(MRoleName);
			}
			set
			{
				MRoleName=value;
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