using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace Testing2
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MySecureController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[AllowAnonymous]
		[HttpGet("Anonymous")]
		public CSecureName Anonymous()
		{
			CSecureName											SecureName=new CSecureName("Connor","Phills",15,ESex.E_MALE);

			return(SecureName);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali iba AUTHENTICATED USERS.
		[Authorize(Roles=CRoles.ROLE_1)]
		[HttpGet("ForRole1")]
		public CSecureName ForRole1()
		{
			CSecureName											SecureName=new CSecureName("Timmy","Anderson",12,ESex.E_MALE);

			return(SecureName);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali iba AUTHENTICATED USERS.
		[Authorize(Roles=CRoles.ROLE_2)]
		[HttpGet("ForRole2")]
		public CSecureName ForRole2()
		{
			CSecureName											SecureName=new CSecureName("Jenny","Thompson",13,ESex.E_FEMALE);

			return(SecureName);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali iba AUTHENTICATED USERS.
		[Authorize(Roles=CRoles.ROLE_3)]
		[HttpGet("ForRole3")]
		public CSecureName ForRole3()
		{
			CSecureName											SecureName=new CSecureName("Josh","Hurt",12,ESex.E_MALE);

			return(SecureName);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Authorize] sposobi, ze ACTION METHOD vyzaduje, aby pristup k nej mali iba AUTHENTICATED USERS.
		[Authorize(Roles=$"{CRoles.ROLE_1},{CRoles.ROLE_2},{CRoles.ROLE_3}")]
		[HttpGet("GetClaims")]
		public CSecureClaims GetClaims()
		{
			ClaimsIdentity										ClaimsIdentity=(User.Identity as ClaimsIdentity);
			CSecureClaim[]										Claims=ClaimsIdentity.Claims.Select(P => new CSecureClaim(P.Type,P.Value)).ToArray();
			CSecureClaims										SecureClaims=new CSecureClaims(ClaimsIdentity.AuthenticationType,ClaimsIdentity.Name,Claims);

			return(SecureClaims);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------