using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Dapr.Client;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace StateManagement
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MyStateManagementController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! VALUE [statestore] je definovana DAPR a nemoze tu byt ina VALUE.
		private const string									STORE_NAME="statestore";
		private const string									KEY="MyState";
//----------------------------------------------------------------------------------------------------------------------
		private readonly static AutoResetEvent					MEvent=new AutoResetEvent(true);
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<MyStateManagementController>	MLogger;
		private readonly DaprClient								MDaprClient;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyStateManagementController(ILogger<MyStateManagementController> Logger, DaprClient DaprClient)
		{
			MLogger=Logger;
			MDaprClient=DaprClient;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public async Task<string> MyService(int ID, int DelayInMS)
		{
			MLogger.LogInformation($"SERVICE [{ID}] CALLED !");

			CState												State;

			MEvent.WaitOne();

			MLogger.LogInformation($"SERVICE [{ID}] LOCK GRANTED !");

			await Task.Delay(DelayInMS);

			try
			{
				State=await MDaprClient.GetStateAsync<CState>(STORE_NAME,KEY);

				DateTime										Now=DateTime.Now;

				if (State!=null)
				{
					State.LastRequestTime=Now;
					State.NumberOfRequests=(State.NumberOfRequests+1);
				}
				else
				{
					State=new CState(Now,Now,1);
				}

				await MDaprClient.SaveStateAsync<CState>(STORE_NAME,KEY,State);
			}
			finally
			{
				MEvent.Set();
			}

			MLogger.LogInformation($"SERVICE [{ID}] LOCK RELEASED !");

			string												Response=$"FIRST REQUEST TIME [{State.FirstRequestTime}] LAST REQUEST TIME [{State.LastRequestTime}] NUMBER OF REQUESTS [{State.NumberOfRequests}].";

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------