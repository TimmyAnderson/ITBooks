using System;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Http;
using Microsoft.DurableTask;
using Microsoft.DurableTask.Client;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace MyAzureFunctions
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Pre korektny beh DURABLE AZURE FUNCTION MUSI bezat EMULATOR AZURITE.
	public static class DurableFanOutFanIn
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ACTITIVY.
		[Function(nameof(FanOutFanInSayHello1))]
		public static string FanOutFanInSayHello1([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("FanOutFanInSayHello1");

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FanOutFanInSayHello1)}] STARTED.");

				Random											RND=new Random();
				int												Timeout=RND.Next(5000);

				// !!! Simulate WORK.
				Thread.Sleep(Timeout);

				Logger.LogInformation($"METHOD [{nameof(FanOutFanInSayHello1)}] FINISHED.");

				string											Response=$"SAY HELLO 1 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FanOutFanInSayHello1)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ACTITIVY.
		[Function(nameof(FanOutFanInSayHello2))]
		public static string FanOutFanInSayHello2([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("FanOutFanInSayHello2");

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FanOutFanInSayHello2)}] STARTED.");

				Random											RND=new Random();
				int												Timeout=RND.Next(5000);

				// !!! Simulate WORK.
				Thread.Sleep(Timeout);

				Logger.LogInformation($"METHOD [{nameof(FanOutFanInSayHello2)}] FINISHED.");

				string											Response=$"SAY HELLO 2 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FanOutFanInSayHello2)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ACTITIVY.
		[Function(nameof(FanOutFanInSayHello3))]
		public static string FanOutFanInSayHello3([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("FanOutFanInSayHello3");

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FanOutFanInSayHello3)}] STARTED.");

				Random											RND=new Random();
				int												Timeout=RND.Next(5000);

				// !!! Simulate WORK.
				Thread.Sleep(Timeout);

				Logger.LogInformation($"METHOD [{nameof(FanOutFanInSayHello3)}] FINISHED.");

				string											Response=$"SAY HELLO 3 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FanOutFanInSayHello3)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Function(nameof(DurableFanOutFanIn))]
		public static async Task<string[]> RunOrchestrator([OrchestrationTrigger] TaskOrchestrationContext Context)
		{
			ILogger												Logger=Context.CreateReplaySafeLogger(nameof(DurableFanOutFanIn));

			try
			{
				Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] STARTED.");

				Task<string>									Task1=Context.CallActivityAsync<string>(nameof(FanOutFanInSayHello1),"Timmy");
				Task<string>									Task2=Context.CallActivityAsync<string>(nameof(FanOutFanInSayHello2),"Jenny");
				Task<string>									Task3=Context.CallActivityAsync<string>(nameof(FanOutFanInSayHello3),"Lucas");

				await Task.WhenAll(Task1,Task2,Task3);

				string											Response1=Task1.Result;
				string											Response2=Task2.Result;
				string											Response3=Task3.Result;

				string[]										Responses=new string[]{Response1,Response2,Response3};

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
		[Function("DurableFanOutFanIn_HttpStart")]
		public static async Task<HttpResponseData> HttpStart([HttpTrigger(AuthorizationLevel.Anonymous,"get")] HttpRequestData Request, [DurableClient] DurableTaskClient Client, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("DurableFanOutFanIn_HttpStart");
			string												InstanceID=await Client.ScheduleNewOrchestrationInstanceAsync(nameof(DurableFanOutFanIn));

			Logger.LogInformation($"ORCHESTRATION ID [{InstanceID}] STARTED.");

			// !!!!! OBJECT TYPE [HttpResponseData] obsahuje HTTP RESPONSE CODE 202 s URL cez ktory moze CLIENT zistovat stav v akom je beh DURABLE AZURE FUNCTION.
			HttpResponseData									ResponseData=await Client.CreateCheckStatusResponseAsync(Request,InstanceID);

			Logger.LogInformation($"ORCHESTRATION ID [{InstanceID}] FINISHED.");

			return(ResponseData);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------