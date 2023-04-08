using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authentication;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Security
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CLASS pridava CUSTOM CLAIMS do CLAIMS PRINCIPAL.
	public sealed class CCustomClaimsTransformation : IClaimsTransformation
	{
//----------------------------------------------------------------------------------------------------------------------
		public Task<ClaimsPrincipal> TransformAsync(ClaimsPrincipal Principal)
		{
			if (Principal!=null)
			{
				ClaimsIdentity									TypedIdentity=Principal.Identity as ClaimsIdentity;

				if (TypedIdentity!=null)
				{
					if (TypedIdentity.IsAuthenticated==true)
					{
						Claim									CustomClaim=new Claim("MY CUSTOM NAME from CLAIMS TRANSFORMATION",TypedIdentity.Name.ToUpper(),ClaimValueTypes.String,"CLAIMS TRANSFORMATION","ORIGINAL CLAIMS TRANSFORMATION");
						
						// !!! Prida sa CUSTOM CLAIM.
						TypedIdentity.AddClaim(CustomClaim);
					}
				}
			}

			return(Task.FromResult(Principal));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------