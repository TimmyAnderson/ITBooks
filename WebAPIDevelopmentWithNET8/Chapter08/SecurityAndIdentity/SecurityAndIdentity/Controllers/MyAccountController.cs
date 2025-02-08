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
	public sealed class MyAccountController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
		private readonly UserManager<CIdentityUser>				MUserManager;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyAccountController(IConfiguration Configuration, UserManager<CIdentityUser> UserManager)
		{
			MConfiguration=Configuration;
			MUserManager=UserManager;
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

					IdentityResult								IdentityResult1=await MUserManager.CreateAsync(User,Model.Password);

					// !!! USER bol uspesne vytvoreny.
					if (IdentityResult1.Succeeded==true)
					{
						List<string>							Roles=new List<string>();

						Roles.Add(CIdentityRoles.USERS);

						if (User.UserName==CIdentityUsers.VIP)
						{
							Roles.Add(CIdentityRoles.VIPS);
						}
						else if (User.UserName==CIdentityUsers.ADMINISTRATOR)
						{
							Roles.Add(CIdentityRoles.VIPS);
							Roles.Add(CIdentityRoles.ADMINISTRATORS);
						}

						IdentityResult							IdentityResult2=await MUserManager.AddToRolesAsync(User,Roles);

						if (IdentityResult2.Succeeded==true)
						{
							string[]							UserRoles=(await MUserManager.GetRolesAsync(User)).ToArray();

							// !!! Vygeneruje sa JWT TOKEN.
							string								Token=GenerateToken(Model.UserName,UserRoles);
							OkObjectResult						OkResult=Ok(new CMyTokenModel(Token));

							return(OkResult);
						}
						else
						{
							AddIdentityErrors(ModelState,IdentityResult2);
						}
					}
					else
					{
						AddIdentityErrors(ModelState,IdentityResult1);
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
					bool										ValidPassword=await MUserManager.CheckPasswordAsync(User,Model.Password);

					if (ValidPassword==true)
					{
						string[]								UserRoles=(await MUserManager.GetRolesAsync(User)).ToArray();

						// !!! Ak bol PASSWORD VALID, vygeneruje sa JSON WEB TOKEN, ktory sa posle v HTTP RESPONSE MESSAGE.
						string									Token=GenerateToken(Model.UserName,UserRoles);
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