using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingRazorPages
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureCustomWebHostBuilder(IWebHostBuilder WebHostBuilder)
		{
			// !!! Nastavi sa pouzitie KESTREL INTERNAL WEB SERVER.
			WebHostBuilder.UseKestrel();

			// !!! Nastavi sa PORT pre KESTREL INTERNAL WEB SERVER.
			WebHostBuilder.UseUrls("http://localhost:50000");

			// !!! Nastavi sa WORKING DIRECTORY.
			WebHostBuilder.UseContentRoot(Directory.GetCurrentDirectory());

			// !!! Nastavi sa ISS INTEGRATION.
			WebHostBuilder.UseIISIntegration();

			WebHostBuilder.UseStartup<Startup>();
		}
//----------------------------------------------------------------------------------------------------------------------
		private static IHostBuilder CreateCustomHostBuilder(string[] args)
		{
			IHostBuilder										CustomHostBuilder=new HostBuilder();

			// !!!!! Namiesto volania METHOD IHostBuilder.ConfigureWebHostDefaults() je mozne vykonat CUSTOM HOST INTIALIZATION.
			CustomHostBuilder.ConfigureWebHost(ConfigureCustomWebHostBuilder);

			return(CustomHostBuilder);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			// !!! Ked je PROJECT spusteny priamo z VISUAL STUDIO, tak v pripade, ze je uzavtoreny BROWSER, tak sa PROGRAM OKAMZITE UKONCI.
			// !!! Ak je vsak PROJECT spusteny pomocou COMMAND [dotnet run], tak PROGRAM je NEZAVISLY na BROWSER, ktory je treba spusat manualne.

			// !!!!! Nato, aby PROGRAM bezal je NUTNE VYHODIT spustenie IIS EXPRESS, ktore sa robi v MENU [Debug->PROJECT Properties] nastavenim KEY [Profile] na VALUE 'ConfiguringApplications' a nastavenim KEY [Launch] na VALUE 'Project'.
			IHostBuilder										HostBuilder=CreateCustomHostBuilder(args);

			// !!! Vytvori sa HOST.
			// !!!!! HOST MUSI byt UVOLNENY volanim METHOD IDisposable.Dispose() inak PROGRAM ZAMRZNE.
			using(IHost Host=HostBuilder.Build())
			{
				Console.WriteLine("HOST is CONFIGURED !");

				Task											StartTask=Host.StartAsync();

				StartTask.Wait();

				IHostApplicationLifetime						HostApplicationLifetime=(IHostApplicationLifetime) Host.Services.GetService(typeof(IHostApplicationLifetime));

				Console.WriteLine("HOST is RUNNING !");
				Console.ReadLine();

				Console.WriteLine("APPLICATION is STOPPING !");

				// !!! Vykona sa poziadavka na zastavenie ASP.NET CORE APPLICATION.
				HostApplicationLifetime.StopApplication();

				Console.WriteLine("APPLICATION STOPPED !");

				Task											StopTask=Host.StopAsync();

				StopTask.Wait();
			}

			Console.WriteLine("HOST is STOPPED !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------