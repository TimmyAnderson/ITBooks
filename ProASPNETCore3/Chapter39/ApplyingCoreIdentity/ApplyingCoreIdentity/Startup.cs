using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
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
using ApplyingCoreIdentity.Database;
using ApplyingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace ApplyingCoreIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	public class Startup
	{
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
		// !!! METHOD vytvara CUSTOM POLICY.
		private void CreateCustomPolicy1(AuthorizationPolicyBuilder Builder)
		{
			Builder.RequireAuthenticatedUser();
			Builder.RequireRole("Administrators");
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vytvara CUSTOM POLICY.
		private void CreateCustomPolicy2(AuthorizationPolicyBuilder Builder)
		{
			Builder.RequireAuthenticatedUser();
			Builder.RequireRole("Users");
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vytvara CUSTOM POLICY s CUSTOM REQUIREMENT.
		private void CreateCustomPolicyWithCustomRequirement(AuthorizationPolicyBuilder Builder)
		{
			Builder.RequireAuthenticatedUser();

			CCustomAuthorizationRequirement						CustomAuthorizationRequirement=new CCustomAuthorizationRequirement(new string[]{"Timmy"});

			// !!! Prida sa CUSTOM REQUIREMENT.
			Builder.AddRequirements(CustomAuthorizationRequirement);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vytvara CUSTOM POLICY s CUSTOM REQUIREMENT, ktora robi RESOURCE AUTHORIZATION.
		private void CreateResourceAuthorizationPolicyForAll(AuthorizationPolicyBuilder Builder)
		{
			Builder.RequireAuthenticatedUser();

			CCustomResourceAuthorizationRequirement				CustomResourceAuthorizationRequirement=new CCustomResourceAuthorizationRequirement(true);

			// !!! Prida sa CUSTOM REQUIREMENT.
			Builder.AddRequirements(CustomResourceAuthorizationRequirement);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD vytvara CUSTOM POLICY s CUSTOM REQUIREMENT, ktora robi RESOURCE AUTHORIZATION.
		private void CreateResourceAuthorizationPolicyForUser(AuthorizationPolicyBuilder Builder)
		{
			Builder.RequireAuthenticatedUser();

			CCustomResourceAuthorizationRequirement				CustomResourceAuthorizationRequirement=new CCustomResourceAuthorizationRequirement(false);

			// !!! Prida sa CUSTOM REQUIREMENT.
			Builder.AddRequirements(CustomResourceAuthorizationRequirement);
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
		private void ConfigureAuthenticationCookie(CookieAuthenticationOptions Options)
		{
			// !!!!! Nastavi sa URL LOGIN PAGE.
			Options.LoginPath="/Login/PerformLogin";

			// !!!!! Nastavi sa URL v pripade, ze AUTHORIZATION ZLYHALA.
			Options.AccessDeniedPath="/Login/AuthorizationError";
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureAuthorization(AuthorizationOptions Options)
		{
			// !!! Nastavi sa CUSTOM POLICY.
			Options.AddPolicy("CustomPolicy1",CreateCustomPolicy1);

			// !!! Nastavi sa CUSTOM POLICY.
			Options.AddPolicy("CustomPolicy2",CreateCustomPolicy2);

			// !!! Nastavi sa CUSTOM POLICY.
			Options.AddPolicy("CustomPolicyWithCustomRequirement",CreateCustomPolicyWithCustomRequirement);

			// !!! Nastavi sa CUSTOM POLICY.
			Options.AddPolicy("ResourceAuthorizationPolicyForAll",CreateResourceAuthorizationPolicyForAll);

			// !!! Nastavi sa CUSTOM POLICY.
			Options.AddPolicy("ResourceAuthorizationPolicyForUser",CreateResourceAuthorizationPolicyForUser);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			// !!! Prida BLAZOR SERVICE.
			Services.AddServerSideBlazor();

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

			// !!!!! Nastavi sa LOGIN PAGE URL a ACCESS DENIED PAGE URL.
			Services.ConfigureApplicationCookie(ConfigureAuthenticationCookie);

			// !!!!! Prida sa SERVICE, ktory pridava CUSTOM CLAIM do CLAIMS PRINCIPAL.
			Services.AddSingleton<IClaimsTransformation,CCustomClaimsTransformation>();

			// !!!!! METHOD konfiguruje POLICIES.
			Services.AddAuthorization(ConfigureAuthorization);

			// !!!!! Zaregistruje sa CUSTOM AUTHORIZATION REQUIREMENT HANDLER.
			Services.AddTransient<IAuthorizationHandler,CCustomAuthorizationRequirementHandler>();

			// !!!!! Zaregistruje sa CUSTOM AUTHORIZATION REQUIREMENT HANDLER, ktory kontroluje pristup k PROTECTER RESOURCE.
			Services.AddTransient<IAuthorizationHandler,CCustomResourceAuthorizationRequirementHandler>();
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

				// !!! Prida SIGNALR HUB pre BLAZOR SERVER.
				Endpoints.MapBlazorHub();

				Endpoints.MapFallbackToPage("/Blazor/PageSecureBlazorRouter");
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------