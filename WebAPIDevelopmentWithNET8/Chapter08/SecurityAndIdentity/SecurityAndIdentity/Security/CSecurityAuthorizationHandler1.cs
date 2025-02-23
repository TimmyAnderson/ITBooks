using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! ASP.NET CORE vola pre kazdy REQUIREMENT VSETKY AUTHORIZATION HANDLERS pricom NEROZLISUJE ci dany AUTHORIZATION HANDLER je vobec schopny spracovat dany REQUIREMENT. AUTHORIZATION uspeje, ak VSETKY REQUIREMENTS su SPLNENE, bez ohladu na to, ktory HANDLER ich splnil.
	public sealed class CSecurityAuthorizationHandler1 : AuthorizationHandler<CSecurityAuthorizationRequirement1>
	{
//----------------------------------------------------------------------------------------------------------------------
	    protected override Task HandleRequirementAsync(AuthorizationHandlerContext Context, CSecurityAuthorizationRequirement1 Requirement)
		{
			bool												HasClaim=Context.User.HasClaim(P => P.Type==CSecurityClaims.MY_CLAIM_1 && P.Value.StartsWith(Requirement.ClaimsStartsWith)==true);

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