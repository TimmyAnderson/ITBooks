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
	// !!! RAZOR PAGE je pristupna iba pre ROLE 'Users'.
	[Authorize(Roles="Users")]
    public class ShowUserAndRolesForUsersModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly UserManager<CCustomUser>				MUserManager;
		private readonly RoleManager<CCustomRole>				MRoleManager;
		private readonly SignInManager<CCustomUser>				MSignInManager;
//----------------------------------------------------------------------------------------------------------------------
		private CAuthenticationUser								MAuthenticationUser;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ShowUserAndRolesForUsersModel(UserManager<CCustomUser> UserManager, RoleManager<CCustomRole> RoleManager, SignInManager<CCustomUser> SignInManager)
		{
			MUserManager=UserManager;
			MRoleManager=RoleManager;
			MSignInManager=SignInManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CAuthenticationUser								AuthenticationUser
		{
			get
			{
				return(MAuthenticationUser);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetAsync()
        {
			string												ErrorMessage;

			if (User!=null)
			{
				if (User.Identity.IsAuthenticated==true)
				{
					CCustomUser									CustomUser=await MUserManager.GetUserAsync(User);

					if (CustomUser!=null)
					{
						CCustomRole[]							CustomRoles=MRoleManager.Roles.OrderBy(P => P.Name).ToArray();
						List<CAuthenticationRole>				AuthenticationRoles=new List<CAuthenticationRole>();
						
						foreach(CCustomRole CustomRole in CustomRoles)
						{
							if (await MUserManager.IsInRoleAsync(CustomUser,CustomRole.Name)==true)
							{
								AuthenticationRoles.Add(new CAuthenticationRole(CustomRole.Id,CustomRole.Name,CustomRole.Description));
							}
						}

						MAuthenticationUser=new CAuthenticationUser(CustomUser.Id,CustomUser.UserName,CustomUser.Description,AuthenticationRoles.ToArray(),User.Claims.ToArray());

						IActionResult							Result=Page();

						return(Result);
					}
					else
					{
						ErrorMessage="User not FOUND !";
					}
				}
				else
				{
					ErrorMessage="User is UNAUTHENTICATED !";
				}
			}
			else
			{
				ErrorMessage="User doesn't EXIST !";
			}

			IActionResult										AuthenticationErrorResult=RedirectToPage("AuthenticationError",new {AuthenticationError=ErrorMessage});

			return(AuthenticationErrorResult);
        }
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetPerformLogoutAsync()
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