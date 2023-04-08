using System;
using System.Collections.Generic;
using System.Linq;
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
    public class PageAddRemoveUsersToRoleModel : PageModel
    {
//----------------------------------------------------------------------------------------------------------------------
		// !!! CLASS [RoleManager<TRoleType>] umoznuje pristup k ROLES, ktori su ulozeni v DB.
		private readonly RoleManager<CCustomRole>				MRoleManager;
		// !!! CLASS [UserManager<TUserType>] umoznuje pristup k USERS, ktori su ulozeni v DB.
		private readonly UserManager<CCustomUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
		private CAddRemoveUserToRoleModel						MAddRemoveUserToRoleModel;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PageAddRemoveUsersToRoleModel(RoleManager<CCustomRole> RoleManager, UserManager<CCustomUser> UserManager)
		{
			MRoleManager=RoleManager;
			MUserManager=UserManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[BindProperty]
		public CAddRemoveUserToRoleModel						AddRemoveUserToRoleModel
		{
			get
			{
				return(MAddRemoveUserToRoleModel);
			}
			set
			{
				MAddRemoveUserToRoleModel=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private async Task UpdateModel(string RoleID)
		{
			CCustomRole											CustomRole=await MRoleManager.FindByIdAsync(RoleID);

			if (CustomRole!=null)
			{
				string											RoleName=CustomRole.Name;
				CCustomUser[]									AllUsers=MUserManager.Users.OrderBy(P => P.UserName).ToArray();
				IList<CCustomUser>								UsersInRoleFromDB=await MUserManager.GetUsersInRoleAsync(CustomRole.Name);
				CAddRemoveUserToRole[]							UsersInRole=UsersInRoleFromDB.Select(P => new CAddRemoveUserToRole(RoleID,P.Id,P.UserName)).OrderBy(P => P.UserName).ToArray();
				List<CAddRemoveUserToRole>						UsersNotInRoleCollection=new List<CAddRemoveUserToRole>();

				foreach(CCustomUser User in AllUsers)
				{
					bool										IsUserInRole=false;

					foreach(CCustomUser UserInRole in UsersInRoleFromDB)
					{
						if (User.Id==UserInRole.Id)
						{
							IsUserInRole=true;
							break;
						}
					}

					if (IsUserInRole==false)
					{
						UsersNotInRoleCollection.Add(new CAddRemoveUserToRole(RoleID,User.Id,User.UserName));
					}
				}

				CAddRemoveUserToRole[]							UsersNotInRole=UsersNotInRoleCollection.ToArray();

				MAddRemoveUserToRoleModel=new CAddRemoveUserToRoleModel(RoleID,RoleName,UsersInRole,UsersNotInRole);
			}
			else
			{
				MAddRemoveUserToRoleModel=new CAddRemoveUserToRoleModel(RoleID,"",new CAddRemoveUserToRole[0],new CAddRemoveUserToRole[0]);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task<IActionResult> OnGetAsync(string RoleID)
		{
			CCustomRole											CustomRole=await MRoleManager.FindByIdAsync(RoleID);

			if (CustomRole!=null)
			{
				await UpdateModel(RoleID);

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
		public async Task<IActionResult> OnPostAsync(CAddRemoveUserToRoleModel AddRemoveUserToRoleModel, string UserID, string RoleID, bool AddUser)
		{
			CCustomUser											CustomUser=await MUserManager.FindByIdAsync(UserID);
			CCustomRole											CustomRole=await MRoleManager.FindByIdAsync(RoleID);

			if (CustomUser!=null && CustomRole!=null)
			{
				if (AddUser==true)
				{
					// !!! USER sa prida do ROLE.
					IdentityResult								IdentityResult=await MUserManager.AddToRoleAsync(CustomUser,CustomRole.Name);

					if (IdentityResult.Succeeded==true)
					{
						IActionResult							Result=RedirectToPage("PageViewRoles");

						return(Result);
					}
					else
					{
						// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o pridanie USER do ROLE.
						foreach(IdentityError Error in IdentityResult.Errors)
						{
							ModelState.AddModelError("",Error.Description);
						}

						await UpdateModel(RoleID);

						IActionResult							Result=Page();

						return(Result);
					}
				}
				else
				{
					// !!! USER sa odstrani z ROLE.
					IdentityResult								IdentityResult=await MUserManager.RemoveFromRoleAsync(CustomUser,CustomRole.Name);

					if (IdentityResult.Succeeded==true)
					{
						IActionResult							Result=RedirectToPage("PageViewRoles");

						return(Result);
					}
					else
					{
						// !!! Pridaju sa ERRORS, ku ktorym doslo pri pokuse o odstranenie USER z ROLE.
						foreach(IdentityError Error in IdentityResult.Errors)
						{
							ModelState.AddModelError("",Error.Description);
						}

						await UpdateModel(RoleID);

						IActionResult							Result=Page();

						return(Result);
					}
				}
			}
			else
			{
				IActionResult									Result=RedirectToPage("PageViewRoles");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------