﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingCoreIdentity.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CAddRemoveUserToRoleModel
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MRoleID;
		private string											MRoleName;
		private CAddRemoveUserToRole[]							MUsersInRole;
		private CAddRemoveUserToRole[]							MUsersNotInRole;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CAddRemoveUserToRoleModel()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public CAddRemoveUserToRoleModel(string RoleID, string RoleName, CAddRemoveUserToRole[] UsersInRole, CAddRemoveUserToRole[] UsersNotInRole)
		{
			MRoleID=RoleID;
			MRoleName=RoleName;
			MUsersInRole=UsersInRole;
			MUsersNotInRole=UsersNotInRole;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											RoleID
		{
			get
			{
				return(MRoleID);
			}
			set
			{
				MRoleID=value;
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
		public CAddRemoveUserToRole[]							UsersInRole
		{
			get
			{
				return(MUsersInRole);
			}
			set
			{
				MUsersInRole=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public CAddRemoveUserToRole[]							UsersNotInRole
		{
			get
			{
				return(MUsersNotInRole);
			}
			set
			{
				MUsersNotInRole=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------