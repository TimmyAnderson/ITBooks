using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using RealApplication5.Models.ViewModels;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication5.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class AccountController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly UserManager<IdentityUser>				MUserManager;
		private readonly SignInManager<IdentityUser>			MSignInManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public AccountController(UserManager<IdentityUser> UserManager, SignInManager<IdentityUser> SignInManager)
		{
			MUserManager=UserManager;
			MSignInManager=SignInManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult Login(string ReturnUrl)
		{
			CLoginModel											Model=new CLoginModel(ReturnUrl);
			ViewResult											Result=View("Login",Model);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		[ValidateAntiForgeryToken]
		public async Task<IActionResult> Login(CLoginModel LoginModel)
		{
			if (ModelState.IsValid==true)
			{
				IdentityUser									User=await MUserManager.FindByNameAsync(LoginModel.Name);

				if (User!=null)
				{
					await MSignInManager.SignOutAsync();

					Microsoft.AspNetCore.Identity.SignInResult	SignInResult=await MSignInManager.PasswordSignInAsync(User,LoginModel.Password,false,false);

					if (SignInResult.Succeeded==true)
					{
						IActionResult							SuccessResult=Redirect(LoginModel?.ReturnUrl ?? "/Admin");

						return(SuccessResult);
					}
				}
			}

			ModelState.AddModelError("", "Invalid name or password !");

			IActionResult										Result=View("Login",LoginModel);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
        [Authorize]
        public async Task<RedirectResult> Logout(string ReturnUrl="/Page1")
		{
            await MSignInManager.SignOutAsync();

			RedirectResult										Result=Redirect(ReturnUrl);

            return(Result);
        }
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------