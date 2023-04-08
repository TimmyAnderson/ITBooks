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
using Microsoft.Net.Http.Headers;
using Microsoft.OpenApi.Models;
using Swashbuckle.AspNetCore.SwaggerGen;
using Swashbuckle.AspNetCore.SwaggerUI;
using DocumentationUsingOpenAPI.Database;
using DocumentationUsingOpenAPI.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace DocumentationUsingOpenAPI
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
		private void ConfigureSwaggerService(SwaggerGenOptions Options)
		{
			OpenApiInfo											Info=new OpenApiInfo();

			Info.Title="WebApp";
			Info.Version="v1";

			Options.SwaggerDoc("v1",Info);
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureSwaggerUI(SwaggerUIOptions Options)
		{
			// !!! Definuje sa URL na ktorej bude bezat SWAGGER.
			// !!!!! Pri pokuse zmenit URL mi SWAGGER PRESTAL FUNGOVAT.
			Options.SwaggerEndpoint("/swagger/v1/swagger.json","WebApp");
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
			MvcBuilder.AddNewtonsoftJson();

			CMemoryNameProvider									Provider=new CMemoryNameProvider();

			Provider.AddName(new CName(1,"Timmy","Anderson",12));
			Provider.AddName(new CName(2,"Jenny","Thompson",13));

			// !!! SERVICE je zaregistrovany ako SINGLETON.
			Services.AddSingleton<INameProvider>(Provider);

			// !!! Prida sa OPEN API SERVICE.
			Services.AddSwaggerGen(ConfigureSwaggerService);
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

			// !!! Povoli sa pouzitie SWAGGER.
			ApplicationBuilder.UseSwagger();

			// !!! Povoli sa pouzitie SWAGGER UI.
			ApplicationBuilder.UseSwaggerUI(ConfigureSwaggerUI);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------