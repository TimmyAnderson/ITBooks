using System;
using System.IO;
using System.Net;
using System.Threading.RateLimiting;
using Client;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Timeouts;
using Microsoft.AspNetCore.RateLimiting;
using Microsoft.AspNetCore.Routing;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Serilog;
using Serilog.Core;
using Serilog.Events;
using Serilog.Formatting.Json;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
    public class Program
    {
//----------------------------------------------------------------------------------------------------------------------
		public const string										MY_RATE_LIMITER_POLICY="MyRateLimiterPolicy";
		public const string										MY_REQUEST_TIMEOUTS_POLICY_1="MyRequestTimeoutsPolicy1";
		public const string										MY_REQUEST_TIMEOUTS_POLICY_2="MyRequestTimeoutsPolicy2";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! RATE LIMITER POLICY sa aplikuje na ENDPOINT.
        private static void MyRateLimiterPolicy(FixedWindowRateLimiterOptions Options)
        {
            Options.PermitLimit=3;
            Options.Window=TimeSpan.FromSeconds(15);
            Options.QueueProcessingOrder=QueueProcessingOrder.OldestFirst;
            Options.QueueLimit=2;			
		}
//----------------------------------------------------------------------------------------------------------------------
        private static void MyRateLimiterConfiguration(RateLimiterOptions Options)
        {
			Options.AddFixedWindowLimiter(MY_RATE_LIMITER_POLICY,MyRateLimiterPolicy);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
        private static void MyRequestTimeoutConfiguration(RequestTimeoutOptions Options)
        {
			Options.AddPolicy(MY_REQUEST_TIMEOUTS_POLICY_1,TimeSpan.FromSeconds(5));
			Options.AddPolicy(MY_REQUEST_TIMEOUTS_POLICY_2,TimeSpan.FromSeconds(9));
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

			Builder.Services.AddRateLimiter(MyRateLimiterConfiguration);

			Builder.Services.AddRequestTimeouts(MyRequestTimeoutConfiguration);

			// !!! Odstrania sa DEFAULT LOGGING PROVIDERS.
			Builder.Logging.ClearProviders();

			Builder.Logging.AddConsole();
			Builder.Logging.AddDebug();

#pragma warning disable CA1416
			// !!! EVENT LOG LOGGING PROVIDER funguje IBA na WINDOWS.
			// !!! Na to aby zapisoval EVENT LOG LOGGING PROVIDER LOG MESSAGES s LOGGING LEVEL [Information], musi byt v CONFIGURATION FILE povoleny tento LOGGING LEVEL.
			//Builder.Logging.AddEventLog();
#pragma warning restore CA1416

			string												SerilogLogFile=Path.Combine(AppDomain.CurrentDomain.BaseDirectory,"MyLogs/MyLog.txt");

			// !!! Vytvori sa LOGGER CONFIGURATION pre SERILOG.
			LoggerConfiguration									SerilogLoggerConfiguration=new LoggerConfiguration();

			// !!! Pouzije sa JSON FORMAT PROVIDER, aby sa spravne zobrazili STRUCTURED LOG MESSAGES.
			JsonFormatter										SerilogFormatter=new JsonFormatter();
			
			SerilogLoggerConfiguration.WriteTo.File(SerilogFormatter,SerilogLogFile,LogEventLevel.Information);

			// !!! Vytvori sa SERILOG LOGGER z LOGGER CONFIGURATION.
			Logger												SerilogLogger=SerilogLoggerConfiguration.CreateLogger();

			Builder.Logging.AddSerilog(SerilogLogger);

			WebApplication										Application=Builder.Build();

			Application.Map("/MyComplexBranch",CPipelineComplexBranch.MyComplexBranch);

			Application.Map("/BranchWithUseWhen",CPipelineBranchWithUseWhen.BranchWithUseWhen);

			Application.Map("/BranchWithMapWhen",CPipelineBranchWithMapWhen.BranchWithMapWhen);

			// !!! Vykona SHORT CIRCUIT REQUEST PIPELINE.
			Application.MapGet("MyShortCircuit1",CPipelineShortCircuitsMiddlewareComponent.ShortCircuitsMiddlewareComponent).ShortCircuit();

			// !!! Vykona SHORT CIRCUIT REQUEST PIPELINE.
			Application.MapShortCircuit((int)HttpStatusCode.Ambiguous,"MyShortCircuit2");

			// !!! Prida sa CUSTOM MIDDLEWARE COMPONENT CLASS do REQUEST PIPELINE.
			Application.UseMyCustomMiddlewareClasses();

			// !!! Do MAIN BRANCH sa prida CUSTOM MIDDLEWARE COMPONENT.
			Application.Use(CPipelineMiddlewareInMainBranch.MyMiddlewareInMainBranch);

            if (Application.Environment.IsDevelopment()==true)
            {
                Application.UseSwagger();
                Application.UseSwaggerUI();
            }

            Application.UseHttpsRedirection();

            Application.UseAuthorization();

			Application.UseRateLimiter();

			Application.UseRequestTimeouts();

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