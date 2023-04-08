using System;
using System.Collections.Generic;
using System.Linq;
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
    public class PageDeleteRoleModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [RoleManager<TRoleType>] umoznuje pristup k ROLES, ktori su ulozeni v DB.
		private readonly RoleManager<CCustomRole>				MRoleManager;
		// !!! CLASS [UserManager<TUserType>] umoznuje pristup k USERS, ktori su ulozeni v DB.
		private readonly UserManager<CCustomUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
		private CRoleDelete										MRoleDelete;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageDeleteRoleModel(RoleManager<CCustomRole> RoleManager, UserManager<CCustomUser> UserManager)
		{
			MRoleManager=RoleManager;
			MUserManager=UserManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CRoleDelete										RoleDelete
		{
			get
			{
				return(MRoleDelete);
			}
			set
			{
				MRoleDelete=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetAsync(string ID)
		{
			CCustomRole											CustomRole=await MRoleManager.FindByIdAsync(ID);

			if (CustomRole!=null)
			{
				MRoleDelete=new CRoleDelete(CustomRole.Id,CustomRole.Name,CustomRole.Description);

				IActionResult									Result=Page();

				return(Result);
			}
			else
			{
				IActionResult									Result=RedirectToPage("PageViewRoles");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnPostAsync(string ID)
		{
			if (ModelState.IsValid==true)
			{
				CCustomRole										CustomRole=await MRoleManager.FindByIdAsync(ID);

				if (CustomRole!=null)
				{
					IList<CCustomUser>							UsersInRole=await MUserManager.GetUsersInRoleAsync(CustomRole.Name);
					
					foreach(CCustomUser CustomUser in UsersInRole)
					{
						// !!! USER sa odstrani z ROLE.
						await MUserManager.RemoveFromRoleAsync(CustomUser,CustomRole.Name);
					}

					// !!! Vykona sa DELETE ROLE z DB.
					IdentityResult								IdentityResult=await MRoleManager.DeleteAsync(CustomRole);

					if (IdentityResult.Succeeded==true)
					{
						IActionResult							ResultSuccess=RedirectToPage("PageViewRoles");

						return(ResultSuccess);
					}
					else
					{
						// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o DELETE ROLE.
						foreach(IdentityError Error in IdentityResult.Errors)
						{
							ModelState.AddModelError("",Error.Description);
						}
					}
				}
				else
				{
					ModelState.AddModelError("","ROLE not FOUND !");
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