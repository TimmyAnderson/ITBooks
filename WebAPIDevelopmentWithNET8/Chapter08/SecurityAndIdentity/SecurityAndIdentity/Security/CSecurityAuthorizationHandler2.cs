using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ASP.NET CORE vola pre kazdy REQUIREMENT VSETKY AUTHORIZATION HANDLERS pricom NEROZLISUJE ci dany AUTHORIZATION HANDLER je vobec schopny spracovat dany REQUIREMENT. AUTHORIZATION uspeje, ak VSETKY REQUIREMENTS su SPLNENE, bez ohladu na to, ktory HANDLER ich splnil.
	public sealed class CSecurityAuthorizationHandler2 : AuthorizationHandler<CSecurityAuthorizationRequirement2>
	{
//----------------------------------------------------------------------------------------------------------------------
	    protected override Task HandleRequirementAsync(AuthorizationHandlerContext Context, CSecurityAuthorizationRequirement2 Requirement)
		{
			bool												HasClaim=Context.User.HasClaim(P => P.Type==CSecurityClaims.MY_CLAIM_2 && P.Value.EndsWith(Requirement.ClaimsEndsWith)==true);

			if (HasClaim==true)
			{
				Context.Succeed(Requirement);
			}

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------