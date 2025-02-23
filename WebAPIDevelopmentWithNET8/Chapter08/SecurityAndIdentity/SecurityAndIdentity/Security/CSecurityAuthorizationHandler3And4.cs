using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ASP.NET CORE vola pre kazdy REQUIREMENT VSETKY AUTHORIZATION HANDLERS pricom NEROZLISUJE ci dany AUTHORIZATION HANDLER je vobec schopny spracovat dany REQUIREMENT. AUTHORIZATION uspeje, ak VSETKY REQUIREMENTS su SPLNENE, bez ohladu na to, ktory HANDLER ich splnil.
	public sealed class CSecurityAuthorizationHandler3And4 : IAuthorizationHandler
	{
//----------------------------------------------------------------------------------------------------------------------
	    public Task HandleAsync(AuthorizationHandlerContext Context)
		{
			IAuthorizationRequirement[]							PendingRequirements=Context.PendingRequirements.ToArray();

			foreach(IAuthorizationRequirement AuthorizationRequirement in PendingRequirements)
			{
				if ((AuthorizationRequirement is CSecurityAuthorizationRequirement3)==true)
				{
					CSecurityAuthorizationRequirement3			TypedAuthorizationRequirement=(CSecurityAuthorizationRequirement3) AuthorizationRequirement;
					bool										HasClaim=Context.User.HasClaim(P => P.Type==CSecurityClaims.MY_CLAIM_1 && P.Value.StartsWith(TypedAuthorizationRequirement.ClaimsStartsWith)==true);

					if (HasClaim==true)
					{
						Context.Succeed(TypedAuthorizationRequirement);
					}
				}
				else if ((AuthorizationRequirement is CSecurityAuthorizationRequirement4)==true)
				{
					CSecurityAuthorizationRequirement4			TypedAuthorizationRequirement=(CSecurityAuthorizationRequirement4) AuthorizationRequirement;
					bool										HasClaim=Context.User.HasClaim(P => P.Type==CSecurityClaims.MY_CLAIM_2 && P.Value.EndsWith(TypedAuthorizationRequirement.ClaimsEndsWith)==true);

					if (HasClaim==true)
					{
						Context.Succeed(TypedAuthorizationRequirement);
					}
				}
			}

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------