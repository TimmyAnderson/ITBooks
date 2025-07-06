using System;
using System.Collections.Generic;
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
	public static class DurableMonitoring
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD reprezentuje ACTITIVY.
		[Function(nameof(DurableMonitoringWorker))]
		public static string DurableMonitoringWorker([ActivityTrigger] string Name, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("DurableMonitoringWorker");

			try
			{
				Logger.LogInformation($"METHOD [{nameof(DurableMonitoringWorker)}] STARTED.");

				// !!! Simulate WORK.
				Thread.Sleep(5000);

				Logger.LogInformation($"METHOD [{nameof(DurableMonitoringWorker)}] FINISHED.");

				string											Response=$"MONITORING [{Name}].";

				return(Response);
			}
			catch(Exception E)
			{
				Logger.LogError(E,$"EXCEPTION in METHOD [{nameof(DurableMonitoringWorker)}].");

				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Function(nameof(DurableMonitoring))]
		public static async Task<string[]> RunOrchestrator([OrchestrationTrigger] TaskOrchestrationContext Context)
		{
			ILogger												Logger=Context.CreateReplaySafeLogger(nameof(DurableMonitoring));

			try
			{
				Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] STARTED.");

				List<string>									ResponsesCollection=new List<string>();

				for(int Index=0;Index<3;Index++)
				{
					DateTime									CurrentTimeInUTC=Context.CurrentUtcDateTime;
					DateTime									NextExpirationTime=CurrentTimeInUTC.AddSeconds(20);

					// !!!!! Simuluje sa cakanie na EXPIRATION TIME, kedy sa ma ACTIVITY spustit.
					await Context.CreateTimer(NextExpirationTime,CancellationToken.None);

					string										Result=await Context.CallActivityAsync<string>(nameof(DurableMonitoringWorker),$"ACTIVITY START TIME [{Context.CurrentUtcDateTime}].");

					ResponsesCollection.Add(Result);
				}

				string[]										Responses=ResponsesCollection.ToArray();

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
		[Function("DurableMonitoring_HttpStart")]
		public static async Task<HttpResponseData> HttpStart([HttpTrigger(AuthorizationLevel.Anonymous,"get")] HttpRequestData Request, [DurableClient] DurableTaskClient Client, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("DurableMonitoring_HttpStart");
			string												InstanceID=await Client.ScheduleNewOrchestrationInstanceAsync(nameof(DurableMonitoring));

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