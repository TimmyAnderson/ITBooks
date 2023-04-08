using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.IdentityModel.Tokens;
using SecuringWebServicesBearerTokens.Database;
using SecuringWebServicesBearerTokens.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesBearerTokens
{
//----------------------------------------------------------------------------------------------------------------------
	public class Startup
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE obsahuje JWT SECRET VALUE, ktora sa pouziva pri ENCRYPTION a DECRYPTION.
		public const string										JWT_SECRET="SOME_SUPER_SECRET";
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Startup(IConfiguration Configuration)
		{
			MConfiguration=Configuration;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IConfiguration									Configuration
		{
			get
			{
				return(MConfiguration);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private Func<RedirectContext<CookieAuthenticationOptions>,Task> RedirectToError(int StatusCode)
		{
			Func<RedirectContext<CookieAuthenticationOptions>,Task>	RedirectMethod=Context =>
			{
				// !!! Nastavi sa HTTP ERROR CODE cim sa ukonci spracovanie HTTP REQUEST MESSAGE.
				Context.HttpContext.Response.StatusCode=StatusCode;

				return(Task.CompletedTask);
			};

			return(RedirectMethod);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureIdentity(IdentityOptions Options)
		{
			// !!! Nastavia sa PASSWORD POLICIES.
			Options.Password.RequiredLength=6;
			Options.Password.RequireDigit=true;
			Options.Password.RequireNonAlphanumeric=true;
			Options.Password.RequireLowercase=true;
			Options.Password.RequireUppercase=true;

			// !!! Nastavia sa USER POLICIES.
			Options.User.AllowedUserNameCharacters="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_.";
			Options.User.RequireUniqueEmail=true;
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureAuthentication(AuthenticationOptions Options)
		{
			// !!! Nastavi sa AUTHENTICATION SCHEME.
			Options.DefaultScheme=CookieAuthenticationDefaults.AuthenticationScheme;

			// !!! Nastavi sa CHALLENGE SCHEME.
			Options.DefaultChallengeScheme=CookieAuthenticationDefaults.AuthenticationScheme;
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureAuthorization(AuthorizationOptions Options)
		{
			// EMPTY.
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureAuthenticationCookie(CookieAuthenticationOptions Options)
		{
			// !!!!! Vypne sa REDIRECTION na LOGIN PAGE, tym ze pri pokuse o REDIRECTION na LOGIN PAGE ASP.NET CORE vrati HTTP ERROR CODE.
			Options.Events.OnRedirectToLogin=RedirectToError(StatusCodes.Status401Unauthorized);

			// !!!!! Vypne sa REDIRECTION na ACCESS DENIED PAGE, tym ze pri pokuse o REDIRECTION na ACCESS DENIED PAGE ASP.NET CORE vrati HTTP ERROR CODE.
			Options.Events.OnRedirectToAccessDenied=RedirectToError(StatusCodes.Status403Forbidden);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD nastavi JWT BEARER TOKEN AUTHENTICATION.
		private void ConfigureJWTBearer(JwtBearerOptions Options)
		{
			Options.RequireHttpsMetadata=false;
			Options.SaveToken=true;

			Options.TokenValidationParameters=new TokenValidationParameters();

			Options.TokenValidationParameters.ValidateAudience=false;
			Options.TokenValidationParameters.ValidateIssuer=false;
			Options.TokenValidationParameters.ValidateIssuerSigningKey=true;

			byte[]												SecurityCode=Encoding.ASCII.GetBytes(JWT_SECRET);

			Options.TokenValidationParameters.IssuerSigningKey=new SymmetricSecurityKey(SecurityCode);

			Options.Events=new JwtBearerEvents();
			Options.Events.OnTokenValidated=ValidateJWTBearerToken;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD vykonava VALIDATION JWT BEARER TOKEN.
		private async Task ValidateJWTBearerToken(TokenValidatedContext Context)
		{
			UserManager<CCustomUser>							UserManager=Context.HttpContext.RequestServices.GetRequiredService<UserManager<CCustomUser>>();
			SignInManager<CCustomUser>							SignInManager=Context.HttpContext.RequestServices.GetRequiredService<SignInManager<CCustomUser>>();

			// !!! Z PRINCIPAL sa ziska USER NAME.
			Claim												NameClaim=Context.Principal.FindFirst(ClaimTypes.Name);

			if (NameClaim!=null)
			{
				string											UserName=NameClaim.Value;

				if (UserName!=null)
				{
					// !!! Pre dany USER NAME sa najde USER.
					CCustomUser									User=await UserManager.FindByNameAsync(UserName);

					if (User!=null)
					{
						// !!!!! Pre daneho USER sa vytvori PRINCIPAL, ktory uz bude mat CLAIMS vytiahnute z IDENTITY DB.
						Context.Principal=await SignInManager.CreateUserPrincipalAsync(User);
					}
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			// !!! Prida sa ENTITY FRAMEWORK DB CONTEXT ako SERVICE.
			Services.AddDbContext<CIdentityDBContext>();

			// !!! Prida sa IDENTITY SERVICE.
			IdentityBuilder										IdentityBuilder=Services.AddIdentity<CCustomUser,CCustomRole>(ConfigureIdentity);

			// !!! Nakonfiguruje sa IDENTITY SERVICE.
			IdentityBuilder.AddEntityFrameworkStores<CIdentityDBContext>();
			IdentityBuilder.AddDefaultTokenProviders();

			// !!! Odstrania sa existujuce PASSWORD VALIDATORS.
			ServiceDescriptor[]									PasswordValidatorServices=Services.Where(P => P.ServiceType==typeof(IPasswordValidator<CCustomUser>)).ToArray();

			foreach(ServiceDescriptor Descriptor in PasswordValidatorServices)
			{
				Services.Remove(Descriptor);
			}

			// !!! Prida sa CUSTOM PASSWORD VALIDATOR.
			//Services.AddTransient<IPasswordValidator<CCustomUser>,CSimplePasswordValidator>();
			Services.AddTransient<IPasswordValidator<CCustomUser>,CComplexPasswordValidator>();

			// !!! Odstrania sa existujuce USER VALIDATORS.
			ServiceDescriptor[]									UserValidatorServices=Services.Where(P => P.ServiceType==typeof(IUserValidator<CCustomUser>)).ToArray();

			foreach(ServiceDescriptor Descriptor in UserValidatorServices)
			{
				Services.Remove(Descriptor);
			}

			// !!! Prida sa CUSTOM USER VALIDATOR.
			//Services.AddTransient<IUserValidator<CCustomUser>,CSimpleUserValidator>();
			Services.AddTransient<IUserValidator<CCustomUser>,CComplexUserValidator>();

			// !!!!! Prida sa SERVICE, ktory pridava CUSTOM CLAIM do CLAIMS PRINCIPAL.
			Services.AddSingleton<IClaimsTransformation,CCustomClaimsTransformation>();

			// !!!!! METHOD konfiguruje AUTHENTICATION.
			AuthenticationBuilder								Builder=Services.AddAuthentication(ConfigureAuthentication);

			// !!!!! Nastavi sa LOGIN PAGE HANDLER a ACCESS DENIED PAGE HANDLER.
			Builder.AddCookie(ConfigureAuthenticationCookie);

			// !!!!! Nastavi sa JWT BEARER TOKEN AUTHENTICATION.
			Builder.AddJwtBearer(ConfigureJWTBearer);

			// !!!!! METHOD konfiguruje AUTHORIZATION.
			Services.AddAuthorization(ConfigureAuthorization);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)
		{
			// !!!!! Na to, aby boli JAVA SCRIPT FILES korektne nacitane z DIRECTORY 'StaticFiles', je nutne definovat ROOT PATH pre [IWebHostEnvironment.WebRootFileProvider].
			WebHostEnvironment.WebRootFileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));

			ApplicationBuilder.UseDeveloperExceptionPage();
			ApplicationBuilder.UseStatusCodePages();

			ApplicationBuilder.UseStaticFiles();

			StaticFileOptions									Options=new StaticFileOptions();

			Options.FileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));
			Options.RequestPath="/StaticFiles";

			// !!!!! METHOD pridava do REQUEST PIPELINE MIDDLEWARE COMPONENT [StaticFileMiddleware], ktora zabezpeci spracovanie STATIC FILES. Ak MIDDLEWARE COMPONENT detekuje poziadavku na ziskanie STATIC FILE, tak OKAMZITE GENERUJE HTTP RESPONSE a spracovanie NIE JE ODOSLANE do NASLEDUJUCICH MIDDLEWARE COMPONENTS v REQUEST PIPELINE.
			ApplicationBuilder.UseStaticFiles(Options);

			ApplicationBuilder.UseRouting();

			// !!!!! Do PIPELINE sa prida AUTHENTICATION MIDDLEWARE COMPONENT.
			ApplicationBuilder.UseAuthentication();

			// !!!!! Do PIPELINE sa prida AUTHORIZATION MIDDLEWARE COMPONENT.
			ApplicationBuilder.UseAuthorization();

			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");

				// !!! Prida ROUTING pre RAZOR PAGES.
				Endpoints.MapRazorPages();
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------