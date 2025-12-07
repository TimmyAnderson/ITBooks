using System;
using System.Text;
using Azure.Monitor.OpenTelemetry.AspNetCore;
using FluentValidation;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Diagnostics.HealthChecks;
using Microsoft.AspNetCore.HttpLogging;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using OpenTelemetry;
using OpenTelemetry.Exporter;
using OpenTelemetry.Metrics;
using OpenTelemetry.Resources;
using OpenTelemetry.Trace;
//--------------------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureDbContext(DbContextOptionsBuilder OptionsBuilder, string ConnectionString)
		{
			OptionsBuilder.UseSqlite(ConnectionString);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOpenTelemetryOtlpExporter(OtlpExporterOptions Options)
		{
			// !!! OLTP DATA sa exportuju na danu URL.
			// JAEGER COLLECTOR zodpovedny za zber TRACES vystavuje GPRC ENDPOINT na URL [localhost:4317] a HTTP ENDPOINT na URL [localhost:4318].
            Options.Endpoint=new Uri("http://localhost:4317");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOpenTelemetryResource(ResourceBuilder Builder)
		{
			Builder.AddService(nameof(MyWebProject));
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOpenTelemetryMetrics(MeterProviderBuilder Builder)
		{
			Builder.AddMeter("Microsoft.AspNetCore.Hosting");
			Builder.AddMeter("Microsoft.AspNetCore.Server.Kestrel");

			// !!! Zaregistruje sa CUSTOM METER vytvoreny v CLASS [CMyObservabilityService].
			Builder.AddMeter(CMyObservabilityService.METER_NAME);

			Builder.AddAspNetCoreInstrumentation();
			Builder.AddConsoleExporter();

			// !!! Prida sa PROMETHEUS EXPORTER.
			Builder.AddPrometheusExporter();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOpenTelemetryTracing(TracerProviderBuilder Builder)
		{
			Builder.AddAspNetCoreInstrumentation();
            
			Builder.AddHttpClientInstrumentation();

			Builder.AddConsoleExporter();

			Builder.AddOtlpExporter(ConfigureOpenTelemetryOtlpExporter);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureHttpLogging(HttpLoggingOptions Options)
		{
			// !!! Definuju sa FIELD HTTP REQUEST MESSAGES a HTTP RESPONSE MESSAGES, ktore budu LOGGED.
			Options.LoggingFields=HttpLoggingFields.All;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			const string										TAG_NAME_1="TAG_1";
			const string										TAG_NAME_2="TAG_2";
			const string										TAG_NAME_DB="TAG_DB";

			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			// !!! Zaregistruje sa CUSTOM VALIDATOR pre FLUENT VALIDATION LIBRARY.
			Builder.Services.AddScoped<IValidator<CFluentName1>,CFluentNameValidator1>();

			// !!! Zaregistruju sa vsetky CUSTOM VALIDATORS pre FLUENT VALIDATION LIBRARY v ASSEMBLY kde sa nachadza VALIDATOR [CFluentNameValidator1].
			Builder.Services.AddValidatorsFromAssemblyContaining<CFluentNameValidator1>();

			Builder.Services.AddHttpLogging(ConfigureHttpLogging);

			string												ConnectionString=Builder.Configuration.GetConnectionString("MyConnection");

			// !!! DB CONTEXT sa prida do DEPENDENCY INJECTION CONTAINER.
			Builder.Services.AddDbContext<CDBContext>(P => ConfigureDbContext(P,ConnectionString));

			// !!! Pridaju sa SERVICES potrebne pre HEALTH CHECKS.
			IHealthChecksBuilder								HealthChecksBuilder=Builder.Services.AddHealthChecks();

			HealthChecksBuilder.AddCheck<CMyHealthCheck1>("MyHealthCheck1",null,new string[]{TAG_NAME_1});
			HealthChecksBuilder.AddCheck<CMyHealthCheck2>("MyHealthCheck2",null,new string[]{TAG_NAME_1});
			HealthChecksBuilder.AddCheck<CMyHealthCheck3>("MyHealthCheck3",null,new string[]{TAG_NAME_2});
			HealthChecksBuilder.AddCheck<CMyHealthCheck4>("MyHealthCheck4",null,new string[]{TAG_NAME_2});

			// !!! Pridaju sa DATABASE HEALTH CHECK.
			HealthChecksBuilder.AddDbContextCheck<CDBContext>("DatabaseCheck",null,new string[]{TAG_NAME_DB});

			// !!! Zaregistruje sa CUSTOM OBSERBAILITY SERVICE.
			Builder.Services.AddSingleton<CMyObservabilityService>();

			// !!! Pridaju sa SERVICES potrebne pre OPEN TELEMETRY.
			OpenTelemetryBuilder								OpenTelemetryBuilder=Builder.Services.AddOpenTelemetry();

			OpenTelemetryBuilder.ConfigureResource(ConfigureOpenTelemetryResource);
			OpenTelemetryBuilder.WithMetrics(ConfigureOpenTelemetryMetrics);

			// !!! Nakonfiguruje sa TRACING.
			OpenTelemetryBuilder.WithTracing(ConfigureOpenTelemetryTracing);

			// !!! Prida sa AZURE APPLICATION INSIGHTS MONITOR.
			// !!!!! V CONFIGURATION FILE [appsettings.json] musi byt nakonfigurovany SETTINGS [APPLICATIONINSIGHTS_CONNECTION_STRING].
			OpenTelemetryBuilder.UseAzureMonitor();

			// !!! Pridaju sa SERVICES potrebne pre TYPED HTTP CLIENT.
			Builder.Services.AddHttpClient<CMyTypedHttpClient>();

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();

				// !!! Zaregistruje sa CUSTOM CONTROLLER ACTION METHOD pre DEVELOPMENT ENVIRONMENTS.
				Application.UseExceptionHandler("/MyErrorHandler/HandleErrorDevelopment");
			}
			else
			{
				// !!! Zaregistruje sa CUSTOM CONTROLLER ACTION METHOD pre PRODUCTION ENVIRONMENT.
				Application.UseExceptionHandler("/MyErrorHandler/HandleErrorProduction");
			}

			Application.UseHttpsRedirection();

			Application.UseAuthorization();

			// !!! Do ASP.NET PIPELINE sa vlozi HTTP LOGGING MIDDLEWARE COMPONENT.
			Application.UseHttpLogging();

			HealthCheckOptions									HealthCheckOptionsTag1=new HealthCheckOptions();

			HealthCheckOptionsTag1.Predicate=P => P.Tags.Contains(TAG_NAME_1);

			// !!! Pridaju sa vsetky HEALTH CHECK, ktore maju nastaveny TAG [TAG_1].
			// !!! HEALTH CHECK vrati HEALTHY, ak vsetky CUSTOM HEALTH CHECKS vratia status HEALTHY.
			Application.MapHealthChecks("/health/tag1",HealthCheckOptionsTag1);

			HealthCheckOptions									HealthCheckOptionsTag2=new HealthCheckOptions();

			HealthCheckOptionsTag2.Predicate=P => P.Tags.Contains(TAG_NAME_2);

			// !!! Pridaju sa vsetky HEALTH CHECK, ktore maju nastaveny TAG [TAG_2].
			// !!! HEALTH CHECK vrati HEALTHY, ak vsetky CUSTOM HEALTH CHECKS vratia status HEALTHY.
			Application.MapHealthChecks("/health/tag2",HealthCheckOptionsTag2);

			HealthCheckOptions									HealthCheckOptionsTagDB=new HealthCheckOptions();

			HealthCheckOptionsTagDB.Predicate=P => P.Tags.Contains(TAG_NAME_DB);

			// !!! Pridaju sa vsetky HEALTH CHECK, ktore maju nastaveny TAG [TAG_DB].
			Application.MapHealthChecks("/health/tagDB",HealthCheckOptionsTagDB);

			// !!! Prida sa PROMETHEUS SCRAPING ENDPOINT.
			Application.MapPrometheusScrapingEndpoint();

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