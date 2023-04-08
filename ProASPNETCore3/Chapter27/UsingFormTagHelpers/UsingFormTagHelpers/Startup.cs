using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Antiforgery;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Razor;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.Net.Http.Headers;
using UsingFormTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFormTagHelpers
{
//----------------------------------------------------------------------------------------------------------------------
	public class Startup
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
		private IAntiforgery									MAntiforgery;
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
		private void ConfigureAntiForgeryCookie(AntiforgeryOptions Options)
		{
			Options.HeaderName="X-XSRF-TOKEN";
		}
//----------------------------------------------------------------------------------------------------------------------
		private async Task AddAntiForgeryCookieMiddleware(HttpContext Context, Func<Task> Next)
		{
			Context.Response.Cookies.Append("XSRF-TOKEN",MAntiforgery.GetAndStoreTokens(Context).RequestToken,new CookieOptions{HttpOnly=false});

			await Next();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			CNameProvider										NameProvider=new CNameProvider();

			NameProvider.AddName(new CName(1,"Timmy","Anderson",12));
			NameProvider.AddName(new CName(2,"Jenny","Thompson",13));

			Services.AddSingleton<INameProvider>(NameProvider);

			CPageNameProvider									PageNameProvider=new CPageNameProvider();

			PageNameProvider.AddName(new CPageName(1,"Timmy","Anderson",12));
			PageNameProvider.AddName(new CPageName(2,"Jenny","Thompson",13));

			Services.AddSingleton<IPageNameProvider>(PageNameProvider);

			CPersonProvider										PersonProvider=new CPersonProvider();

			PersonProvider.AddPerson(new CPerson(1,"Timmy","Anderson",12,7654321,1.52));
			PersonProvider.AddPerson(new CPerson(2,"Jenny","Thompson",13,1234567,1.45));

			Services.AddSingleton<IPersonProvider>(PersonProvider);

			CChildProvider										ChildProvider=new CChildProvider();

			ChildProvider.AddChild(new CChild(1,"Timmy","Anderson",12,ESex.Male));
			ChildProvider.AddChild(new CChild(2,"Jenny","Thompson",13,ESex.Female));

			Services.AddSingleton<IChildProvider>(ChildProvider);

			CNameWithNoteProvider								NameWithNoteProvider=new CNameWithNoteProvider();

			NameWithNoteProvider.AddName(new CNameWithNote(1,"Timmy","Anderson",12,"Note 1 !"));
			NameWithNoteProvider.AddName(new CNameWithNote(2,"Jenny","Thompson",13,"Note 2 !"));

			Services.AddSingleton<INameWithNoteProvider>(NameWithNoteProvider);

			// !!! Nastavi sa nazov ANTIFORGERY TOKEN COOKIE.
			Services.Configure<AntiforgeryOptions>(ConfigureAntiForgeryCookie);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment, IAntiforgery Antiforgery)
		{
			MAntiforgery=Antiforgery;

			ApplicationBuilder.UseDeveloperExceptionPage();
			ApplicationBuilder.UseStatusCodePages();

			ApplicationBuilder.UseStaticFiles();

			StaticFileOptions									Options=new StaticFileOptions();

			Options.FileProvider=new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(),"StaticFiles"));
			Options.RequestPath="/StaticFiles";

			// !!!!! METHOD pridava do REQUEST PIPELINE MIDDLEWARE COMPONENT [StaticFileMiddleware], ktora zabezpeci spracovanie STATIC FILES. Ak MIDDLEWARE COMPONENT detekuje poziadavku na ziskanie STATIC FILE, tak OKAMZITE GENERUJE HTTP RESPONSE a spracovanie NIE JE ODOSLANE do NASLEDUJUCICH MIDDLEWARE COMPONENTS v REQUEST PIPELINE.
			ApplicationBuilder.UseStaticFiles(Options);

			ApplicationBuilder.UseRouting();

			// !!! Nastavi sa MIDDLEWARE, ktory vklada ANTIFORGERY COOKIE do HTTP RESPONSE.
			ApplicationBuilder.Use(AddAntiForgeryCookieMiddleware);

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