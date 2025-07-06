using System;
using System.Collections.Specialized;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Azure.Functions.Worker.Http;
using Microsoft.DurableTask;
using Microsoft.DurableTask.Client;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace MyAzureFunctions
{
//----------------------------------------------------------------------------------------------------------------------
	public static class DurableHumanInteraction
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									EVENT_NAME="MY_EVENT";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Function(nameof(DurableHumanInteraction))]
		public static async Task<string> RunOrchestrator([OrchestrationTrigger] TaskOrchestrationContext Context)
		{
			ILogger												Logger=Context.CreateReplaySafeLogger(nameof(DurableHumanInteraction));

			try
			{
				Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] STARTED.");

				string											Response;

				using(CancellationTokenSource CTS=new CancellationTokenSource())
				{
					DateTime									CurrentTimeInUTC=Context.CurrentUtcDateTime;
					DateTime									NextExpirationTime=CurrentTimeInUTC.AddSeconds(60);

					// !!!!! TASK je COMPLETED, ak sa nastavi EVENT, ktory vznikne na zaklade HUMAN INTERACTION.
					Task<bool>									EventTask=Context.WaitForExternalEvent<bool>(EVENT_NAME);

					// !!!!! TASK reprezentuje cakanie na HUMAN INTERACTION.
					Task										WaitTask=Context.CreateTimer(NextExpirationTime,CTS.Token);

					Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] EXPIRATION TIME [{NextExpirationTime}].");

					Task										FinishedTask=await Task.WhenAny(EventTask,WaitTask);

					Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] EVENT FIRED AT [{Context.CurrentUtcDateTime}].");

					if (FinishedTask==EventTask)
					{
						CTS.Cancel();

						Task<bool>								TypedFinishedTask=(Task<bool>) FinishedTask;

						Response=$"USER INTERACTION - RESULT [{TypedFinishedTask.Result}].";
					}
					else if (FinishedTask==WaitTask)
					{
						Response="TIMEOUT EXPIRED.";
					}
					else
					{
						CTS.Cancel();

						Response="UNEXPECTED EVENT.";
					}
				}

				Logger.LogInformation($"METHOD [{nameof(RunOrchestrator)}] FINISHED.");

				return(Response);
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
		[Function("DurableHumanInteraction_HttpStart")]
		public static async Task<HttpResponseData> HttpStart([HttpTrigger(AuthorizationLevel.Anonymous,"get")] HttpRequestData Request, [DurableClient] DurableTaskClient Client, FunctionContext ExecutionContext)
		{
			ILogger												Logger=ExecutionContext.GetLogger("DurableHumanInteraction_HttpStart");
			string												InstanceID=await Client.ScheduleNewOrchestrationInstanceAsync(nameof(DurableHumanInteraction));

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