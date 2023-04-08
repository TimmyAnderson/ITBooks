using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;
using SecuringWebServicesUsingCookies.Model;
using SecuringWebServicesUsingCookies.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesUsingCookies.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER poskytuje pre WEB SERVICE CLIENT ACTION METHODS na vykonanie LOGIN a LOGOUT.
	[ApiController]
	[Route("api/{Controller}/{Action}")]
	public class APILoginController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly SignInManager<CCustomUser>				MSignInManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public APILoginController(SignInManager<CCustomUser> SignInManager)
		{
			MSignInManager=SignInManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION METHOD vykonava LOGIN na zaklade dat, ktore zasle CLIENT ako PARAMETER.
		[HttpPost]
		public async Task<IActionResult> LoginAsync([FromBody] CLogin Login)
		{
			Microsoft.AspNetCore.Identity.SignInResult			SignInResult=await MSignInManager.PasswordSignInAsync(Login.UserName,Login.Password,false,false);

			if (SignInResult.Succeeded==true)
			{
				IActionResult									Result=Ok();

				return(Result);
			}
			else
			{
				IActionResult									Result=Unauthorized();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION METHOD vykonava LOGOUT.
		[HttpPost]
		public async Task<IActionResult> LogoutAsync()
		{
			await MSignInManager.SignOutAsync();

			IActionResult										Result=Ok();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------