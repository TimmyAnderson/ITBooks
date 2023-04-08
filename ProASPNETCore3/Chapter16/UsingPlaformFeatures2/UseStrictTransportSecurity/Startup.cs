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
using Microsoft.Net.Http.Headers;
using UseStrictTransportSecurity.Endpoints;
//----------------------------------------------------------------------------------------------------------------------
namespace UseStrictTransportSecurity
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
		// !!! Nakonfiguruje sa HSTS MIDDLEWARE COMPONENT.
		// !!!!! Na to, aby HTTP STRICT TRANSPORT SECURITY (HSTS) v ASP.NET CORE naozaj fungoval, MUSI HTTP PROTOCOL bezat na PORTE 80 a HTTPS PROTOCOL bezat na PORTE 443.
		private void ConfigureHsts(HstsOptions Options)
		{
			// !!! BY-DEFAULT je LOCALHOST medzi EXCLUDED HOSTS.
			Options.ExcludedHosts.Clear();

			Options.IncludeSubDomains=true;

			// !!! Nastavi sa EXPIRATION TIME.
			Options.MaxAge=TimeSpan.FromSeconds(60);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Nakonfiguruje sa HSTS MIDDLEWARE COMPONENT.
			// !!!!! Na to, aby HTTP STRICT TRANSPORT SECURITY (HSTS) v ASP.NET CORE naozaj fungoval, MUSI HTTP PROTOCOL bezat na PORTE 80 a HTTPS PROTOCOL bezat na PORTE 443.
			Services.AddHsts(ConfigureHsts);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! DEPENDENCY INJECTION je mozne pouzit aj v METHOD [void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)].
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)
		{
			// !!!!! Na to, aby boli JAVA SCRIPT FILES korektne nacitane z DIRECTORY 'StaticFiles', je nutne definovat ROOT PATH pre [IWebHostEnvironment.WebRootFileProvider].
			WebHostEnvironment.WebRootFileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));

			ApplicationBuilder.UseDeveloperExceptionPage();
			ApplicationBuilder.UseStatusCodePages();

			// !!! Prida sa HSTS MIDDLEWARE COMPONENT do REQUEST PIPELINE.
			// !!!!! Na to, aby HTTP STRICT TRANSPORT SECURITY (HSTS) v ASP.NET CORE naozaj fungoval, MUSI HTTP PROTOCOL bezat na PORTE 80 a HTTPS PROTOCOL bezat na PORTE 443.
			ApplicationBuilder.UseHsts();

			ApplicationBuilder.UseStaticFiles();

			StaticFileOptions									Options=new StaticFileOptions();

			Options.FileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));
			Options.RequestPath="/StaticFiles";

			// !!!!! METHOD pridava do REQUEST PIPELINE MIDDLEWARE COMPONENT [StaticFileMiddleware], ktora zabezpeci spracovanie STATIC FILES. Ak MIDDLEWARE COMPONENT detekuje poziadavku na ziskanie STATIC FILE, tak OKAMZITE GENERUJE HTTP RESPONSE a spracovanie NIE JE ODOSLANE do NASLEDUJUCICH MIDDLEWARE COMPONENTS v REQUEST PIPELINE.
			ApplicationBuilder.UseStaticFiles(Options);

			ApplicationBuilder.UseRouting();

			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");

				Endpoints.MapGet("/TestHttps",CTestHttps.Endpoint);
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------