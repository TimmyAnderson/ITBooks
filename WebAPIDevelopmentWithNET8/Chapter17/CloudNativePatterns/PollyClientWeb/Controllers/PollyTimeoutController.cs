using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Polly;
using Polly.Registry;
//----------------------------------------------------------------------------------------------------------------------
namespace PollyClientWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class PollyTimeoutController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IHttpClientFactory						MHttpClientFactory;
		private readonly ResiliencePipelineProvider<string>		MResiliencePipelineProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PollyTimeoutController(IHttpClientFactory HttpClientFactory, ResiliencePipelineProvider<string> ResiliencePipelineProvider)
		{
			MHttpClientFactory=HttpClientFactory;
			MResiliencePipelineProvider=ResiliencePipelineProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private async Task<HttpResponseMessage> CallRemoteMethod(CancellationToken Token, string ID, int TimeoutInMS)
		{
			HttpClient											Client=MHttpClientFactory.CreateClient();
			string												Address=$"https://localhost:8000/Timeout/SlowMethod?ID={ID}&TimeoutInMS={TimeoutInMS}";

			// !!!!! CANCELLATION TOKEN vytvoreny POLLY PIPELINE sa MUSI pouzit na realizaciu ASYNCHRONOUS METHOD.
			HttpResponseMessage									ResponseMessage=await Client.GetAsync(Address,Token);

			return(ResponseMessage);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD nepouziva POLLY.
		[HttpGet(nameof(CallSlowMethod1))]
		public async Task<IActionResult> CallSlowMethod1(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"SLOW METHOD 1 STARTED. ID [{ID}].");

			HttpClient											Client=MHttpClientFactory.CreateClient();
			string												Address=$"https://localhost:8000/Timeout/SlowMethod?ID={ID}&TimeoutInMS={TimeoutInMS}";

			HttpResponseMessage									ResponseMessage=await Client.GetAsync(Address);

			ResponseMessage.EnsureSuccessStatusCode();

			string												RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

			string												Content=$"METHOD 1 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";
			IActionResult										Result=Ok(Content);

			Console.WriteLine($"SLOW METHOD 1 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena manualne v METHOD.
		[HttpGet(nameof(CallSlowMethod2))]
		public async Task<IActionResult> CallSlowMethod2(string ID, int TimeoutInMS, int WaitTimeoutInMS)
		{
			Console.WriteLine($"SLOW METHOD 2 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Vytvori sa POLLY PIPELINE.
				ResiliencePipelineBuilder						PollyPipelineBuilder=new ResiliencePipelineBuilder();
				TimeSpan										WaitTimeSpan=TimeSpan.FromMilliseconds(WaitTimeoutInMS);

				PollyPipelineBuilder.AddTimeout(WaitTimeSpan);
				
				ResiliencePipeline								PollyPipeline=PollyPipelineBuilder.Build();

				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID,TimeoutInMS));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 2 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"SLOW METHOD 2 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"SLOW METHOD 2 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena EXTERNE v externej COFIGURATION.
		[HttpGet(nameof(CallSlowMethod3))]
		public async Task<IActionResult> CallSlowMethod3(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"SLOW METHOD 3 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Ziska sa nakonfigurovana POLLY PIPELINE, ktora ma TIMEOUT definovany na 5 sekund.
				ResiliencePipeline								PollyPipeline=MResiliencePipelineProvider.GetPipeline(Program.POLLY_TIMEOUT_PIPELINE_NAME);
				
				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID,TimeoutInMS));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 3 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"SLOW METHOD 3 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"SLOW METHOD 3 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------