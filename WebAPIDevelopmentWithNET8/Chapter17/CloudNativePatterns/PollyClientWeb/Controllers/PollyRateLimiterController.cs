using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.RateLimiting;
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
	public class PollyRateLimiterController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IHttpClientFactory						MHttpClientFactory;
		private readonly ResiliencePipelineProvider<string>		MResiliencePipelineProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public PollyRateLimiterController(IHttpClientFactory HttpClientFactory, ResiliencePipelineProvider<string> ResiliencePipelineProvider)
		{
			MHttpClientFactory=HttpClientFactory;
			MResiliencePipelineProvider=ResiliencePipelineProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private async Task<HttpResponseMessage> CallRemoteMethod(CancellationToken Token, string ID)
		{
			HttpClient											Client=MHttpClientFactory.CreateClient();
			string												Address=$"https://localhost:8000/RateLimiter/MyRateLimterMethod?ID={ID}";

			// !!!!! CANCELLATION TOKEN vytvoreny POLLY PIPELINE sa MUSI pouzit na realizaciu ASYNCHRONOUS METHOD.
			HttpResponseMessage									ResponseMessage=await Client.GetAsync(Address,Token);

			return(ResponseMessage);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena manualne v METHOD.
		[HttpGet(nameof(RateLimiterMethod1))]
		public async Task<IActionResult> RateLimiterMethod1(string ID, int NumberOfRequests, int PauseInSeconds, int NumberOfBatches)
		{
			Console.WriteLine($"RATE LIMITER METHOD 1 STARTED. ID [{ID}].");

			IActionResult										Result;

			// !!! Vytvori sa POLLY PIPELINE.
			ResiliencePipelineBuilder							PollyPipelineBuilder=new ResiliencePipelineBuilder();

			FixedWindowRateLimiterOptions						Options=new FixedWindowRateLimiterOptions();

			Options.PermitLimit=3;
			Options.Window=TimeSpan.FromSeconds(20);

			using(FixedWindowRateLimiter TimeLimiter=new FixedWindowRateLimiter(Options))
			{
				PollyPipelineBuilder.AddRateLimiter(TimeLimiter);

				ResiliencePipeline								PollyPipeline=PollyPipelineBuilder.Build();
				StringBuilder									SB=new StringBuilder();

				for(int Batch=0;Batch<NumberOfBatches;Batch++)
				{
					for(int Index=0;Index<NumberOfRequests;Index++)
					{
						int										CommandIndex=((NumberOfRequests*Batch)+Index+1);

						try
						{
							HttpResponseMessage					ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

							ResponseMessage.EnsureSuccessStatusCode();

							string								RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

							string								LocalContent=$"{CommandIndex} - METHOD 1 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

							if (SB.Length>0)
							{
								SB.AppendLine();
							}

							SB.Append(LocalContent);
						}
						catch(Exception E)
						{
							Console.WriteLine($"RATE LIMITER 1 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

							if (SB.Length>0)
							{
								SB.AppendLine();
							}

							string								LocalContent=$"{CommandIndex} - EXCEPTION [{E.Message}].";

							SB.Append(LocalContent);
						}
					}

					await Task.Delay(PauseInSeconds*1000);
				}

				string											Content=SB.ToString();

				Result=Ok(Content);
			}

			Console.WriteLine($"RATE LIMITER 1 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena manualne v METHOD.
		[HttpGet(nameof(RateLimiterMethod2))]
		public async Task<IActionResult> RateLimiterMethod2(string ID, int NumberOfRequests, int PauseInSeconds, int NumberOfBatches)
		{
			Console.WriteLine($"RATE LIMITER METHOD 2 STARTED. ID [{ID}].");

			IActionResult										Result;

			// !!! Vytvori sa POLLY PIPELINE.
			ResiliencePipelineBuilder							PollyPipelineBuilder=new ResiliencePipelineBuilder();

			SlidingWindowRateLimiterOptions						Options=new SlidingWindowRateLimiterOptions();

			Options.PermitLimit=3;
			Options.Window=TimeSpan.FromSeconds(20);
			Options.SegmentsPerWindow=2;

			using(SlidingWindowRateLimiter TimeLimiter=new SlidingWindowRateLimiter(Options))
			{
				PollyPipelineBuilder.AddRateLimiter(TimeLimiter);

				ResiliencePipeline								PollyPipeline=PollyPipelineBuilder.Build();
				StringBuilder									SB=new StringBuilder();

				for(int Batch=0;Batch<NumberOfBatches;Batch++)
				{
					for(int Index=0;Index<NumberOfRequests;Index++)
					{
						int										CommandIndex=((NumberOfRequests*Batch)+Index+1);

						try
						{
							HttpResponseMessage					ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

							ResponseMessage.EnsureSuccessStatusCode();

							string								RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

							string								LocalContent=$"{CommandIndex} - METHOD 2 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

							if (SB.Length>0)
							{
								SB.AppendLine();
							}

							SB.Append(LocalContent);
						}
						catch(Exception E)
						{
							Console.WriteLine($"RATE LIMITER 2 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

							if (SB.Length>0)
							{
								SB.AppendLine();
							}

							string								LocalContent=$"{CommandIndex} - EXCEPTION [{E.Message}].";

							SB.Append(LocalContent);
						}
					}

					await Task.Delay(PauseInSeconds*1000);
				}

				string											Content=SB.ToString();

				Result=Ok(Content);
			}

			Console.WriteLine($"RATE LIMITER 2 FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena EXTERNE v externej COFIGURATION.
		[HttpGet(nameof(RateLimiterMethod3))]
		public async Task<IActionResult> RateLimiterMethod3(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"RATE LIMITER METHOD 3 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Ziska sa nakonfigurovana POLLY PIPELINE, ktora ma TIMEOUT definovany na 5 sekund.
				ResiliencePipeline								PollyPipeline=MResiliencePipelineProvider.GetPipeline(Program.POLLY_RATE_LIMITER_FIXED_PIPELINE_NAME);

				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 3 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"RATE LIMITER 3 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"RATE LIMITER 3 FINISHED. ID [{ID}].");

			return(Result);

		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD pouziva POLLY, pricom POLLY PIPELINE je vytvorena EXTERNE v externej COFIGURATION.
		[HttpGet(nameof(RateLimiterMethod4))]
		public async Task<IActionResult> RateLimiterMethod4(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"RATE LIMITER METHOD 4 STARTED. ID [{ID}].");

			IActionResult										Result;

			try
			{
				// !!! Ziska sa nakonfigurovana POLLY PIPELINE, ktora ma TIMEOUT definovany na 5 sekund.
				ResiliencePipeline								PollyPipeline=MResiliencePipelineProvider.GetPipeline(Program.POLLY_RATE_LIMITER_SLIDING_PIPELINE_NAME);

				HttpResponseMessage								ResponseMessage=await PollyPipeline.ExecuteAsync(async CancelToken => await CallRemoteMethod(CancelToken,ID));

				ResponseMessage.EnsureSuccessStatusCode();

				string											RemoteServiceContent=await ResponseMessage.Content.ReadAsStringAsync();

				string											Content=$"METHOD 4 - REMOTE SERVICE RESPONSE [{RemoteServiceContent}].";

				Result=Ok(Content);
			}
			catch(Exception E)
			{
				Console.WriteLine($"RATE LIMITER 4 DETECTED EXCEPTION. ID [{ID}]. EXCEPTION [{E.Message}].");

				Result=Problem(E.Message);
			}

			Console.WriteLine($"RATE LIMITER 4 FINISHED. ID [{ID}].");

			return(Result);

		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------