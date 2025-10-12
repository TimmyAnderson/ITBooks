using System.Collections.Generic;
using System.Security.Claims;
using System.Text.Encodings.Web;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authentication;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using Microsoft.Extensions.Primitives;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CAuthenticationHandlerTest : AuthenticationHandler<CAuthenticationHandlerTestOptions>
	{
//----------------------------------------------------------------------------------------------------------------------
		public const string										AUTHENTICATION_SCHEME="TestScheme";
//----------------------------------------------------------------------------------------------------------------------
		public const string										HEADER_CLAIM_USER_NAME="UserName";
		public const string										HEADER_CLAIM_ROLE_1="RoleClaim1";
		public const string										HEADER_CLAIM_ROLE_2="RoleClaim2";
		public const string										HEADER_CLAIM_ROLE_3="RoleClaim3";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly string									MDefaultUserName;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CAuthenticationHandlerTest(IOptionsMonitor<CAuthenticationHandlerTestOptions> Options, ILoggerFactory Logger, UrlEncoder Encoder)
			: base(Options,Logger,Encoder)
		{
			MDefaultUserName=Options.CurrentValue.TestUserName;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override Task<AuthenticateResult> HandleAuthenticateAsync()
		{
			List<Claim>											Claims=new List<Claim>();

			StringValues										UserNameClaimValue;
			StringValues										RoleClaim1Value;
			StringValues										RoleClaim2Value;
			StringValues										RoleClaim3Value;

			if (Context.Request.Headers.TryGetValue(HEADER_CLAIM_USER_NAME,out UserNameClaimValue)==true)
			{
				Claim											Claim=new Claim(ClaimTypes.Name,UserNameClaimValue[0]);

				Claims.Add(Claim);
			}
			else
			{
				Claim											Claim=new Claim(ClaimTypes.Name,MDefaultUserName);

				Claims.Add(Claim);
			}

			if (Context.Request.Headers.TryGetValue(HEADER_CLAIM_ROLE_1,out RoleClaim1Value)==true)
			{
				Claim											Claim=new Claim(ClaimTypes.Role,RoleClaim1Value[0]);

				Claims.Add(Claim);
			}

			if (Context.Request.Headers.TryGetValue(HEADER_CLAIM_ROLE_2,out RoleClaim2Value)==true)
			{
				Claim											Claim=new Claim(ClaimTypes.Role,RoleClaim2Value[0]);

				Claims.Add(Claim);
			}

			if (Context.Request.Headers.TryGetValue(HEADER_CLAIM_ROLE_3,out RoleClaim3Value)==true)
			{
				Claim											Claim=new Claim(ClaimTypes.Role,RoleClaim3Value[0]);

				Claims.Add(Claim);
			}

			ClaimsIdentity										Identity=new ClaimsIdentity(Claims,AUTHENTICATION_SCHEME);
			ClaimsPrincipal										Principal=new ClaimsPrincipal(Identity);
			AuthenticationTicket								Ticket=new AuthenticationTicket(Principal,AUTHENTICATION_SCHEME);
			AuthenticateResult									Result=AuthenticateResult.Success(Ticket);
			Task<AuthenticateResult>							ResultTask=Task.FromResult(Result);

			return(ResultTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------