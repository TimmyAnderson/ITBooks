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
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using UsingFilters.CustomFilters;
using UsingFilters.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters
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
		private void SetMvcOptions(MvcOptions Options)
		{
			// !!! Prida sa GLOBAL FILTER.
			// !!!!! FILTER MUSI byt zaregistrovany v DEPENDENCY INJECTION FRAMEWORK.
			// !!!!! Kedze FILTER TYPE bol v DEPENDENCY INJECTION FRAMEWORK zaregistrovany pomocou METHOD [Services.AddSingleton<TYPE>()], tak FILTER ma SINGLETON LIFESCOPE.
			Options.Filters.AddService(typeof(CGlobalFilter1));

			// !!! Prida sa GLOBAL FILTER.
			// !!!!! Tento FILTER nie je potrebne zaregistrovat v DEPENDENCY INJECTION FRAMEWORK, pretoze jeho instancie NIE SU vytvarane pomocou DEPENDENCY INJECTION FRAMEWORK.
			// !!! FILTER LIFESCOPE je TRANSIENT.
			Options.Filters.Add(typeof(CGlobalFilter2));

			// !!! Prida sa GLOBAL FILTER.
			Options.Filters.AddService<COrderFilter2Attribute>(0);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			IMvcBuilder											MvcBuilder=Services.AddControllersWithViews();

			MvcBuilder.AddMvcOptions(SetMvcOptions);

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			Services.AddScoped<ITimeService,CTimeService>();

			// !!! SERVICE je zaregistrovany ako SINGLETON.
			Services.AddSingleton<ICounterService,CCounterService>();

			Services.AddSingleton(typeof(COrderFilter2Attribute),new COrderFilter2Attribute("GLOBAL FILTER",0));

			// !!! FILTER je zaregistrovany ako SCOPED FILTER.
			Services.AddSingleton<CAsynchronousResultServiceCreationAttribute>();

			// !!! FILTER je zaregistrovany ako SINGLETON.
			Services.AddSingleton<CFilterFactoryCounterFilter>();

			// !!! FILTER bude zaregistrovany ako SINGLETON.
			Services.AddSingleton<CGlobalFilter1>();
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