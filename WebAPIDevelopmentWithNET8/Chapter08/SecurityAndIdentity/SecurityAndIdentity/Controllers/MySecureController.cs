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
	public class MySecureController : ControllerBase
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
		[Authorize(Roles=CSecurityRoles.ADMINISTRATORS)]
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
		[Authorize(Roles=$"{CSecurityRoles.ADMINISTRATORS},{CSecurityRoles.USERS}")]
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
		[Authorize(Roles=CSecurityRoles.ADMINISTRATORS)]
		[Authorize(Roles=CSecurityRoles.USERS)]
		[HttpGet("SecureMethodUsersAndAdministrators")]
		public string SecureMethodUsersAndAdministrators()
		{
			string												MethodName=nameof(SecureMethodUsersAndAdministrators);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje POLICY [CIdentityPolicies.MY_POLICY_ROLE_AUTHORIZATION_ADMINISTRATORS_OR_VIPS] na zaklade ktorej k ACTION METHOD maju pristup AUTHENTICATED USERS, ktori maju ROLE [CIdentityRoles.ADMINISTRATORS] a zaroven aj ROLE [CIdentityRoles.VIPS].
		[Authorize(Policy=CSecurityPolicies.MY_POLICY_ROLE_AUTHORIZATION_ADMINISTRATORS_OR_VIPS)]
		[HttpGet("SecureMethodVIPsOrAdministrators")]
		public string SecureMethodVIPsOrAdministrators()
		{
			string												MethodName=nameof(SecureMethodUsersAndAdministrators);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje POLICY [CIdentityPolicies.MY_POLICY_CLAIMS_AUTHORIZATION_VIPS_ONLY] na zaklade ktorej k ACTION METHOD maju pristup AUTHENTICATED USERS, ktori maju CLAIM [CIdentityClaims.MY_CLAIM_1] so spravne nastavenou VALUE.
		[Authorize(Policy=CSecurityPolicies.MY_POLICY_CLAIMS_AUTHORIZATION_VIP_ONLY)]
		[HttpGet("SecureMethodVIPOnly")]
		public string SecureMethodVIPOnly()
		{
			string												MethodName=nameof(SecureMethodVIPOnly);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje POLICY [CIdentityPolicies.MY_POLICY_CLAIMS_AUTHORIZATION_ADMINISTRATOR_OR_VIP] na zaklade ktorej k ACTION METHOD maju pristup AUTHENTICATED USERS, ktori maju CLAIM [CIdentityClaims.MY_CLAIM_2] so spravne nastavenou VALUE.
		[Authorize(Policy=CSecurityPolicies.MY_POLICY_CLAIMS_AUTHORIZATION_ADMINISTRATOR_OR_VIP)]
		[HttpGet("SecureMethodAdministratorOrVIP")]
		public string SecureMethodAdministratorOrVIP()
		{
			string												MethodName=nameof(SecureMethodAdministratorOrVIP);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje POLICY [CIdentityPolicies.MY_POLICY_POLICY_AUTHORIZATION_ADMINISTRATOR] na zaklade ktorej k ACTION METHOD maju pristup AUTHENTICATED USERS, splnaju CUSTOM POLICY AUTHROZATION.
		[Authorize(Policy=CSecurityPolicies.MY_POLICY_POLICY_AUTHORIZATION_ADMINISTRATOR)]
		[HttpGet("SecureMethodPolicyAuthorizationAdministrator")]
		public string SecureMethodPolicyAuthorizationAdministrator()
		{
			string												MethodName=nameof(SecureMethodPolicyAuthorizationAdministrator);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje POLICY [CIdentityPolicies.MY_POLICY_POLICY_AUTHORIZATION_ADMINISTRATOR_MULTI_HANDLER] na zaklade ktorej k ACTION METHOD maju pristup AUTHENTICATED USERS, splnaju CUSTOM POLICY AUTHROZATION.
		[Authorize(Policy=CSecurityPolicies.MY_POLICY_POLICY_AUTHORIZATION_ADMINISTRATOR_MULTI_HANDLER)]
		[HttpGet("SecureMethodPolicyAuthorizationAdministratorMultiHandler")]
		public string SecureMethodPolicyAuthorizationAdministratorMultiHandler()
		{
			string												MethodName=nameof(SecureMethodPolicyAuthorizationAdministratorMultiHandler);
			string												UserName=HttpContext.User.Identity.Name;
			string												Result=$"METHOD [{MethodName}] - USER [{UserName}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------