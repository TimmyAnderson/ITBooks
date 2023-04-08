using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.Extensions.Caching.Memory;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Options;
using UnderstandingCorePlatform.Configurations;
using UnderstandingCorePlatform.Endpoints;
using UnderstandingCorePlatform.Middlewares;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform
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
		// !!! Nakonfiguruje sa REQUEST PIPELINE BRANCH A.
		private void ConfigureBranchA(IApplicationBuilder ApplicationBuilder)
		{
			ApplicationBuilder.UseRouting();

			ApplicationBuilder.UseMiddleware<CBranchAMiddleware1>();

			ApplicationBuilder.UseMiddleware<CBranchAMiddleware2>();

			// !!!!! BRANCHES mozu definovat aj vlastne ENDPOINTS.
			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				// !!! ENDPOINT k BRANCH A.
				// !!!!! ENDPOINT MUSI mat PRAZDU PATH, pretoze BRANCH odoberie z URL PATH identifikujucu danu BRANCH.
				Endpoints.MapGet("",CBranchAEndpoint.Endpoint);
			});
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Nakonfiguruje sa REQUEST PIPELINE BRANCH B.
		private void ConfigureBranchB(IApplicationBuilder ApplicationBuilder)
		{
			ApplicationBuilder.UseRouting();

			ApplicationBuilder.UseMiddleware<CBranchBMiddleware1>();

			ApplicationBuilder.UseMiddleware<CBranchBMiddleware2>();

			// !!!!! BRANCHES mozu definovat aj vlastne ENDPOINTS.
			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				// !!! ENDPOINT k BRANCH B.
				// !!!!! ENDPOINT MUSI mat PRAZDU PATH, pretoze BRANCH odoberie z URL PATH identifikujucu danu BRANCH.
				Endpoints.MapGet("",CBranchBEndpoint.Endpoint);
			});
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Nakonfiguruje sa REQUEST PIPELINE BRANCH C.
		private void ConfigureBranchC(IApplicationBuilder ApplicationBuilder)
		{
			ApplicationBuilder.UseRouting();

			ApplicationBuilder.UseMiddleware<CBranchCMiddleware1>();

			ApplicationBuilder.UseMiddleware<CBranchCMiddleware2>();

			// !!!!! BRANCHES mozu definovat aj vlastne ENDPOINTS.
			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				// !!! ENDPOINT k BRANCH C.
				// !!!!! ENDPOINT MUSI mat nastavenu PATH, pretoze pri registracii BRANCH cez METHOD [IApplicationBuilder IApplicationBuilder.MapWhen(Func<HttpContext,bool> Predicate, Action<IApplicationBuilder> Configuration)] sa NEODOBERA ziadna cast URL.
				Endpoints.MapGet("/EndpointBranchC",CBranchCEndpoint.Endpoint);
			});
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! PREDICATE vyhodnocuje ci HTTP REQUEST MESSAGE ma byt spracovana v REQUEST PIPELINE BRANCH C.
		private bool BranchCPredicate(HttpContext Context)
		{
			if (Context.Request.Path=="/EndpointBranchC")
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureConfigurationMethodWithConfiguration(CConfigurationMethodWithConfiguration Options)
		{
			// !!! Nastavia sa PROPERTIES CONFIGURATION CLASS MIDDLEWARE COMPONENT.
			Options.Value1="Timmy";
			Options.Value2="Anderson";
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureConfigurationClassWithConfiguration(CConfigurationClassWithConfiguration Options)
		{
			// !!! Nastavia sa PROPERTIES CONFIGURATION CLASS MIDDLEWARE COMPONENT.
			Options.Value1="Jenny";
			Options.Value2="Thompson";
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();
			
			// !!! Prida sa CONFIGURATION CUSTOM MIDDLEWARE COMPONENT.
			Services.Configure<CConfigurationMethodWithConfiguration>(ConfigureConfigurationMethodWithConfiguration);
			
			// !!! Prida sa CONFIGURATION CUSTOM MIDDLEWARE COMPONENT.
			Services.Configure<CConfigurationClassWithConfiguration>(ConfigureConfigurationClassWithConfiguration);
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

			// !!! Aplikuje sa MIDDLEWARE COMPONENT definovany ako METHOD.
			ApplicationBuilder.Use(CMethodMiddleware.MiddlewareCallback);

			// !!! Aplikuje sa MIDDLEWARE COMPONENT definovany ako CLASS.
			ApplicationBuilder.UseMiddleware<CClassMiddleware>();

			// !!! Aplikuje sa MIDDLEWARE COMPONENT definovany ako METHOD.
			ApplicationBuilder.Use(CMethodWithConfigurationMiddleware.MiddlewareCallback);

			// !!! Aplikuje sa MIDDLEWARE COMPONENT definovany ako CLASS.
			ApplicationBuilder.UseMiddleware<CClassWithConfigurationMiddleware>();

			// !!! SHORTCUT MIDDLEWARE COMPONENT vykona SHORTCUT REQUEST PIPELINE a priamo vygeneruje HTTP RESPONSE MESSAGE.
			ApplicationBuilder.UseMiddleware<CShortcutMiddleware>();

			// !!! Zaregistruje sa BRANCH A.
			ApplicationBuilder.Map("/EndpointBranchA",ConfigureBranchA);

			// !!! Zaregistruje sa BRANCH B.
			ApplicationBuilder.Map("/EndpointBranchB",ConfigureBranchB);

			// !!! Zaregistruje sa BRANCH C. Pouzitie BRANCH vyhodnocuje PREDICATE.
			ApplicationBuilder.MapWhen(BranchCPredicate,ConfigureBranchC);

			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");

				Endpoints.MapGet("/Endpoint1",CSimpleEndpoint.Endpoint);
				Endpoints.MapGet("/Endpoint2",CSimpleEndpoint.Endpoint);
				Endpoints.MapGet("/Endpoint3",CSimpleEndpoint.Endpoint);
				Endpoints.MapGet("/Endpoint4",CSimpleEndpoint.Endpoint);
				Endpoints.MapGet("/Endpoint5",CSimpleEndpoint.Endpoint);

				// !!! Prida ROUTING pre RAZOR PAGES.
				Endpoints.MapRazorPages();
			});

			// !!!!! Zaregistruje sa TERMINAL MIDDLEWARE COMPONENT.
			ApplicationBuilder.Run(CTerminalMiddleware.MiddlewareCallback);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------