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
using ModelValidation.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelValidation
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
		private string ProcessSetValueMustNotBeNullAccessor(string Value)
		{
			return("PLEASE ENTER VALUE !");
		}
//----------------------------------------------------------------------------------------------------------------------
		private void ConfigureMvcOptions(MvcOptions Options)
		{
			// !!! Pri generovani VALIDATION ERROR (VALUE NESMIE byt NULL) sa zavola CUSTOM METHOD, ktora moze vratit CUSTOM ERROR MESSAGE.
			Options.ModelBindingMessageProvider.SetValueMustNotBeNullAccessor(ProcessSetValueMustNotBeNullAccessor);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void ConfigureServices(IServiceCollection Services)
		{
			Services.AddControllersWithViews();

			// !!! Prida SERVICE, ktory umoznuje pouzitie RAZOR PAGES.
			Services.AddRazorPages();

			Services.AddMvc().AddMvcOptions(ConfigureMvcOptions);

			CChildProvider										ChildProvider=new CChildProvider();

			ChildProvider.AddChild(new CChild(1,"Timmy","Anderson",12,ESex.Male));
			ChildProvider.AddChild(new CChild(2,"Jenny","Thompson",13,ESex.Female));

			Services.AddSingleton<IChildProvider>(ChildProvider);

			CChildAutoValidationProvider						ChildAutoValidationProvider=new CChildAutoValidationProvider();

			ChildAutoValidationProvider.AddChild(new CChildAutoValidation(1,"Timmy","Anderson",12,ESex.Male));
			ChildAutoValidationProvider.AddChild(new CChildAutoValidation(2,"Jenny","Thompson",13,ESex.Female));

			Services.AddSingleton<IChildAutoValidationProvider>(ChildAutoValidationProvider);

			CChildRemoteValidationProvider						ChildRemoteValidationProvider=new CChildRemoteValidationProvider();

			ChildRemoteValidationProvider.AddChild(new CChildRemoteValidation(1,"Timmy","Anderson",12,ESex.Male));
			ChildRemoteValidationProvider.AddChild(new CChildRemoteValidation(2,"Jenny","Thompson",13,ESex.Female));

			Services.AddSingleton<IChildRemoteValidationProvider>(ChildRemoteValidationProvider);

			CChildRemoteValidationRazorPageProvider				ChildRemoteValidationRazorPageProvider=new CChildRemoteValidationRazorPageProvider();

			ChildRemoteValidationRazorPageProvider.AddChild(new CChildRemoteValidationRazorPage(1,"Timmy","Anderson",12,ESex.Male));
			ChildRemoteValidationRazorPageProvider.AddChild(new CChildRemoteValidationRazorPage(2,"Jenny","Thompson",13,ESex.Female));

			Services.AddSingleton<IChildRemoteValidationRazorPageProvider>(ChildRemoteValidationRazorPageProvider);
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