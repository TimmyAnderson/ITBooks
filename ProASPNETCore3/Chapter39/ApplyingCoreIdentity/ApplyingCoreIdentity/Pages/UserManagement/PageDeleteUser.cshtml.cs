using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using ApplyingCoreIdentity.Model;
using ApplyingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageDeleteUserModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [UserManager<TUserType>] umoznuje pristup k USERS, ktori su ulozeni v DB.
		private readonly UserManager<CCustomUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
		private CUserDelete										MUserDelete;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageDeleteUserModel(UserManager<CCustomUser> UserManager)
		{
			MUserManager=UserManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CUserDelete										UserDelete
		{
			get
			{
				return(MUserDelete);
			}
			set
			{
				MUserDelete=value;
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
				MUserDelete=new CUserDelete(CustomUser.Id,CustomUser.UserName,CustomUser.Email,CustomUser.Description);

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
		public async Task<IActionResult> OnPostAsync(string ID)
		{
			if (ModelState.IsValid==true)
			{
				CCustomUser										CustomUser=await MUserManager.FindByIdAsync(ID);

				if (CustomUser!=null)
				{
					// !!! Vykona sa DELETE USER z DB.
					IdentityResult								IdentityResult=await MUserManager.DeleteAsync(CustomUser);

					if (IdentityResult.Succeeded==true)
					{
						IActionResult							ResultSuccess=RedirectToPage("PageViewUsers");

						return(ResultSuccess);
					}
					else
					{
						// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o DELETE USER.
						foreach(IdentityError Error in IdentityResult.Errors)
						{
							ModelState.AddModelError("",Error.Description);
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