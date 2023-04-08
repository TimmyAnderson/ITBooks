using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Security
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS implementuje CUSTOM AUTHORIZATION REQUIREMENT HANDLER, ktory povoluje iba USERS s danym NAME.
	public sealed class CCustomAuthorizationRequirementHandler : AuthorizationHandler<CCustomAuthorizationRequirement>
	{
//----------------------------------------------------------------------------------------------------------------------
		protected override Task HandleRequirementAsync(AuthorizationHandlerContext Context, CCustomAuthorizationRequirement Requirement)
		{
			if (Context.User!=null)
			{
				if (Context.User.Identity!=null)
				{
					if (Context.User.Identity.Name!=null)
					{
						bool									IsAllowedUser=Requirement.AllowedUsers.Contains(Context.User.Identity.Name);

						if (IsAllowedUser==true)
						{
							Context.Succeed(Requirement);
						}
						else
						{
							Context.Fail();
						}
					}
					else
					{
						Context.Fail();
					}
				}
				else
				{
					Context.Fail();
				}
			}
			else
			{
				Context.Fail();
			}

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------