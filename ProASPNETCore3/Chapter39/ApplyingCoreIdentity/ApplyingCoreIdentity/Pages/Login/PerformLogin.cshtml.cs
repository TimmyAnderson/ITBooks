using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using ApplyingCoreIdentity.Model;
using ApplyingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PerformLoginModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly UserManager<CCustomUser>				MUserManager;
		private readonly SignInManager<CCustomUser>				MSignInManager;
//----------------------------------------------------------------------------------------------------------------------
		private CLogin											MLogin;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PerformLoginModel(UserManager<CCustomUser> UserManager, SignInManager<CCustomUser> SignInManager)
		{
			MUserManager=UserManager;
			MSignInManager=SignInManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CLogin											Login
		{
			get
			{
				return(MLogin);
			}
			set
			{
				MLogin=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnGet(string ReturnURL)
        {
			MLogin=new CLogin(null,null,ReturnURL);

			IActionResult										Result=Page();

			return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnPostAsync()
		{
			if (ModelState.IsValid==true)
			{
				CCustomUser										User=await MUserManager.FindByNameAsync(Login.UserName);

				if (User!=null)
				{
					// !!! Vykona sa LOGOUT, ak bol USER uz prihlaseny.
					await MSignInManager.SignOutAsync();

					// !!! Vykona sa LOGIN.
					Microsoft.AspNetCore.Identity.SignInResult	SignInResult=await MSignInManager.PasswordSignInAsync(User,Login.Password,false,false);

					if (SignInResult.Succeeded==true)
					{
						// !!! Vykona sa REDIRECT na RETURN URL.
						IActionResult							SuccessResult=Redirect(MLogin.ReturnURL);

						return(SuccessResult);
					}
					else
					{
						ModelState.AddModelError("","LOGIN FAILED !");
					}
				}
				else
				{
					ModelState.AddModelError("","User NOT FOUND !");
				}
			}

			// !!! Ak neboli zadane vsetky VALUES, zobrazi sa znova ten isty PAGE s ERROR MESSAGES.
			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
    }
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------