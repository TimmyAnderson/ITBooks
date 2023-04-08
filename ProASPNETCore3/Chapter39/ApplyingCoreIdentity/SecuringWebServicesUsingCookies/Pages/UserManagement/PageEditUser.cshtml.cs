using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using SecuringWebServicesUsingCookies.Model;
using SecuringWebServicesUsingCookies.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesUsingCookies.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageEditUserModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [UserManager<TUserType>] umoznuje pristup k USERS, ktori su ulozeni v DB.
		private readonly UserManager<CCustomUser>				MUserManager;
		private readonly IUserValidator<CCustomUser>			MUserValidator;
		private readonly IPasswordValidator<CCustomUser>		MPasswordValidator;
		private readonly IPasswordHasher<CCustomUser>			MPasswordHasher;
//----------------------------------------------------------------------------------------------------------------------
		private CUserEdit										MUserEdit;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageEditUserModel(UserManager<CCustomUser> UserManager, IUserValidator<CCustomUser> UserValidator, IPasswordValidator<CCustomUser> PasswordValidator, IPasswordHasher<CCustomUser> PasswordHasher)
		{
			MUserManager=UserManager;
			MUserValidator=UserValidator;
			MPasswordValidator=PasswordValidator;
			MPasswordHasher=PasswordHasher;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CUserEdit										UserEdit
		{
			get
			{
				return(MUserEdit);
			}
			set
			{
				MUserEdit=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetAsync(string ID)
		{
			CCustomUser											CustomUser=await MUserManager.FindByIdAsync(ID);

			if (CustomUser!=null)
			{
				MUserEdit=new CUserEdit(CustomUser.Id,CustomUser.UserName,CustomUser.Email,"",CustomUser.Description);

				IActionResult									Result=Page();

				return(Result);
			}
			else
			{
				IActionResult									Result=RedirectToPage("PageViewUsers");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnPostAsync()
		{
			if (ModelState.IsValid==true)
			{
				CCustomUser										CustomUser=await MUserManager.FindByIdAsync(UserEdit.ID);

				if (CustomUser!=null)
				{
					CustomUser.Email=UserEdit.Email;
					CustomUser.Description=UserEdit.Description;

					// !!! Vykona sa USER VALIDATION.
					IdentityResult								ResultValidUser=await MUserValidator.ValidateAsync(MUserManager,CustomUser);

					if (ResultValidUser.Succeeded==false)
					{
						// !!! Pridaju sa ERRORS, ku ktorym doslo pri USER VALIDATION.
						foreach(IdentityError Error in ResultValidUser.Errors)
						{
							ModelState.AddModelError("",Error.Description);
						}
					}

					if (string.IsNullOrEmpty(UserEdit.Password)==true)
					{
						ModelState.AddModelError("","PASSWORD is EMPTY !");
					}
					else
					{
						// !!! Vykona sa PASSWORD VALIDATION.
						IdentityResult							ResultValidPassword=await MPasswordValidator.ValidateAsync(MUserManager,CustomUser,UserEdit.Password);

						if (ResultValidPassword.Succeeded==true)
						{
							// !!! Vypocita sa HASH daneho PASSWORD.
							CustomUser.PasswordHash=MPasswordHasher.HashPassword(CustomUser,UserEdit.Password);

							// !!!!! UPDATE PASSWORD je mozne vykonat aj volanim METHOD [MUserManager.RemovePasswordAsync(CustomUser)] a naslednym volanim METHOD [MUserManager.AddPasswordAsync(CustomUser,UserUpdate.Password)].
						}
						else
						{
							// !!! Pridaju sa ERRORS, ku ktorym doslo pri USER VALIDATION.
							foreach(IdentityError Error in ResultValidPassword.Errors)
							{
								ModelState.AddModelError("",Error.Description);
							}
						}
					}

					if (ModelState.ErrorCount==0)
					{
						// !!! Vykona sa UPDATE USER v DB.
						IdentityResult							IdentityResult=await MUserManager.UpdateAsync(CustomUser);

						if (IdentityResult.Succeeded==true)
						{
							IActionResult						ResultSuccess=RedirectToPage("PageViewUsers");

							return(ResultSuccess);
						}
						else
						{
							// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o UPDATE USER.
							foreach(IdentityError Error in IdentityResult.Errors)
							{
								ModelState.AddModelError("",Error.Description);
							}
						}
					}
				}
				else
				{
					ModelState.AddModelError("","USER not FOUND !");
				}
			}

			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------