using System;
using Azure.Monitor.OpenTelemetry.AspNetCore;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using OpenTelemetry;
using OpenTelemetry.Exporter;
using OpenTelemetry.Metrics;
using OpenTelemetry.Resources;
using OpenTelemetry.Trace;
//----------------------------------------------------------------------------------------------------------------------
namespace RemoteWebService
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
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
			Builder.AddService(nameof(RemoteWebService));
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static void ConfigureOpenTelemetryMetrics(MeterProviderBuilder Builder)
		{
			Builder.AddAspNetCoreInstrumentation();

			Builder.AddMeter("Microsoft.AspNetCore.Hosting");
			Builder.AddMeter("Microsoft.AspNetCore.Server.Kestrel");

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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
			WebApplicationBuilder								Builder=WebApplication.CreateBuilder(args);

			Builder.Services.AddControllers();

			Builder.Services.AddEndpointsApiExplorer();
			Builder.Services.AddSwaggerGen();

			// !!! Pridaju sa SERVICES potrebne pre OPEN TELEMETRY.
			OpenTelemetryBuilder								OpenTelemetryBuilder=Builder.Services.AddOpenTelemetry();

			OpenTelemetryBuilder.ConfigureResource(ConfigureOpenTelemetryResource);
			OpenTelemetryBuilder.WithMetrics(ConfigureOpenTelemetryMetrics);

			// !!! Nakonfiguruje sa TRACING.
			OpenTelemetryBuilder.WithTracing(ConfigureOpenTelemetryTracing);

			// !!! Prida sa AZURE APPLICATION INSIGHTS MONITOR.
			// !!!!! V CONFIGURATION FILE [appsettings.json] musi byt nakonfigurovany SETTINGS [APPLICATIONINSIGHTS_CONNECTION_STRING].
			OpenTelemetryBuilder.UseAzureMonitor();

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			Application.UseHttpsRedirection();

			Application.UseAuthorization();

			Application.MapControllers();

			Application.StartAsync().Wait();

			CMenuProgram										Menu=new CMenuProgram();

			Menu.Execute();

			Application.StopAsync().Wait();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------