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
using CreatingRESTfulWebServices.Database;
using CreatingRESTfulWebServices.Model;
using CreatingRESTfulWebServices.Endpoints;
using Newtonsoft.Json;
//----------------------------------------------------------------------------------------------------------------------
namespace CreatingRESTfulWebServices
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
		// !!! Nastavi ASP.NET CORE JSON SERIALIZER OPTION.
		private void ConfigureJsonOptions(JsonOptions Options)
		{
			// !!! Nastavi sa, aby sa PROPERTIES s NULL VALUES neprenasali.
			Options.JsonSerializerOptions.IgnoreNullValues=true;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Nastavi NEWTON-SOFT JSON SERIALIZER OPTION.
		private void ConfigureJsonOptions(MvcNewtonsoftJsonOptions Options)
		{
			// !!! Nastavi sa, aby sa PROPERTIES s NULL VALUES neprenasali.
			Options.SerializerSettings.DefaultValueHandling=DefaultValueHandling.Ignore;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			IMvcBuilder											MvcBuilder=Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			// !!!!! Aby fungovala operacia PATCH, je NUTNE pouzit NEWTONSOFT JSON SERIALIZER.
			MvcBuilder.AddNewtonsoftJson(ConfigureJsonOptions);

			CMemoryNameProvider									Provider=new CMemoryNameProvider();

			Provider.AddName(new CName(1,"Timmy","Anderson",12));
			Provider.AddName(new CName(2,"Jenny","Thompson",13));
			Provider.AddName(new CName(3,"John","Stone",13));

			// !!! SERVICE je zaregistrovany ako SINGLETON.
			Services.AddSingleton<INameProvider>(Provider);

			// !!! Nastavia sa PROPERTIES JSON SERIALIZER.
			Services.Configure<JsonOptions>(ConfigureJsonOptions);
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

				// !!! Zaregistruju sa API ENDPOINTS.
				Endpoints.MapGet("api/APIEndpointName",CAPIEndpointName.GetNames);
				Endpoints.MapGet("api/APIEndpointName/{ID}",CAPIEndpointName.GetName);
				Endpoints.MapPost("api/APIEndpointName",CAPIEndpointName.InsertName);
				Endpoints.MapPut("api/APIEndpointName",CAPIEndpointName.UpdateName);
				Endpoints.Map("api/APIEndpointName/patch/{ID}",CAPIEndpointName.PartialUpdateName);
				Endpoints.MapDelete("api/APIEndpointName/{ID}",CAPIEndpointName.DeleteName);
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------