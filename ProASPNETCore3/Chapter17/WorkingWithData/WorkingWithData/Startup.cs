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
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Caching.Memory;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using WorkingWithData.Database;
using WorkingWithData.Endpoints;
using WorkingWithData.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace WorkingWithData
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
		private void ConfigureDistributedCacheOptions(MemoryDistributedCacheOptions Options)
		{
			Options.CompactionPercentage=0.5;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Nakonfiguruje sa DB.
		private void ConfigureDBOptions(DbContextOptionsBuilder Options)
		{
			// !!! Pouzije sa SQLite.
			Options.UseSqlite("Data Source=MyDatabase.db");

			// !!! Povoli sa LOGGING SENSITIVE DATA.
			Options.EnableSensitiveDataLogging(true);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			// !!! Prida sa DISTRIBUTED CACHE SERVICE.
			Services.AddDistributedMemoryCache(ConfigureDistributedCacheOptions);

			// !!! DB CONTEXT sa prida ako SERVICE do DEPENDENCY INJECTION FRAMEWORK.
			Services.AddDbContext<CDBContext>(ConfigureDBOptions);

			// !!! Alternativny sposob pridania DB CONTEXT ako SERVICE.
			//Services.AddTransient<CDBContext>();

			// !!! Pridanie CUSTOM SERVICE, ktory vykonava DB OPERATIONS nad ENTITY FRAMEWORK CORE.
			Services.AddTransient<IDBOperations,CDBOperations>();

			// !!! Prida sa SERVICE vykonavajuci RESPONSE CACHING.
			Services.AddResponseCaching();
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

			// !!! Prida sa MIDDLEWARE, ktory robi RESPONSE CACHING.
			ApplicationBuilder.UseResponseCaching();

			ApplicationBuilder.UseRouting();

			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");

				Endpoints.MapGet("/LongCalculation",CLongCalculationEndpoint.Endpoint);

				Endpoints.MapGet("/CachedAbsoluteLongCalculation",CCachedAbsoluteLongCalculationEndpoint.Endpoint);
				Endpoints.MapGet("/CachedRelativeLongCalculation",CCachedRelativeLongCalculationEndpoint.Endpoint);
				Endpoints.MapGet("/CachedSlidingLongCalculation",CCachedSlidingLongCalculationEndpoint.Endpoint);

				Endpoints.MapGet("/ResponseCacheLongCalculation",CResponseCacheLongCalculationEndpoint.Endpoint);

				// !!! Prida ROUTING pre RAZOR PAGES.
				Endpoints.MapRazorPages();
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------