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
    public class PageEditRoleModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [RoleManager<TRoleType>] umoznuje pristup k ROLES, ktori su ulozeni v DB.
		private readonly RoleManager<CCustomRole>				MRoleManager;
//----------------------------------------------------------------------------------------------------------------------
		private CRoleEdit										MRoleEdit;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageEditRoleModel(RoleManager<CCustomRole> RoleManager)
		{
			MRoleManager=RoleManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CRoleEdit										RoleEdit
		{
			get
			{
				return(MRoleEdit);
			}
			set
			{
				MRoleEdit=value;
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
				MRoleEdit=new CRoleEdit(CustomRole.Id,CustomRole.Name,CustomRole.Description);

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
		public async Task<IActionResult> OnPostAsync()
		{
			if (ModelState.IsValid==true)
			{
				CCustomRole										CustomRole=await MRoleManager.FindByIdAsync(RoleEdit.ID);

				if (CustomRole!=null)
				{
					CustomRole.Description=RoleEdit.Description;

					// !!! Vykona sa UPDATE ROLE v DB.
					IdentityResult								IdentityResult=await MRoleManager.UpdateAsync(CustomRole);

					if (IdentityResult.Succeeded==true)
					{
						IActionResult							ResultSuccess=RedirectToPage("PageViewRoles");

						return(ResultSuccess);
					}
					else
					{
						// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o UPDATE ROLE.
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