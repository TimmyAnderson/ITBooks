using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;
using SecuringWebServicesBearerTokens.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER implementuje API CONTROLLER.
	[ApiController]
	[Route("api/{Controller}/{Action}")]
	public class APINameController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CName[]								MNames;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public APINameController()
		{
			List<CName>											Names=new List<CName>();

			Names.Add(new CName(1,"Timmy","Anderson",12));
			Names.Add(new CName(2,"Jenny","Thompson",13));

			MNames=Names.ToArray();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public CName[] NonSecured()
		{
			CName[]												Names=MNames;

			return(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pri vykonavani AUTHENTICATION pomocou JWT BEARER TOKENS, je nutne v ATTRIBUTE [AuthorizeAttribute] pridat do PROPERTY [AuthenticationSchemes] VALUE [Bearer].
		[Authorize(AuthenticationSchemes="Identity.Application,Bearer")]
		[HttpGet]
		public CName[] Secured()
		{
			CName[]												Names=MNames;

			return(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pri vykonavani AUTHENTICATION pomocou JWT BEARER TOKENS, je nutne v ATTRIBUTE [AuthorizeAttribute] pridat do PROPERTY [AuthenticationSchemes] VALUE [Bearer].
		[Authorize(AuthenticationSchemes="Identity.Application,Bearer",Roles="Administrators")]
		[HttpGet]
		public CName[] SecuredForAdministrators()
		{
			CName[]												Names=MNames;

			return(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Pri vykonavani AUTHENTICATION pomocou JWT BEARER TOKENS, je nutne v ATTRIBUTE [AuthorizeAttribute] pridat do PROPERTY [AuthenticationSchemes] VALUE [Bearer].
		[Authorize(AuthenticationSchemes="Identity.Application,Bearer",Roles="Users")]
		[HttpGet]
		public CName[] SecuredForUsers()
		{
			CName[]												Names=MNames;

			return(Names);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------