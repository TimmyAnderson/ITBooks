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
    public class PageAddRoleModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [RoleManager<TRoleType>] umoznuje pristup k ROLES, ktori su ulozeni v DB.
		private readonly RoleManager<CCustomRole>				MRoleManager;
//----------------------------------------------------------------------------------------------------------------------
		private CRoleAdd										MRoleAdd;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageAddRoleModel(RoleManager<CCustomRole> RoleManager)
		{
			MRoleManager=RoleManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CRoleAdd											RoleAdd
		{
			get
			{
				return(MRoleAdd);
			}
			set
			{
				MRoleAdd=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnGet()
		{
			MRoleAdd=new CRoleAdd();

			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnPostAsync()
		{
			if (ModelState.IsValid==true)
			{
				CCustomRole										CustomRole=new CCustomRole();

				CustomRole.Name=RoleAdd.RoleName;
				CustomRole.Description=RoleAdd.Description;

				// !!! Novy ROLE sa ULOZI do DB.
				IdentityResult									IdentityResult=await MRoleManager.CreateAsync(CustomRole);

				if (IdentityResult.Succeeded==true)
				{
					IActionResult								Result=RedirectToPage("PageViewRoles");

					return(Result);
				}
				else
				{
					// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o vytvorenie ROLE.
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