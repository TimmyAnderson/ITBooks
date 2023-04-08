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
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Net.Http.Headers;
using RealApplication1.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace RealApplication1
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
		private void ConfigureDBContext(DbContextOptionsBuilder OptionsBuilder)
		{
			OptionsBuilder.UseSqlite("Data Source=MyDatabase.db");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			Services.AddDbContext<CApplicationDbContext>(ConfigureDBContext);

			Services.AddScoped<IStoreRepository,CEntityFrameworkStoreRepository>();
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

			ApplicationBuilder.UseRouting();

			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				// !!!!! Poradie ROUTES je DOLEZITE.

				// !!! Nastavi ROUTE s prehladnejsimi URL v tvare 'Products/PageXXX', kde 'XXX' je cislo PAGE.
                Endpoints.MapControllerRoute("Pagination","Products/Page{ProductPage}",new {Controller="Home", Action="Index"});

				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");
			});

			// !!!!! METHOD vytvori DB SCHEME a zaroven naplni DB datami.
			CInitialDataSeed.CreateSchemeAndAddInitialData(ApplicationBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------