using System;
using System.Threading;
using System.Threading.RateLimiting;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.RateLimiting;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
//----------------------------------------------------------------------------------------------------------------------
namespace PollyServerWeb
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		public const string										RATE_LIMTER_POLICY_NAME="MY_POLICY";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureFixedWindowRateLimiter(FixedWindowRateLimiterOptions Options)
		{
			Options.PermitLimit=3;
			Options.Window=TimeSpan.FromSeconds(10);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static async ValueTask RejectByRateLimiterCallback(OnRejectedContext Context, CancellationToken Token)
		{
			HttpResponse										Response=Context.HttpContext.Response;

			Response.Headers.ContentType="text/plain";

			await Response.WriteAsync("!!!!! Too many requests. SERVER is OVERLOADED.",Token);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigureRateLimiter(RateLimiterOptions Options)
		{
			Options.AddFixedWindowLimiter(RATE_LIMTER_POLICY_NAME,ConfigureFixedWindowRateLimiter);

			Options.RejectionStatusCode=StatusCodes.Status429TooManyRequests;

			Options.OnRejected=RejectByRateLimiterCallback;
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

			// !!! Nakonfiguruju sa RATE LIMITER POLICIES.
			Builder.Services.AddRateLimiter(ConfigureRateLimiter);

			WebApplication										Application=Builder.Build();

			if (Application.Environment.IsDevelopment()==true)
			{
				Application.UseSwagger();
				Application.UseSwaggerUI();
			}

			Application.UseHttpsRedirection();

			Application.UseAuthorization();

			// !!! Do ASP.NET PIPELINE sa vlozi RATE LIMITER MIDDLEWARE COMPONENT.
			Application.UseRateLimiter();

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