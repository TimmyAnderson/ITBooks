using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Polly;
using Polly.Registry;
using Polly.Retry;
//----------------------------------------------------------------------------------------------------------------------
namespace PollyClientWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class PollyRetryController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IHttpClientFactory						MHttpClientFactory;
		private readonly ResiliencePipelineProvider<string>		MResiliencePipelineProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PollyRetryController(IHttpClientFactory HttpClientFactory, ResiliencePipelineProvider<string> ResiliencePipelineProvider)
		{
			MHttpClientFactory=HttpClientFactory;
			MResiliencePipelineProvider=ResiliencePipelineProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask OnRetryMethod(OnRetryArguments<HttpResponseMessage> Parameter)
		{
			Outcome<HttpResponseMessage>						Outcome=Parameter.Outcome;
			HttpResponseMessage									TypedResult=Outcome.Result;

			Console.WriteLine($"RETRY ERROR - PARAMETER [{TypedResult}].");

			ValueTask											Result=ValueTask.CompletedTask;

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		private static ValueTask<bool> ShouldHandleMethod(RetryPredicateArguments<HttpResponseMessage> Parameter)
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private async Task<HttpResponseMessage> CallRemoteMethod(CancellationToken Token, string ID)
		{
			HttpClient											Client=MHttpClientFactory.CreateClient();
			string												Address=$"https://localhost:8000/Retry/MyRetryMethod?ID={ID}";

			// !!!!! CANCELLATION TOKEN vytvoreny POLLY PIPELINE sa MUSI pouzit na realizaciu ASYNCHRONOUS METHOD.
			HttpResponseMessage									ResponseMessage=await Client.GetAsync(Address,Token);

			return(ResponseMessage);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena manualne v METHOD.
		[HttpGet(nameof(CallRetryMethod1))]
		public async Task<IActionResult> CallRetryMethod1(string ID, int TimeoutInMS, int WaitTimeoutInMS)
		{
			Console.WriteLine($"RETRY METHOD 1 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Vytvori sa POLLY PIPELINE.
				ResiliencePipelineBuilder<HttpResponseMessage>	PollyPipelineBuilder=new ResiliencePipelineBuilder<HttpResponseMessage>();

				RetryStrategyOptions<HttpResponseMessage>		RetryOptions=new RetryStrategyOptions<HttpResponseMessage>();

				RetryOptions.ShouldHandle=ShouldHandleMethod;
				RetryOptions.MaxRetryAttempts=4;
				RetryOptions.Delay=TimeSpan.FromSeconds(1);
				RetryOptions.MaxDelay=TimeSpan.FromSeconds(10);
				RetryOptions.BackoffType=DelayBackoffType.Constant;
				RetryOptions.OnRetry=OnRetryMethod;

				PollyPipelineBuilder.AddRetry(RetryOptions);

				ResiliencePipeline<HttpResponseMessage>			PollyPipeline=PollyPipelineBuilder.Build();

				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 2 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"RETRY METHOD 1 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"RETRY METHOD 1 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena EXTERNE v externej COFIGURATION.
		[HttpGet(nameof(CallRetryMethod2))]
		public async Task<IActionResult> CallRetryMethod2(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"RETRY METHOD 2 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Ziska sa nakonfigurovana POLLY PIPELINE, ktora ma TIMEOUT definovany na 5 sekund.
				ResiliencePipeline<HttpResponseMessage>			PollyPipeline=MResiliencePipelineProvider.GetPipeline<HttpResponseMessage>(Program.POLLY_RETRY_PIPELINE_NAME);

				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 2 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"RETRY METHOD 2 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"RETRY METHOD 2 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena EXTERNE v externej COFIGURATION.
		[HttpGet(nameof(CallRetryMethod3))]
		public async Task<IActionResult> CallRetryMethod3(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"RETRY METHOD 3 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Vytvori sa POLLY PIPELINE.
				ResiliencePipelineBuilder<HttpResponseMessage>	PollyPipelineBuilder=new ResiliencePipelineBuilder<HttpResponseMessage>();

				RetryStrategyOptions<HttpResponseMessage>		RetryOptions=new RetryStrategyOptions<HttpResponseMessage>();

				RetryOptions.ShouldHandle=ShouldHandleMethod;
				RetryOptions.MaxRetryAttempts=2;
				RetryOptions.Delay=TimeSpan.FromSeconds(1);
				RetryOptions.MaxDelay=TimeSpan.FromSeconds(10);
				RetryOptions.BackoffType=DelayBackoffType.Constant;
				RetryOptions.OnRetry=OnRetryMethod;

				PollyPipelineBuilder.AddRetry(RetryOptions);

				ResiliencePipeline<HttpResponseMessage>			PollyPipeline=PollyPipelineBuilder.Build();

				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 3 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"RETRY METHOD 3 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"RETRY METHOD 3 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------