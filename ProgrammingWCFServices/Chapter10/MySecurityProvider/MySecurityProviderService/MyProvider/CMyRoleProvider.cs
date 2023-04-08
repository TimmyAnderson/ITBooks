using System;
using System.Collections.Generic;
using System.Text;
using System.Web.Security;
//-------------------------------------------------------------------------------------------------------
namespace MySecurityProviderService
{
//-------------------------------------------------------------------------------------------------------
	public class CMyRoleProvider : RoleProvider
	{
//-------------------------------------------------------------------------------------------------------
		public override string									ApplicationName
		{
			get
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
			set
			{
				Console.WriteLine(CDebugHelper.GetMethodCallString());
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override void AddUsersToRoles(string[] Usernames, string[] RoleNames)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override void CreateRole(string RoleName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool DeleteRole(string RoleName, bool ThrowOnPopulatedRole)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override string[] FindUsersInRole(string RoleName, string UsernameToMatch)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override string[] GetAllRoles()
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override string[] GetRolesForUser(string Username)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override string[] GetUsersInRole(string RoleName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool IsUserInRole(string Username, string RoleName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			if (Username=="MySQLTest1" && RoleName=="MySQLRole1")
				return(true);
			
			if (Username=="MySQLTest2" && RoleName=="MySQLRole2")
				return(true);

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public override void RemoveUsersFromRoles(string[] Usernames, string[] RoleNames)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		public override bool RoleExists(string RoleName)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------