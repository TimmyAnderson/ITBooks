using System;
using System.Net.Http;
using System.Threading.RateLimiting;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Polly;
using Polly.CircuitBreaker;
using Polly.DependencyInjection;
using Polly.Retry;
//----------------------------------------------------------------------------------------------------------------------
namespace PollyClientWeb
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		public const string										POLLY_TIMEOUT_PIPELINE_NAME="MY_TIMEOUT";
		public const string										POLLY_RATE_LIMITER_FIXED_PIPELINE_NAME="MY_RATE_LIMITER_FIXED";
		public const string										POLLY_RATE_LIMITER_SLIDING_PIPELINE_NAME="MY_RATE_LIMITER_SLIDING";
		public const string										POLLY_RETRY_PIPELINE_NAME="MY_RETRY";
		public const string										POLLY_CIRCUIT_BREAKER_PIPELINE_NAME="MY_CIRCUIT_BREAKER";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigurePollyPipelineTimeout5Seconds(ResiliencePipelineBuilder PollyPipelineBuilder)
		{
			TimeSpan											WaitTimeSpan=TimeSpan.FromMilliseconds(5000);

			PollyPipelineBuilder.AddTimeout(WaitTimeSpan);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigurePollyPipelineRateLimiterFixed(ResiliencePipelineBuilder PollyPipelineBuilder, AddResiliencePipelineContext<string> Context)
		{
			FixedWindowRateLimiterOptions						Options=new FixedWindowRateLimiterOptions();

			Options.PermitLimit=3;
			Options.Window=TimeSpan.FromSeconds(20);

			FixedWindowRateLimiter								TimeLimiter=new FixedWindowRateLimiter(Options);

			PollyPipelineBuilder.AddRateLimiter(TimeLimiter);

			// !!!!! Instancia CLASS [FixedWindowRateLimiter] MUSI byt uvolnena volanim METHOD [void IDisposable.Dispose()].
			Context.OnPipelineDisposed(() => TimeLimiter.Dispose());
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigurePollyPipelineRateLimiterSliding(ResiliencePipelineBuilder PollyPipelineBuilder, AddResiliencePipelineContext<string> Context)
		{
			SlidingWindowRateLimiterOptions						Options=new SlidingWindowRateLimiterOptions();

			Options.PermitLimit=3;
			Options.Window=TimeSpan.FromSeconds(20);
			Options.SegmentsPerWindow=2;

			SlidingWindowRateLimiter							TimeLimiter=new SlidingWindowRateLimiter(Options);

			PollyPipelineBuilder.AddRateLimiter(TimeLimiter);

			// !!!!! Instancia CLASS [SlidingWindowRateLimiter] MUSI byt uvolnena volanim METHOD [void IDisposable.Dispose()].
			Context.OnPipelineDisposed(() => TimeLimiter.Dispose());
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask OnRetryMethod(OnRetryArguments<HttpResponseMessage> Parameter)
		{
			Outcome<HttpResponseMessage>						Outcome=Parameter.Outcome;
			HttpResponseMessage									TypedResult=Outcome.Result;

			Console.WriteLine($"GLOBAL RETRY ERROR - PARAMETER [{TypedResult}].");

			ValueTask											Result=ValueTask.CompletedTask;

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask<bool> RetryShouldHandleMethod(RetryPredicateArguments<HttpResponseMessage> Parameter)
		{
			Outcome<HttpResponseMessage>						Outcome=Parameter.Outcome;
			HttpResponseMessage									TypedResult=Outcome.Result;
			bool												ShouldHandle=false;

			if (TypedResult!=null)
			{
				int												StatusCode=(int) TypedResult.StatusCode;

				if (StatusCode==451)
				{
					ShouldHandle=true;
				}
				else if (StatusCode==452)
				{
					ShouldHandle=true;
				}
			}

			ValueTask<bool>										Result=new ValueTask<bool>(ShouldHandle);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigurePollyPipelineRetry(ResiliencePipelineBuilder<HttpResponseMessage> PollyPipelineBuilder, AddResiliencePipelineContext<string> Context)
		{
			RetryStrategyOptions<HttpResponseMessage>			RetryOptions=new RetryStrategyOptions<HttpResponseMessage>();

			RetryOptions.ShouldHandle=RetryShouldHandleMethod;
			RetryOptions.MaxRetryAttempts=4;
			RetryOptions.Delay=TimeSpan.FromSeconds(1);
			RetryOptions.MaxDelay=TimeSpan.FromSeconds(10);
			RetryOptions.BackoffType=DelayBackoffType.Constant;
			RetryOptions.OnRetry=OnRetryMethod;

			PollyPipelineBuilder.AddRetry(RetryOptions);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask<bool> CircuitBreakerShouldHandleMethod(CircuitBreakerPredicateArguments<HttpResponseMessage> Parameter)
		{
			Outcome<HttpResponseMessage>						Outcome=Parameter.Outcome;
			HttpResponseMessage									TypedResult=Outcome.Result;
			bool												ShouldHandle=false;

			if (TypedResult!=null)
			{
				int												StatusCode=(int) TypedResult.StatusCode;

				if (StatusCode==451)
				{
					ShouldHandle=true;
				}
				else if (StatusCode==452)
				{
					ShouldHandle=true;
				}
			}

			ValueTask<bool>										Result=new ValueTask<bool>(ShouldHandle);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask OnOpenedMethod(OnCircuitOpenedArguments<HttpResponseMessage> Parameter)
		{
			Outcome<HttpResponseMessage>						Outcome=Parameter.Outcome;
			HttpResponseMessage									TypedResult=Outcome.Result;

			Console.WriteLine($"CIRCUIT BREAKER is OPENED. STATUS [{TypedResult?.StatusCode}].");

			ValueTask											Result=ValueTask.CompletedTask;

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask OnClosedMethod(OnCircuitClosedArguments<HttpResponseMessage> Parameter)
		{
			Outcome<HttpResponseMessage>						Outcome=Parameter.Outcome;
			HttpResponseMessage									TypedResult=Outcome.Result;

			Console.WriteLine($"CIRCUIT BREAKER is CLOSED. STATUS [{TypedResult?.StatusCode}].");

			ValueTask											Result=ValueTask.CompletedTask;

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static void ConfigurePollyPipelineCircuitBreaker(ResiliencePipelineBuilder<HttpResponseMessage> PollyPipelineBuilder, AddResiliencePipelineContext<string> Context)
		{
			CircuitBreakerStrategyOptions<HttpResponseMessage>	Options=new CircuitBreakerStrategyOptions<HttpResponseMessage>();

			Options.ShouldHandle=CircuitBreakerShouldHandleMethod;
			Options.FailureRatio=0.5;
			Options.SamplingDuration=TimeSpan.FromSeconds(5);
			Options.MinimumThroughput=3;
			Options.BreakDuration=TimeSpan.FromSeconds(6);
			Options.OnOpened=OnOpenedMethod;
			Options.OnClosed=OnClosedMethod;

			PollyPipelineBuilder.AddCircuitBreaker<HttpResponseMessage>(Options);
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

			// !!! Prida sa HTTP CLIENT.
			Builder.Services.AddHttpClient();

			// !!! Prida sa POLLY PIPELINE pre TIMEOUT.
			Builder.Services.AddResiliencePipeline(POLLY_TIMEOUT_PIPELINE_NAME,ConfigurePollyPipelineTimeout5Seconds);

			// !!! Prida sa POLLY PIPELINE pre RATE_LIMITER s FIXED WINDOW.
			Builder.Services.AddResiliencePipeline(POLLY_RATE_LIMITER_FIXED_PIPELINE_NAME,ConfigurePollyPipelineRateLimiterFixed);

			// !!! Prida sa POLLY PIPELINE pre RATE_LIMITER so SIDING WINDOW.
			Builder.Services.AddResiliencePipeline(POLLY_RATE_LIMITER_SLIDING_PIPELINE_NAME,ConfigurePollyPipelineRateLimiterSliding);

			// !!! Prida sa POLLY PIPELINE pre RETRY.
			Builder.Services.AddResiliencePipeline<string,HttpResponseMessage>(POLLY_RETRY_PIPELINE_NAME,ConfigurePollyPipelineRetry);

			// !!! Prida sa POLLY PIPELINE pre CIRCUIT BREAKER.
			Builder.Services.AddResiliencePipeline<string,HttpResponseMessage>(POLLY_CIRCUIT_BREAKER_PIPELINE_NAME,ConfigurePollyPipelineCircuitBreaker);

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