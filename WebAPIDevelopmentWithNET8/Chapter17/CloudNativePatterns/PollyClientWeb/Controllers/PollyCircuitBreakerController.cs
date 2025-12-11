using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Polly;
using Polly.CircuitBreaker;
using Polly.Registry;
//----------------------------------------------------------------------------------------------------------------------
namespace PollyClientWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class PollyCircuitBreakerController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IHttpClientFactory						MHttpClientFactory;
		private readonly ResiliencePipelineProvider<string>		MResiliencePipelineProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PollyCircuitBreakerController(IHttpClientFactory HttpClientFactory, ResiliencePipelineProvider<string> ResiliencePipelineProvider)
		{
			MHttpClientFactory=HttpClientFactory;
			MResiliencePipelineProvider=ResiliencePipelineProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask<bool> ShouldHandleMethod(CircuitBreakerPredicateArguments<HttpResponseMessage> Parameter)
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private async Task<HttpResponseMessage> CallRemoteMethod(CancellationToken Token, string ID)
		{
			HttpClient											Client=MHttpClientFactory.CreateClient();
			string												Address=$"https://localhost:8000/CircuitBreaker/MyCircuitBreakerMethod?ID={ID}";

			// !!!!! CANCELLATION TOKEN vytvoreny POLLY PIPELINE sa MUSI pouzit na realizaciu ASYNCHRONOUS METHOD.
			HttpResponseMessage									ResponseMessage=await Client.GetAsync(Address,Token);

			return(ResponseMessage);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena manualne v METHOD.
		[HttpGet(nameof(CircuitBreakerMethod1))]
		public async Task<IActionResult> CircuitBreakerMethod1(string ID, int NumberOfRequests, int PauseInSeconds)
		{
			Console.WriteLine($"CIRCUIT BREAKER METHOD 1 STARTED. ID [{ID}].");

			IActionResult										Result;

			// !!! Vytvori sa POLLY PIPELINE.
			ResiliencePipelineBuilder<HttpResponseMessage>		PollyPipelineBuilder=new ResiliencePipelineBuilder<HttpResponseMessage>();

			CircuitBreakerStrategyOptions<HttpResponseMessage>	Options=new CircuitBreakerStrategyOptions<HttpResponseMessage>();

			Options.ShouldHandle=ShouldHandleMethod;
			Options.FailureRatio=0.5;
			Options.SamplingDuration=TimeSpan.FromSeconds(5);
			Options.MinimumThroughput=3;
			Options.BreakDuration=TimeSpan.FromSeconds(6);
			Options.OnOpened=OnOpenedMethod;
			Options.OnClosed=OnClosedMethod;

			PollyPipelineBuilder.AddCircuitBreaker<HttpResponseMessage>(Options);

			ResiliencePipeline<HttpResponseMessage>				PollyPipeline=PollyPipelineBuilder.Build();
			StringBuilder										SB=new StringBuilder();

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				int												CommandIndex=(Index+1);

				try
				{
					HttpResponseMessage							ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

					ResponseMessage.EnsureSuccessStatusCode();

					string										RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

					string										LocalContent=$"{CommandIndex} - TIME [{DateTime.Now}] - METHOD 1 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

					if (SB.Length>0)
					{
						SB.AppendLine();
					}

					SB.Append(LocalContent);
				}
				catch(Exception E)
				{
					Console.WriteLine($"CIRCUIT BREAKER 1 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

					if (SB.Length>0)
					{
						SB.AppendLine();
					}

					string										LocalContent=$"{CommandIndex} - EXCEPTION [{E.Message}].";

					SB.Append(LocalContent);
				}

				await Task.Delay(PauseInSeconds*1000);
			}

			string												Content=SB.ToString();

			Result=Ok(Content);

			Console.WriteLine($"CIRCUIT BREAKER 1 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena EXTERNE v externej COFIGURATION.
		[HttpGet(nameof(CircuitBreakerMethod2))]
		public async Task<IActionResult> CircuitBreakerMethod2(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"CIRCUIT BREAKER METHOD 2 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Ziska sa nakonfigurovana POLLY PIPELINE, ktora ma TIMEOUT definovany na 5 sekund.
				ResiliencePipeline<HttpResponseMessage>			PollyPipeline=MResiliencePipelineProvider.GetPipeline<HttpResponseMessage>(Program.POLLY_CIRCUIT_BREAKER_PIPELINE_NAME);

				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 2 - TIME [{DateTime.Now}] - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"CIRCUIT BREAKER 2 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"CIRCUIT BREAKER 2 FINISHED. ID [{ID}].");

			return(Result);

		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------