using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using SecuringWebServicesBearerTokens.Model;
using SecuringWebServicesBearerTokens.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageAddUserModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [UserManager<TUserType>] umoznuje pristup k USERS, ktori su ulozeni v DB.
		private readonly UserManager<CCustomUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
		private CUserAdd										MUserAdd;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageAddUserModel(UserManager<CCustomUser> UserManager)
		{
			MUserManager=UserManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CUserAdd											UserAdd
		{
			get
			{
				return(MUserAdd);
			}
			set
			{
				MUserAdd=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnGet()
		{
			MUserAdd=new CUserAdd();

			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnPostAsync()
		{
			if (ModelState.IsValid==true)
			{
				CCustomUser										CustomUser=new CCustomUser();

				CustomUser.UserName=UserAdd.UserName;
				CustomUser.Email=UserAdd.Email;
				CustomUser.Description=UserAdd.Description;

				// !!! Novy USER sa ULOZI do DB.
				IdentityResult									IdentityResult=await MUserManager.CreateAsync(CustomUser,UserAdd.Password);

				if (IdentityResult.Succeeded==true)
				{
					Claim										CustomClaim=new Claim("MY CUSTOM DESCRIPTION from DB",CustomUser.Description,ClaimValueTypes.String,"IDENTITY DB","ORIGINAL IDENTITY DB");
					IdentityResult								AddClaimResult=await MUserManager.AddClaimAsync(CustomUser,CustomClaim);

					if (AddClaimResult.Succeeded==true)
					{
						IActionResult							Result=RedirectToPage("PageViewUsers");

						return(Result);
					}
					else
					{
						// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o pridanie CLAIM k danemu USER.
						foreach(IdentityError Error in AddClaimResult.Errors)
						{
							ModelState.AddModelError("",Error.Description);
						}

						// !!! Odstrani sa USER.
						await MUserManager.DeleteAsync(CustomUser);

						IActionResult							Result=Page();

						return(Result);
					}
				}
				else
				{
					// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o vytvorenie USER.
					foreach(IdentityError Error in IdentityResult.Errors)
					{
						ModelState.AddModelError("",Error.Description);
					}

					IActionResult								Result=Page();

					return(Result);
				}
			}
			else
			{
				IActionResult									Result=Page();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------