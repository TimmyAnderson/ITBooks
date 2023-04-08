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
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Constraints;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.FileProviders;
using Microsoft.Extensions.Hosting;
using Microsoft.Net.Http.Headers;
using UsingDependencyInjection.Middlewares;
using UsingDependencyInjection.Model;
using UsingDependencyInjection.Service;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection
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
		// !!! METHOD vytvara pre DEPENDENCY INJECTION FRAMEWORK instanciu CLASS 'CFactoryFunctionService'.
		private CFactoryFunctionService CreateFactoryFunctionService(IServiceProvider ServiceProvider)
		{
			List<CName>											Names=new List<CName>();

			Names.Add(new CName(1,"Jenny","Thompson",13));
			Names.Add(new CName(2,"Timmy","Anderson",12));

			CFactoryFunctionService								FactoryFunctionService=new CFactoryFunctionService(Names.ToArray());

			return(FactoryFunctionService);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Pridaju sa CUSTOM SERVICES.
			Services.AddTransient<ITextService1,CTextService1>();
			Services.AddTransient<ITextService2,CTextService2>();
			Services.AddTransient<ITextService3,CTextService3>();
			Services.AddTransient<ITextService4,CTextService4>();
			Services.AddTransient<IChainedService,CChainedService>();

			// !!! Do DEPENDENCY INJECTION FRAMEWORK sa prida implementacia INTERFACE [IInterfaceService].
			Services.AddTransient<IInterfaceService,CInterfaceService>();

			// !!! Do DEPENDENCY INJECTION FRAMEWORK sa prida implementacia BASE CLASS [CBaseClassService].
			Services.AddTransient<CBaseClassService,CDerivedClassService>();

			// !!! Do DEPENDENCY INJECTION FRAMEWORK sa prida konkretny CLASS [CConcreteClassService].
			Services.AddTransient<CConcreteClassService>();

			// !!! Do DEPENDENCY INJECTION FRAMEWORK sa prida implementacia INTERFACE [ILifeCycleTransient].
			Services.AddTransient<ILifeCycleTransient,CLifeCycleTransient>();

			// !!! Do DEPENDENCY INJECTION FRAMEWORK sa prida implementacia INTERFACE [ILifeCycleScoped].
			// !!! SERVICE je SCOPED, co znamena, ze zivotnost vytvorenych OBJECT je zhodna so zivotnostou SCOPE co je standardne spracovanie 1 HTTP REQUEST.
			Services.AddScoped<ILifeCycleScoped,CLifeCycleScoped>();

			// !!! Do DEPENDENCY INJECTION FRAMEWORK sa prida implementacia INTERFACE [ILifeCycleSingleton].
			Services.AddSingleton<ILifeCycleSingleton,CLifeCycleSingleton>();

			// !!! Kedze CLASS NEMA DEFAULT CONSTRUCTOR, je nutne definovat CUSTOM DELEGATE, ktory pre DEPENDENCY INJECTION FRAMEWORK vytvori instanciu tejto CLASS.
			Services.AddTransient<IFactoryFunctionService,CFactoryFunctionService>(CreateFactoryFunctionService);

			// !!! OPAKOVANE sa zaregistruje SERVICE, ktory ma viacero IMPLEMENTATIONS.
			Services.AddTransient<IMultiImplementationService,CMultiImplementationService1>();
			Services.AddTransient<IMultiImplementationService,CMultiImplementationService2>();
			Services.AddTransient<IMultiImplementationService,CMultiImplementationService3>();
			Services.AddTransient<IMultiImplementationService,CMultiImplementationService4>();

			// !!! Zaregistruje sa GENERIC SERVICE, ktory pouziva UNBOUND TYPES. ASP.NET CORE umoznuje na registraciu pouzit IBA NON-GENERIC METHODS INTERFACE [IServiceCollection].
			Services.AddTransient(typeof(IGenericService<>),typeof(CGenericService<>));
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! DEPENDENCY INJECTION je mozne pouzit aj v METHOD [void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment)].
		public void Configure(IApplicationBuilder ApplicationBuilder, IWebHostEnvironment WebHostEnvironment, ITextService1 TextService1)
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

			// !!! Pridaju sa CUSTOM MIDDLEWARES.
			ApplicationBuilder.UseMiddleware<CSimpleMiddleware1>();
			ApplicationBuilder.UseMiddleware<CSimpleMiddleware2>();
			ApplicationBuilder.UseMiddleware<CSimpleMiddleware3>();
			ApplicationBuilder.UseMiddleware<CSimpleMiddleware4>();

			ApplicationBuilder.UseEndpoints(Endpoints =>
			{
				Endpoints.MapControllerRoute("DEFAULT","{Controller}/{Action}");

				// !!! ENDPOINT pouziva SERVICE, ktory ziskal cez DEPENDENCY INJECTION.
				Endpoints.MapGet("/EndpointMiddleware1",async P => await P.Response.WriteAsync($"MESSAGE form SERVICE [{TextService1.GetText()}] !"));
			});
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------