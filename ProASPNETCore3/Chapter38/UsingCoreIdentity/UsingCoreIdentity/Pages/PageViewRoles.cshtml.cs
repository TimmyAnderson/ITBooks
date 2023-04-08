using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using UsingCoreIdentity.Model;
using UsingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingCoreIdentity.Pages
{
//----------------------------------------------------------------------------------------------------------------------
    public class PageViewRolesModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [RoleManager<TRoleType>] umoznuje pristup k ROLES, ktori su ulozeni v DB.
		private readonly RoleManager<CCustomRole>				MRoleManager;
		// !!! CLASS [UserManager<TUserType>] umoznuje pristup k USERS, ktori su ulozeni v DB.
		private readonly UserManager<CCustomUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
		private CRole[]											MRoles;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageViewRolesModel(RoleManager<CCustomRole> RoleManager, UserManager<CCustomUser> UserManager)
		{
			MRoleManager=RoleManager;
			MUserManager=UserManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CRole[]											Roles
		{
			get
			{
				return(MRoles);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetAsync()
		{
			List<CRole>											Roles=new List<CRole>();

			foreach(CCustomRole CustomRole in MRoleManager.Roles)
			{
				IList<CCustomUser>								UsersInRole=await MUserManager.GetUsersInRoleAsync(CustomRole.Name);
				StringBuilder									Users=new StringBuilder();

				Users.Append("[");

				for(int Index=0;Index<UsersInRole.Count;Index++)
				{
					if (Index>0)
					{
						Users.Append(" ");
					}

					Users.Append(UsersInRole[Index]);
				}

				Users.Append("]");

				Roles.Add(new CRole(CustomRole.Id,CustomRole.Name,CustomRole.Description,Users.ToString()));
			}

			MRoles=Roles.ToArray();

			IActionResult										Result=Page();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------