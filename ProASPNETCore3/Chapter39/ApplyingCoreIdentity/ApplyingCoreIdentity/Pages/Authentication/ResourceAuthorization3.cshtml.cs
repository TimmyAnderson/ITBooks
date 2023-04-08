using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Identity;
using ApplyingCoreIdentity.Model;
using ApplyingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Pages
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! RAZOR PAGE je pristupna pre VSETKYCH AUTHORIZED USERS.
	[Authorize]
    public class ResourceAuthorization3Model : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		private readonly SignInManager<CCustomUser>				MSignInManager;
		private readonly IAuthorizationService					MAuthorizationService;
//----------------------------------------------------------------------------------------------------------------------
		private CProtectedResource								MProtectedResource;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ResourceAuthorization3Model(SignInManager<CCustomUser> SignInManager, IAuthorizationService AuthorizationService)
		{
			MSignInManager=SignInManager;
			MAuthorizationService=AuthorizationService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CProtectedResource								ProtectedResource
		{
			get
			{
				return(MProtectedResource);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetAsync()
        {
			CProtectedResource									ProtectedResource=new CProtectedResource("Jenny","This is DOCUMENT created by JENNY !");

			// !!!!! Vykona sa overenie ci USER ma pristup k danemu RESOURCE pomocou CUSTOM AUTHORIZATION POLICY.
			AuthorizationResult									Authorized=await MAuthorizationService.AuthorizeAsync(User,ProtectedResource,"ResourceAuthorizationPolicyForUser");

			if (Authorized.Succeeded==true)
			{
				MProtectedResource=ProtectedResource;

				IActionResult									Result=Page();

				return(Result);
			}
			else
			{
				IActionResult									Result=RedirectToPage("ResourceAuthorizationError",new {AuthorizationError="USER is NOT AUTHORIZED to ACCESS this RESOURCE !"});

				return(Result);
			}
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