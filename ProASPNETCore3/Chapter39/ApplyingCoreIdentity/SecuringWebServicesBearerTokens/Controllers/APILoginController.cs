using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;
using Microsoft.IdentityModel.Tokens;
using SecuringWebServicesBearerTokens.Model;
using SecuringWebServicesBearerTokens.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER poskytuje pre WEB SERVICE CLIENT ACTION METHODS na vykonanie LOGIN a LOGOUT.
	[ApiController]
	[Route("api/{Controller}/{Action}")]
	public class APILoginController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly UserManager<CCustomUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public APILoginController(UserManager<CCustomUser> UserManager)
		{
			MUserManager=UserManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private async Task<bool> CheckPassword(CLogin Login)
		{
			CCustomUser											User=await MUserManager.FindByNameAsync(Login.UserName);

			if (User!=null)
			{
				// !!! Vykona sa PASSWORD VALIDATION voci vsetkym PASSWORD VALIDATORS. Ak niektory uspeje, VALIDATION je povazovana za USPESNU.
				foreach (IPasswordValidator<CCustomUser> PasswordValidator in MUserManager.PasswordValidators)
				{
					IdentityResult								Result=await PasswordValidator.ValidateAsync(MUserManager,User,Login.Password);

					if (Result.Succeeded==true)
					{
						return(true);
					}
				}
			}

			return(false);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION METHOD vykonava funkcionalitu LOGIN. V RETURN VALUE vracia JWT TOKEN, ktory moze CLIENT pouzit pri BEARER TOKEN AUTHENTICATION.
		[HttpPost]
		public async Task<IActionResult> Login([FromBody] CLogin Login)
		{
			bool												PasswordValidated=await CheckPassword(Login);

			if (PasswordValidated==true)
			{
				// !!! JWT TOKEN HANDLER sluzi na vytvaranie JWT TOKENS.
				JwtSecurityTokenHandler							TokenHandler=new JwtSecurityTokenHandler();
				// !!! SECURITY KEY je SERIALIZED.
				byte[]											Secret=Encoding.ASCII.GetBytes(Startup.JWT_SECRET);
				// !!! Vytvori sa SYMMETRIC SECURITY KEY zo SECURITY KEY.
				SymmetricSecurityKey							Key=new SymmetricSecurityKey(Secret);
				ClaimsIdentity									Identity=new ClaimsIdentity(new Claim[]{new Claim(ClaimTypes.Name,Login.UserName)});
				SecurityTokenDescriptor							TokenDescriptor=new SecurityTokenDescriptor();

				TokenDescriptor.Subject=Identity;
				TokenDescriptor.Expires=DateTime.UtcNow.AddHours(24);
				TokenDescriptor.SigningCredentials=new SigningCredentials(Key,SecurityAlgorithms.HmacSha256Signature);

				// !!! Vytvori sa JWT TOKEN.
				SecurityToken									Token=TokenHandler.CreateToken(TokenDescriptor);
				// !!! Do STRING sa zapise TOKEN VALUE.
				string											TokenValue=TokenHandler.WriteToken(Token);
				CLoginResult									LoginResult=new CLoginResult(true,TokenValue);
				IActionResult									Result=Ok(LoginResult);

				return(Result);
			}
			else
			{
				IActionResult									Result=Unauthorized();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------