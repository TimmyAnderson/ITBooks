using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace NewIdentityAPI
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
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------