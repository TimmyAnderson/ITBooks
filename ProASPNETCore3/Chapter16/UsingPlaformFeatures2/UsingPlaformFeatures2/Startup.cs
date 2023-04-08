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
using UsingPlaformFeatures2.Endpoints;
using UsingPlaformFeatures2.StatusCodePages;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingPlaformFeatures2
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
		// !!! METHOD vykonava kontrolu ci pre danu instanciu CLASS [HttpContext] sa ma vykonat COOKIE CONSENT.
		private bool ExecuteCheckConsent(HttpContext Context)
		{
			if (Context.Request.Path=="/CookieEssentialCounterCount" || Context.Request.Path=="/CookieEssentialCounterDelete")
			{
				return (true);
			}
			else
			{
				return(false);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! Nakonfiguruju sa COOKIE POLICIES.
		private void ConfigureCookiePolicies(CookiePolicyOptions Options)
		{
			Options.CheckConsentNeeded=ExecuteCheckConsent;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Nakonfiguruju sa SESSION OPTIONS.
		private void ConfigureSessionOptions(SessionOptions Options)
		{
			// !!! Nastavi sa EXPIRATION TIME pre SESSION DATA.
			Options.IdleTimeout=TimeSpan.FromSeconds(60);

			// !!! SESSION COOKIE NEBUDE vyzadovat COOKIE CONSENT.
			Options.Cookie.IsEssential=true;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Nakonfiguruje sa HTTPS REDIRECTION MIDDLEWARE COMPONENT.
		private void ConfigureHttpsRedirection(HttpsRedirectionOptions Options)
		{
			// !!! NASTAVI sa HTTPS PORT.
			Options.HttpsPort=50001;

			Options.RedirectStatusCode=StatusCodes.Status307TemporaryRedirect;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Nakonfiguruju sa COOKIE POLICIES.
			Services.Configure<CookiePolicyOptions>(ConfigureCookiePolicies);

			// !!!!! Prida sa SERVICE implementujuci SESSION STORAGE.
			Services.AddDistributedMemoryCache();

			// !!!!! Prida sa SERVICE, ktory konfiguruju SESSION.
			Services.AddSession(ConfigureSessionOptions);

			// !!! Nastavi sa HTTPS REDIRECTION MIDDLEWARE COMPONENT.
			Services.AddHttpsRedirection(ConfigureHttpsRedirection);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! DEPENDENCY INJECTION je mozne pouzit aj v METHOD [void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)].
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)
		{
			// !!!!! Na to, aby boli JAVA SCRIPT FILES korektne nacitane z DIRECTORY 'StaticFiles', je nutne definovat ROOT PATH pre [IWebHostEnvironment.WebRootFileProvider].
			WebHostEnvironment.WebRootFileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));

			// !!!!! Prida sa MIDDLEWARE COMPONENT, ktory pri vzniku UNHANDLED EXCEPTION vygeneruje HTML PAGE s podrobnostami o vzniknutej EXCEPTION.
			// !!!!! MIDDLEWARE COMPONENT by mal byt pridany na ZACIATOK REQUEST PIPELINE, aby zachytil EXCEPTIONS VSETKYCH MIDDLEWARE COMPONENTS nizsie v REQUEST PIPELINE.
			ApplicationBuilder.UseDeveloperExceptionPage();

			StatusCodePagesOptions								CodePagesOptions=new StatusCodePagesOptions();

			CodePagesOptions.HandleAsync=CStatusCodePage.GenerateStatusCodePage;

			// !!!!! Prida sa STATUS CODE MIDDLEWARE COMPONENT, ktory umoznuje generovat HTTP PAGE pri vzniku HTTP STATUS CODE v INTERVALE <400,599>.
			ApplicationBuilder.UseStatusCodePages(CodePagesOptions);

			// !!! Prida sa HTTPS REDIRECTION MIDDLEWARE COMPONENT.
			ApplicationBuilder.UseHttpsRedirection();

			// !!! Prida sa COOKIE POLICY MIDDLEWARE COMPONENT.
			ApplicationBuilder.UseCookiePolicy();

			// !!!!! Prida sa SESSION MIDDLEWARE COMPONENT. Pozicia SESSION MIDDLEWARE COMPONENT je DOLEZITA, pretoze az potom ako HTTP REQUEST MESSAGE prejde cez SESSION MIDDLEWARE COMPONENT su SESSION DATA pristupne.
			ApplicationBuilder.UseSession();

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

				Endpoints.MapGet("/CookieCounterCount",CCookieCounterCountEndpoint.Endpoint);
				Endpoints.MapGet("/CookieCounterDelete",CCookieCounterDeleteEndpoint.Endpoint);

				Endpoints.MapGet("/CookieEssentialCounterCount",CCookieEssentialCounterCountEndpoint.Endpoint);
				Endpoints.MapGet("/CookieEssentialCounterDelete",CCookieEssentialCounterDeleteEndpoint.Endpoint);
				Endpoints.MapGet("/CookieEssentialCounterGrantConsent",CCookieEssentialCounterGrantConsentEndpoint.Endpoint);
				Endpoints.MapGet("/CookieEssentialCounterWithdrawConsent",CCookieEssentialCounterWithdrawConsentEndpoint.Endpoint);

				Endpoints.MapGet("/SessionCounterCount",CSessionCounterCountEndpoint.Endpoint);
				Endpoints.MapGet("/SessionCounterDelete",CSessionCounterDeleteEndpoint.Endpoint);

				Endpoints.MapGet("/TestHttps",CTestHttpsEndpoint.Endpoint);

				Endpoints.MapGet("/ThrowUnhandledExcepion",CThrowUnhandledExcepionEndpoint.Endpoint);
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------