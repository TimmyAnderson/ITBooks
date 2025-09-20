using System;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Configuration.AzureAppConfiguration;
using Microsoft.FeatureManagement;
//--------------------------------------------------------------------------------------------------------------------------------
namespace AzureAppConfiguration
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private static readonly string							CONNECTION_STRING_KEY_NAME="AzureAppConfigurationConnectionString";
		private static readonly string							SENTINEL_KEY_NAME="MySentinel";
		private static readonly TimeSpan						REFRESH_INTERVAL=TimeSpan.FromSeconds(60);
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureAzureAppConfigurationRefresh(AzureAppConfigurationRefreshOptions Options)
		{
			// !!!!! Nastavi sa NAME SENTINEL KEY VALUE.
			Options.Register(SENTINEL_KEY_NAME,true);

			// !!!!! Nastavi sa REFRESH INTERVAL, po akom case je VALUE SENTINEL KEY VALUE na detekciu zmeny CONFIGURATION neplatna a pri vykonani dalsie REQUEST sa opatovne nacita.
			Options.SetRefreshInterval(REFRESH_INTERVAL);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureAzureAppConfiguration(AzureAppConfigurationOptions Options, string AzureAppConfigurationConnectionString)
		{
			// !!!!! Vsetky CONFIGURATIONS sa nacitaju z AZURE APP CONFIGURATION.
			Options.Connect(AzureAppConfigurationConnectionString);

			// !!!!! Definuje sa ktore KEY VALUES sa maju citat.
			Options.Select(KeyFilter.Any,LabelFilter.Null);

			// !!!!! Nakonfiguruje sa dynamicke nacitavanie CONFIGURATIONS.
			Options.ConfigureRefresh(ConfigureAzureAppConfigurationRefresh);

			// !!!!! Povoli sa pouzitie FEATURE FLAGS.
			Options.UseFeatureFlags();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigurePipelineBranch1(IApplicationBuilder Builder)
		{
			Builder.UseMiddleware<CMyMiddleware3>();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigurePipelineBranch2(IApplicationBuilder Builder)
		{
			Builder.UseMiddleware<CMyMiddleware4>();
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			// !!!!! VALUE sa ziskava pomocou COMMAND [az appconfig credential list --name MyConfigurationTA76 --resource-group Chapter09].
			string												AzureAppConfigurationConnectionString=Builder.Configuration[CONNECTION_STRING_KEY_NAME];

			// !!!!! METHOD prida vsetky CONFIGURATIONS, ktore vycita z AZURE APP CONFIGURATION.
			Builder.Configuration.AddAzureAppConfiguration(P => ConfigureAzureAppConfiguration(P,AzureAppConfigurationConnectionString));

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			// !!!! Pridaju sa SERVICES potrebne pracu s AZURE APP CONFIGURATION.
			Builder.Services.AddAzureAppConfiguration();

			Builder.Services.AddControllersWithViews();

			// !!!!! Nacita sa SECTION z AZURE APP CONFIGURATION.
			IConfigurationSection								ConfigurationSection=Builder.Configuration.GetSection("complexConfiguration");

			// !!!!! Vytvori sa CONFIGURATION TYPE [CComplexConfiguration] z KEY VALUES ulozenych v AZURE APP CONFIGURATION.
			Builder.Services.Configure<CComplexConfiguration>(ConfigurationSection);

			// !!! Pridaju sa SERVICES, implementujuce FEATURE FLAGS.
			Builder.Services.AddFeatureManagement();

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			// !!!!! MIDDLEWARE COMPONENT sa pouzije podmienecne podla toho ci je nastaveny FEATURE FLAG.
			Application.UseMiddlewareForFeature<CMyMiddleware1>("MyFeature7");

			// !!!!! MIDDLEWARE COMPONENT sa pouzije podmienecne podla toho ci je nastaveny FEATURE FLAG.
			Application.UseMiddlewareForFeature<CMyMiddleware2>("MyFeature8");

			// !!!!! MIDDLEWARE COMPONENT sa pouzije podmienecne podla toho ci je nastaveny FEATURE FLAG.
			Application.UseForFeature("MyFeature9",ConfigurePipelineBranch1);

			// !!!!! MIDDLEWARE COMPONENT sa pouzije podmienecne podla toho ci je nastaveny FEATURE FLAG.
			Application.UseForFeature("MyFeature10",ConfigurePipelineBranch2);

			// !!!!! MIDDLEWARE sluzi pre detekciu zmien v AZURE APP CONFIGURATION.
			// !!!!! MIDDLEWARE kontroluje ci SENTINEL KEY VALUE nie je EXPIRED, a ak ano, nacita jeho VALUE z AZURE APP CONFIGURATION.
			Application.UseAzureAppConfiguration();

			Application.UseHttpsRedirection();

			Application.UseRouting();

			Application.UseAuthorization();

			Application.MapControllerRoute(name: "default", pattern: "{controller=Home}/{action=Index}");

			Application.MapControllers();

			Application.StartAsync().Wait();

			CMenuProgram										Menu=new CMenuProgram();

			Menu.Execute();

			Application.StopAsync().Wait();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------