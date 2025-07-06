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
	public static class DurableFunctionChaining
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ACTIVITY.
		[Function(nameof(FunctionChainingSayHello1))]
		public static string FunctionChainingSayHello1([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("FunctionChainingSayHello1");

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FunctionChainingSayHello1)}] STARTED.");

				// !!! Simulate WORK.
				Thread.Sleep(5000);

				Logger.LogInformation($"METHOD [{nameof(FunctionChainingSayHello1)}] FINISHED.");

				string											Response=$"SAY HELLO 1 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FunctionChainingSayHello1)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ACTIVITY.
		[Function(nameof(FunctionChainingSayHello2))]
		public static string FunctionChainingSayHello2([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("FunctionChainingSayHello2");

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FunctionChainingSayHello2)}] STARTED.");

				// !!! Simulate WORK.
				Thread.Sleep(5000);

				Logger.LogInformation($"METHOD [{nameof(FunctionChainingSayHello2)}] FINISHED.");

				string											Response=$"SAY HELLO 2 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FunctionChainingSayHello2)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ACTIVITY.
		[Function(nameof(FunctionChainingSayHello3))]
		public static string FunctionChainingSayHello3([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("FunctionChainingSayHello3");

			try
			{
				Logger.LogInformation($"METHOD [{nameof(FunctionChainingSayHello3)}] STARTED.");

				// !!! Simulate WORK.
				Thread.Sleep(5000);

				Logger.LogInformation($"METHOD [{nameof(FunctionChainingSayHello3)}] FINISHED.");

				string											Response=$"SAY HELLO 3 [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(FunctionChainingSayHello3)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ORCHESTRATOR.
		[Function(nameof(DurableFunctionChaining))]
		public static async Task<string[]> RunOrchestrator([OrchestrationTrigger] TaskOrchestrationContext Context)
		{
			ILogger												Logger=Context.CreateReplaySafeLogger(nameof(DurableFunctionChaining));

			try
			{
				Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] STARTED.");

				string											Response1=await Context.CallActivityAsync<string>(nameof(FunctionChainingSayHello1),"Timmy");
				string											Response2=await Context.CallActivityAsync<string>(nameof(FunctionChainingSayHello2),"Jenny");
				string											Response3=await Context.CallActivityAsync<string>(nameof(FunctionChainingSayHello3),"Lucas");

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
		// !!! METHOD reprezentuje TRIGGER, ktory spusta ORCHESTRATOR.
		[Function("DurableFunctionChaining_HttpStart")]
		public static async Task<HttpResponseData> HttpStart([HttpTrigger(AuthorizationLevel.Anonymous,"get")] HttpRequestData Request, [DurableClient] DurableTaskClient Client, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("DurableFunctionChaining_HttpStart");

			// !!! Spusti sa vykonavanie ORCHESTRATOR AZURE FUNCTION.
			string												InstanceID=await Client.ScheduleNewOrchestrationInstanceAsync(nameof(DurableFunctionChaining));

			Logger.LogInformation($"ORCHESTRATION ID [{InstanceID}] STARTED.");

			/*
			// !!!!! Standardne by DURABLE AZURE FUNCTION mala byt len asynchronne spustena a CLIENT by NEMAL cakat na jej skoncenie, ale mal by asynchronne konrolovat jej priebeh volanim API.
			OrchestrationMetadata								OrchestrationMetadata=await Client.WaitForInstanceCompletionAsync(InstanceID);

			Logger.LogInformation($"ORCHESTRATION ID [{InstanceID}] FINISHED with STATUS [{OrchestrationMetadata.RuntimeStatus}].");
			*/

			// !!!!! OBJECT TYPE [HttpResponseData] obsahuje HTTP RESPONSE CODE 202 s URL cez ktory moze CLIENT zistovat stav v akom je beh DURABLE AZURE FUNCTION.
			// !!!!! OBJECT TYPE [HttpResponseData] obsahuje aj URLs, ktore moze CLIENT pouzivat na zistenie ci DURABLE AZURE FUNCTION skoncila.
			HttpResponseData									ResponseData=await Client.CreateCheckStatusResponseAsync(Request,InstanceID);

			Logger.LogInformation($"ORCHESTRATION ID [{InstanceID}] FINISHED.");

			return(ResponseData);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------