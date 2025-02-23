using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.Extensions.Configuration;
using Microsoft.IdentityModel.Tokens;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CONTROLLER sluzi na ACCOUNT REGISTRATION a na LOGIN.
	[ApiController]
	[Route("[controller]")]
	public sealed class PasswordPolicyController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
		private readonly UserManager<CIdentityUser>				MUserManager;
		private readonly SignInManager<CIdentityUser>			MSingInManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PasswordPolicyController(IConfiguration Configuration, UserManager<CIdentityUser> UserManager, SignInManager<CIdentityUser> SingInManager)
		{
			MConfiguration=Configuration;
			MUserManager=UserManager;
			MSingInManager=SingInManager;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void AddIdentityErrors(ModelStateDictionary ModelState, IdentityResult IdentityResult)
		{
			// !!! Ak doslo k ERRORS, zapisu sa tieto do HTTP RESPONSE MESSAGE.
			foreach(IdentityError Error in IdentityResult.Errors)
			{
				ModelState.AddModelError("",Error.Description);
			}
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
		// !!! ACTION METHOD zaregistruje do IDENTITY DB noveho USER a vrati TOKEN.
		[HttpPost("Register")]
		public async Task<IActionResult> Register([FromBody] CMyUserModel Model)
		{
			if (ModelState.IsValid==true)
			{
				CIdentityUser									ExistingUser=await MUserManager.FindByNameAsync(Model.UserName);

				if (ExistingUser==null)
				{
					CIdentityUser								User=new CIdentityUser();

					User.UserName=Model.UserName;
					User.PhoneNumber=Model.PhoneNumber;
					User.SecurityStamp=Guid.NewGuid().ToString();

					IdentityResult								IdentityResult=await MUserManager.CreateAsync(User,Model.Password);

					// !!! USER bol uspesne vytvoreny.
					if (IdentityResult.Succeeded==true)
					{
						string[]								UserRoles=(await MUserManager.GetRolesAsync(User)).ToArray();

						// !!! Vygeneruje sa JWT TOKEN.
						string									Token=GenerateToken(Model.UserName,UserRoles);
						OkObjectResult							OkResult=Ok(new CMyTokenModel(Token));

						return(OkResult);
					}
					else
					{
						AddIdentityErrors(ModelState,IdentityResult);
					}
				}
				else
				{
					ModelState.AddModelError("","USER NAME is already REGISTERED.");
				}
			}

			BadRequestObjectResult								ErrorResult=BadRequest(ModelState);

			return(ErrorResult);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION METHOD vykona LOGIN a vrati TOKEN.
		[HttpPost("Login")]
		public async Task<IActionResult> Login([FromBody] CMyLoginModel Model)
		{
			if (ModelState.IsValid==true)
			{
				CIdentityUser									User=await MUserManager.FindByNameAsync(Model.UserName);

				// !!! Ziska sa USER z IDENTITY DB.
				if (User!=null)
				{
					// !!! Vykona sa VALIDATION zadaneho PASSWORD.
					Microsoft.AspNetCore.Identity.SignInResult	ValidPassword=await MSingInManager.CheckPasswordSignInAsync(User,Model.Password,true);

					if (ValidPassword.Succeeded==true)
					{
						string[]								UserRoles=(await MUserManager.GetRolesAsync(User)).ToArray();

						// !!! Ak bol PASSWORD VALID, vygeneruje sa JSON WEB TOKEN, ktory sa posle v HTTP RESPONSE MESSAGE.
						string									Token=GenerateToken(Model.UserName,UserRoles);
						OkObjectResult							OkResult=Ok(new CMyTokenModel(Token));

						return(OkResult);
					}
					else
					{
						if (ValidPassword.IsLockedOut==false)
						{
							ModelState.AddModelError("","INVALID PASSWORD.");
						}
						else
						{
							ModelState.AddModelError("","ACCOUNT is LOCKED.");
						}
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