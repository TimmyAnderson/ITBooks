using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.IdentityModel.Tokens;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingSignalR
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER sluzi na LOGIN.
	[ApiController]
	[Route("[controller]")]
	public class MyAccountController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private static CUserProperties[]						MUsers;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static MyAccountController()
		{
			List<CUserProperties>								UsersCollection=new List<CUserProperties>();

			UsersCollection.Add(new CUserProperties("timmy","aaa",new string[]{"ROLE 1","ROLE 2"}));
			UsersCollection.Add(new CUserProperties("jenny","bbb",new string[]{"ROLE 1","ROLE 2","ROLE 3"}));
			UsersCollection.Add(new CUserProperties("josh","ccc",new string[]{"ROLE 2","ROLE 3"}));
			UsersCollection.Add(new CUserProperties("lucas","ddd",new string[]{"ROLE 1","ROLE 3"}));

			MUsers=UsersCollection.ToArray();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyAccountController(IConfiguration Configuration)
		{
			MConfiguration=Configuration;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vygeneruje sa JWT TOKEN.
		private string GenerateToken(string UserName, string[] Roles)
		{
			string												Secret=MConfiguration["JwtConfig:Secret"];
			string												Issuer=MConfiguration["JwtConfig:ValidIssuer"];
			string												Audience=MConfiguration["JwtConfig:ValidAudiences"];

			if (Secret==null || Issuer==null || Audience==null)
			{
				throw(new InvalidOperationException("JWT is not SET in the CONFIGURATION."));
			}

			SymmetricSecurityKey								SigningKey=new SymmetricSecurityKey(Encoding.UTF8.GetBytes(Secret));
			SecurityTokenDescriptor								TokenDescriptor=new SecurityTokenDescriptor();

			List<Claim>											Claims=new List<Claim>();

			Claims.Add(new Claim(ClaimTypes.Name,UserName));
			Claims.AddRange(Roles.Select(P => new Claim(ClaimTypes.Role,P)));

			// !!! Pridaju sa CUSTOM CLAIMS.
			Claims.Add(new Claim(CSecurityClaims.MY_CLAIM_1,UserName.ToLower()));
			Claims.Add(new Claim(CSecurityClaims.MY_CLAIM_2,UserName.ToUpper()));

			TokenDescriptor.Subject=new ClaimsIdentity(Claims);
			TokenDescriptor.Expires=DateTime.UtcNow.AddDays(1);
			TokenDescriptor.Issuer=Issuer;
			TokenDescriptor.Audience=Audience;

			// !!! ALOGORITHM [SecurityAlgorithms.HmacSha256Signature] vyzaduje, aby KEY mal dlzku ASPON 128 BITS, teda 16 BYTES.
			TokenDescriptor.SigningCredentials=new SigningCredentials(SigningKey,SecurityAlgorithms.HmacSha256Signature);

			JwtSecurityTokenHandler								TokenHandler=new JwtSecurityTokenHandler();
			SecurityToken										SecurityToken=TokenHandler.CreateToken(TokenDescriptor);
			string												Token=TokenHandler.WriteToken(SecurityToken);

			return(Token);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION METHOD vykona LOGIN a vrati TOKEN.
		[HttpPost("Login")]
		public IActionResult Login([FromBody] CMyLoginModel Model)
		{
			if (ModelState.IsValid==true)
			{
				CUserProperties									User=MUsers.Where(P => P.UserName==Model.UserName).FirstOrDefault();

				if (User!=null)
				{
					bool										ValidPassword=(User.Password==Model.Password);

					if (ValidPassword==true)
					{
						// !!! Ak bol PASSWORD VALID, vygeneruje sa JSON WEB TOKEN, ktory sa posle v HTTP RESPONSE MESSAGE.
						string									Token=GenerateToken(Model.UserName,User.Roles);
						OkObjectResult							OkResult=Ok(new CMyTokenModel(Token));

						return(OkResult);
					}
					else
					{
						ModelState.AddModelError("","INVALID PASSWORD.");
					}
				}
				else
				{
					ModelState.AddModelError("","INVALID USERNAME.");
				}
			}

			BadRequestObjectResult								ErrorResult=BadRequest(ModelState);

			return(ErrorResult);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------