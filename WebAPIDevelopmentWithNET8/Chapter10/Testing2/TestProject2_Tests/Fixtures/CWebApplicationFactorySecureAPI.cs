using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.IdentityModel.Tokens;
using Testing2;
//----------------------------------------------------------------------------------------------------------------------
namespace TestProject2_Tests
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CWebApplicationFactorySecureAPI : WebApplicationFactory<Program>
	{
//----------------------------------------------------------------------------------------------------------------------
		protected override void ConfigureWebHost(IWebHostBuilder Builder)
		{
			base.ConfigureWebHost(Builder);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vygeneruje sa JWT TOKEN.
		public string GenerateToken(string UserName, string[] Roles)
		{
			using(IServiceScope Scope=Services.CreateScope())
			{
				IConfiguration									Configuration=Scope.ServiceProvider.GetRequiredService<IConfiguration>();

				// !!!!! CONFIGURATION SETTINGS sa beru z testovaneho PROGRAMU, kedze CONFIGURATION je v CLASS [Program] citana z jeho CONFIGURATION FILE.
				string											Secret=Configuration["JwtConfig:Secret"];
				string											Issuer=Configuration["JwtConfig:ValidIssuer"];
				string											Audience=Configuration["JwtConfig:ValidAudiences"];

				if (Secret==null || Issuer==null || Audience==null)
				{
					throw(new InvalidOperationException("JWT is not SET in the CONFIGURATION."));
				}

				SymmetricSecurityKey							SigningKey=new SymmetricSecurityKey(Encoding.UTF8.GetBytes(Secret));
				SecurityTokenDescriptor							TokenDescriptor=new SecurityTokenDescriptor();

				List<Claim>										Claims=new List<Claim>();

				Claims.Add(new Claim(ClaimTypes.Name,UserName));
				Claims.AddRange(Roles.Select(P => new Claim(ClaimTypes.Role,P)));

				TokenDescriptor.Subject=new ClaimsIdentity(Claims);
				TokenDescriptor.Expires=DateTime.UtcNow.AddDays(1);
				TokenDescriptor.Issuer=Issuer;
				TokenDescriptor.Audience=Audience;

				// !!! ALOGORITHM [SecurityAlgorithms.HmacSha256Signature] vyzaduje, aby KEY mal dlzku ASPON 128 BITS, teda 16 BYTES.
				TokenDescriptor.SigningCredentials=new SigningCredentials(SigningKey,SecurityAlgorithms.HmacSha256Signature);

				JwtSecurityTokenHandler							TokenHandler=new JwtSecurityTokenHandler();
				SecurityToken									SecurityToken=TokenHandler.CreateToken(TokenDescriptor);
				string											Token=TokenHandler.WriteToken(SecurityToken);

				return(Token);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------