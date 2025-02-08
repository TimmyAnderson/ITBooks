using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MySecureRolesAuthorizationController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali iba AUTHENTICATED USERS.
		[Authorize]
		[HttpGet("SecureMethodAllAuthenticatedUsers")]
		public string SecureMethodAllAuthenticatedUsers()
		{
			string												MethodName=nameof(SecureMethodAllAuthenticatedUsers);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali AUTHENTICATED USERS, ktori maju ROLE [Roles=CIdentityRoles.ADMINISTRATORS].
		[Authorize(Roles=CIdentityRoles.ADMINISTRATORS)]
		[HttpGet("SecureMethodAdministratorsOnly")]
		public string SecureMethodAdministratorsOnly()
		{
			string												MethodName=nameof(SecureMethodAdministratorsOnly);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali AUTHENTICATED USERS, ktori maju ROLE [CIdentityRoles.ADMINISTRATORS], alebo ROLE [CIdentityRoles.USERS].
		[Authorize(Roles=$"{CIdentityRoles.ADMINISTRATORS},{CIdentityRoles.USERS}")]
		[HttpGet("SecureMethodUsersOrAdministrators")]
		public string SecureMethodUsersOrAdministrators()
		{
			string												MethodName=nameof(SecureMethodUsersOrAdministrators);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali AUTHENTICATED USERS, ktori maju ROLE [CIdentityRoles.ADMINISTRATORS] a zaroven aj ROLE [CIdentityRoles.USERS].
		[Authorize(Roles=CIdentityRoles.ADMINISTRATORS)]
		[Authorize(Roles=CIdentityRoles.USERS)]
		[HttpGet("SecureMethodUsersAndAdministrators")]
		public string SecureMethodUsersAndAdministrators()
		{
			string												MethodName=nameof(SecureMethodUsersAndAdministrators);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje POLICY na zaklade ktorej k ACTION METHOD maju pristup AUTHENTICATED USERS, ktori maju ROLE [CIdentityRoles.ADMINISTRATORS] a zaroven aj ROLE [CIdentityRoles.VIPS].
		[Authorize(Policy=Program.MY_POLICY_ADMINISTRATORS_OR_VIPS)]
		[HttpGet("SecureMethodVIPsOrAdministrators")]
		public string SecureMethodVIPsOrAdministrators()
		{
			string												MethodName=nameof(SecureMethodUsersAndAdministrators);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------