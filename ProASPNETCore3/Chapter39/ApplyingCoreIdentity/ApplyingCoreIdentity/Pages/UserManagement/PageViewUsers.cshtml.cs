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
    public class PageViewUsersModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [UserManager<TUserType>] umoznuje pristup k USERS, ktori su ulozeni v DB.
		private readonly UserManager<CCustomUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
		private CUser[]											MUsers;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageViewUsersModel(UserManager<CCustomUser> UserManager)
		{
			MUserManager=UserManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CUser[]											Users
		{
			get
			{
				return(MUsers);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult OnGet()
		{
			MUsers=MUserManager.Users.Select(P => new CUser(P.Id,P.UserName,P.Email,P.Description)).ToArray();

			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------