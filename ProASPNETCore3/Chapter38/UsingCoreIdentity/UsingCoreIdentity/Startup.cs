using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
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
using UsingCoreIdentity.Database;
using UsingCoreIdentity.Security;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingCoreIdentity
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

			// !!! Do PIPELINE sa prida AUTHENTICATION MIDDLEWARE COMPONENT.
			ApplicationBuilder.UseAuthentication();

			ApplicationBuilder.UseRouting();

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