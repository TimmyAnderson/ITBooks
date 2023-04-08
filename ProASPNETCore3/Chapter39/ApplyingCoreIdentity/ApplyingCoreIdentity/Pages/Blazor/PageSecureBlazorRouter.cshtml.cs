using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using ApplyingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Pages
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! RAZOR PAGE obsahuje ROUTER BLAZOR COMPONENT.
	// !!!!! RAZOR PAGE, ktora sa pouziva na zobrazenie BLAZOR COMPONENTS MUSI byt oznacena ATTRIBUTE [AuthorizeAttribute].
	[Authorize]
    public class PageAllowAuthorizedContentModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly SignInManager<CCustomUser>				MSignInManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageAllowAuthorizedContentModel(SignInManager<CCustomUser> SignInManager)
		{
			MSignInManager=SignInManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnGet()
		{
			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetLogoutAsync()
		{
			await MSignInManager.SignOutAsync();

			IActionResult										Result=RedirectToAction("Index","Home");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------