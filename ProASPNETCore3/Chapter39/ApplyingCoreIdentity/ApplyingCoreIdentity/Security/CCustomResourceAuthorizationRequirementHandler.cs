using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using ApplyingCoreIdentity.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity.Security
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CLASS kontroluje ci ma USER pristup k RESOURCE TYPE 'CProtectedResource'.
	public sealed class CCustomResourceAuthorizationRequirementHandler : AuthorizationHandler<CCustomResourceAuthorizationRequirement>
	{
//----------------------------------------------------------------------------------------------------------------------
		protected override Task HandleRequirementAsync(AuthorizationHandlerContext Context, CCustomResourceAuthorizationRequirement Requirement)
		{
			if (Requirement.AllowAll==true)
			{
				Context.Succeed(Requirement);

				return(Task.CompletedTask);
			}

			if (Context.User!=null)
			{
				if (Context.User.Identity!=null)
				{
					if (Context.User.Identity.IsAuthenticated==true)
					{
						CProtectedResource						ProtectedResource=Context.Resource as CProtectedResource;

						if (ProtectedResource!=null)
						{
							if (ProtectedResource.Owner==Context.User.Identity.Name)
							{
								Context.Succeed(Requirement);

								return(Task.CompletedTask);
							}
						}
					}
				}
			}

			Context.Fail();

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------