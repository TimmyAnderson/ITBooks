using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Razor;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.Net.Http.Headers;
using UsingRazorPages.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingRazorPages
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
		private void ConfigureRazorPagesOptions(RazorPagesOptions Options)
		{
			// !!! Prida sa CUSTOM ROUTE, ktora mapuje PATH [/Pages/ShowNameStaticRouting.cshtml] na ROUTE [/Startup/Segment1/Segment2/Segment3/ShowNameStaticRouting].
			// !!!!! Kedze RAZOR PAGE [ShowNameStaticRouting.cshtml] MA APLIKOVANU CUSTOM ROUTE cez KEYWORD [@page], po pridani tejto CUSTOM ROUTES na RAZOR PAGE ukazuju obe ROUTES.
			Options.Conventions.AddPageRoute("/ShowNameStaticRouting","/Startup/Segment1/Segment2/Segment3/ShowNameStaticRouting");

			// !!! Prida sa CUSTOM ROUTE, ktora mapuje PATH [/Pages/ShowNameUsingRoutedParameters.cshtml] na ROUTE [/Startup/ShowNameUsingRoutedParameters/{ID:int}/{FirstName:alpha}/{LastName:alpha}/{Age:int}].
			// !!!!! Kedze RAZOR PAGE [ShowNameUsingRoutedParameters.cshtml] MA APLIKOVANU CUSTOM ROUTE cez KEYWORD [@page], po pridani tejto CUSTOM ROUTES na RAZOR PAGE ukazuju obe ROUTES.
			Options.Conventions.AddPageRoute("/ShowNameUsingRoutedParameters","/Startup/ShowNameUsingRoutedParameters/{ID:int}/{FirstName:alpha}/{LastName:alpha}/{Age:int}");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			// !!! Prida sa CUSTOM ROUTES pre RAZOR PAGES.
			Services.Configure<RazorPagesOptions>(ConfigureRazorPagesOptions);

			CMemoryNameProvider									Provider=new CMemoryNameProvider();

			Provider.AddName(new CName(1,"Timmy","Anderson",12));
			Provider.AddName(new CName(2,"Jenny","Thompson",13));

			// !!! SERVICE je zaregistrovany ako SINGLETON.
			Services.AddSingleton<INameProvider>(Provider);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)
		{
			ApplicationBuilder.UseDeveloperExceptionPage();
			ApplicationBuilder.UseStatusCodePages();

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

				// !!! Prida ROUTING pre RAZOR PAGES.
				Endpoints.MapRazorPages();
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------