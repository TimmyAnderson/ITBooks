using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Razor;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Net.Http.Headers;
using UsingPlaformFeatures1.Endpoints;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures1
{
//----------------------------------------------------------------------------------------------------------------------
	public class Startup
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! SERVICE implementujuci INTERFACE [IConfiguration] je naplneny pomocou DEPENDENCY INJECTION FRAMEWORK.
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
		private bool CategoryLogFilter(string Category, LogLevel Level)
		{
			if (Level<LogLevel.Information)
			{
				if (Category!=typeof(CPerformLoggingEndpoint).FullName)
				{
					return(false);
				}
			}

			return(true);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureLogging(ILoggingBuilder Builder)
		{
			// !!! Prida sa CONSOLE LOG PROVIDER.
			Builder.AddConsole();

			// !!! Nastavi sa MINIMUM LOG LEVEL.
			Builder.SetMinimumLevel(LogLevel.Debug);

			// !!! Prida sa CATEGORY LOG FILTER.
			Builder.AddFilter(CategoryLogFilter);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida sa LOGGING SERVICE.
			Services.AddLogging(ConfigureLogging);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! DEPENDENCY INJECTION je mozne pouzit aj v METHOD [void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)].
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)
		{
			// !!!!! Na to, aby boli JAVA SCRIPT FILES korektne nacitane z DIRECTORY 'StaticFiles', je nutne definovat ROOT PATH pre [IWebHostEnvironment.WebRootFileProvider].
			WebHostEnvironment.WebRootFileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));

			// !!!!! Prida sa MIDDLEWARE COMPONENT, ktory pri vzniku UNHANDLED EXCEPTION vygeneruje HTML PAGE s podrobnostami o vzniknutej EXCEPTION.
			ApplicationBuilder.UseDeveloperExceptionPage();

			ApplicationBuilder.UseStatusCodePages();

			// !!! Prida sa DEFAULT STATIC FILES MIDDLEWARE COMPONENT, ktory mapuje FILES do DIRECTORY [wwwroot].
			ApplicationBuilder.UseStaticFiles();

			StaticFileOptions									Options=new StaticFileOptions();

			Options.FileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));
			Options.RequestPath="/StaticFiles";

			// !!! Prida sa STATIC FILES MIDDLEWARE COMPONENT, ktory mapuje FILES do DIRECTORY [StaticFiles].
			ApplicationBuilder.UseStaticFiles(Options);

			StaticFileOptions									Options1=new StaticFileOptions();

			// !!! FILE PROVIDER musi obsahovat FULL PATH.
			Options1.FileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles1"));

			// !!! Mapuju sa FILES, ktore maju v URL VALUE [/Files1] na DIRECTORY [StaticFiles1].
			Options1.RequestPath="/Files1";

			// !!! Prida sa STATIC FILES MIDDLEWARE COMPONENT, ktory mapuje FILES do DIRECTORY [StaticFiles1].
			ApplicationBuilder.UseStaticFiles(Options1);

			StaticFileOptions									Options2=new StaticFileOptions();

			// !!! FILE PROVIDER musi obsahovat FULL PATH.
			Options2.FileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles2"));

			// !!! Mapuju sa FILES, ktore maju v URL VALUE [/Files2] na DIRECTORY [StaticFiles2].
			Options2.RequestPath="/Files2";

			// !!! Prida sa STATIC FILES MIDDLEWARE COMPONENT, ktory mapuje FILES do DIRECTORY [StaticFiles2].
			ApplicationBuilder.UseStaticFiles(Options2);

			ApplicationBuilder.UseRouting();

			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");

				Endpoints.MapGet("/ShowConfigurationValues",CShowConfigurationValuesEndpoint.Endpoint);

				Endpoints.MapGet("/ShowCurrentEnvironment",CShowCurrentEnvironmentEndpoint.Endpoint);

				Endpoints.MapGet("/ShowUserSecrets",CShowUserSecretsEndpoint.Endpoint);

				Endpoints.MapGet("/PerformLogging",CPerformLoggingEndpoint.Endpoint);

				Endpoints.MapGet("/UsingClientSideLibrary",CUsingClientSideLibraryEndpoint.Endpoint);
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------