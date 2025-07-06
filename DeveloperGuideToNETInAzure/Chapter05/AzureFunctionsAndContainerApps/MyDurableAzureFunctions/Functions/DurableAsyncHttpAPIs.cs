using System;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Http;
using Microsoft.DurableTask;
using Microsoft.DurableTask.Client;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace MyAzureFunctions
{
//----------------------------------------------------------------------------------------------------------------------
	public static class DurableAsyncHttpAPIs
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje LONG RUNNING ACTIVITY.
		[Function(nameof(FunctionAsyncHttpAPIsSayHello1))]
		public static string FunctionAsyncHttpAPIsSayHello1([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger(nameof(FunctionAsyncHttpAPIsSayHello1));

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FunctionAsyncHttpAPIsSayHello1)}] STARTED.");

				// !!! Simulate WORK.
				Thread.Sleep(5000);

				Logger.LogInformation($"METHOD [{nameof(FunctionAsyncHttpAPIsSayHello1)}] FINISHED.");

				string											Response=$"SAY HELLO 1 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FunctionAsyncHttpAPIsSayHello1)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje LONG RUNNING ACTIVITY.
		[Function(nameof(FunctionAsyncHttpAPIsSayHello2))]
		public static string FunctionAsyncHttpAPIsSayHello2([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger(nameof(FunctionAsyncHttpAPIsSayHello2));

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FunctionAsyncHttpAPIsSayHello2)}] STARTED.");

				// !!! Simulate WORK.
				Thread.Sleep(10000);

				Logger.LogInformation($"METHOD [{nameof(FunctionAsyncHttpAPIsSayHello2)}] FINISHED.");

				string											Response=$"SAY HELLO 2 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FunctionAsyncHttpAPIsSayHello2)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ORCHESTRATOR.
		[Function(nameof(DurableAsyncHttpAPIs))]
		public static async Task<string[]> RunOrchestrator([OrchestrationTrigger] TaskOrchestrationContext Context)
		{
			ILogger												Logger=Context.CreateReplaySafeLogger(nameof(DurableAsyncHttpAPIs));

			try
			{
				Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] STARTED.");

				string											Response1=await Context.CallActivityAsync<string>(nameof(FunctionAsyncHttpAPIsSayHello1),"Timmy");
				string											Response2=await Context.CallActivityAsync<string>(nameof(FunctionAsyncHttpAPIsSayHello2),"Jenny");

				string[]										Responses=new string[]{Response1,Response2};

				Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] FINISHED.");
			
				return(Responses);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(RunOrchestrator)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Spusta DURABLE AZURE FUNCTION SYNCRHONNE.
	    [Function("DurableAsyncHttpAPIs_HttpStartSynchronous")]
		public static async Task<IActionResult> HttpStartSynchronous([HttpTrigger(AuthorizationLevel.Anonymous,"get")] HttpRequestData Request, [DurableClient] DurableTaskClient Client, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("DurableAsyncHttpAPIs_HttpStartSynchronous");
			string												InstanceID=await Client.ScheduleNewOrchestrationInstanceAsync(nameof(DurableAsyncHttpAPIs));

			Logger.LogInformation($"SYNCHRONOUS - ORCHESTRATION ID [{InstanceID}] STARTED.");

			// !!!!! METHOD caka na skoncenie DURABLE AZURE FUNCTION.
			OrchestrationMetadata								OrchestrationMetadata=await Client.WaitForInstanceCompletionAsync(InstanceID,true);

			string[]											Results=OrchestrationMetadata.ReadOutputAs<string[]>();

			Logger.LogInformation($"SYNCHRONOUS - ORCHESTRATION ID [{InstanceID}] FINISHED with STATUS [{OrchestrationMetadata.RuntimeStatus}].");

			IActionResult										Result=new OkObjectResult(Results);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! Spusta DURABLE AZURE FUNCTION ASYNCRHONNE.
		// !!!!! METHOD reprezentuje implementaciu ASYNC HTTP APIs PATTERN.
	    [Function("DurableAsyncHttpAPIs_HttpStartAsynchronous")]
		public static async Task<HttpResponseData> HttpStartAsynchronous([HttpTrigger(AuthorizationLevel.Anonymous,"get")] HttpRequestData Request, [DurableClient] DurableTaskClient Client, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("DurableAsyncHttpAPIs_HttpStartAsynchronous");
			string												InstanceID=await Client.ScheduleNewOrchestrationInstanceAsync(nameof(DurableAsyncHttpAPIs));

			Logger.LogInformation($"ASYNCHRONOUS - ORCHESTRATION ID [{InstanceID}] STARTED.");

			// !!!!! OBJECT TYPE [HttpResponseData] obsahuje HTTP RESPONSE CODE 202 s URL cez ktory moze CLIENT zistovat stav v akom je beh DURABLE AZURE FUNCTION.
			HttpResponseData									ResponseData=await Client.CreateCheckStatusResponseAsync(Request,InstanceID);

			Logger.LogInformation($"ASYNCHRONOUS - ORCHESTRATION ID [{InstanceID}] FINISHED.");

			return(ResponseData);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
