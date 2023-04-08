﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Model
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS reprezentuje ROLE v RAZOR PAGES.
	public sealed class CRole
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MID;
		private string											MRoleName;
		private string											MDescription;
		private string											MUsers;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CRole()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CRole(string ID, string RoleName, string Description, string Users)
		{
			MID=ID;
			MRoleName=RoleName;
			MDescription=Description;
			MUsers=Users;
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
		public string											Users
		{
			get
			{
				return(MUsers);
			}
			set
			{
				MUsers=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------