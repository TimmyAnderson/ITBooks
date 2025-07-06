using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace ServiceToServiceInvocation1
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MyService1Controller : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									BASE_URL_SERVICE_2_LOCAL="http://localhost:5002/";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<MyService1Controller>			MLogger;
		private readonly HttpClient								MClient;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyService1Controller(ILogger<MyService1Controller> Logger, HttpClient Client)
		{
			MLogger=Logger;
			MClient=Client;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public async Task<string> CallService()
		{
			MLogger.LogInformation("SERVICE 1 CALLED !");

			string												ServiceUrl;

			if (Program.RUN_LOCALLY==true)
			{
				ServiceUrl=$"{BASE_URL_SERVICE_2_LOCAL}MyService2";
			}
			else
			{
				// !!!!! Pri komunikacii cez DAPR HTTP CLIENT sa pouziva iba LOCAL ADDRESS.
				ServiceUrl=$"MyService2";
			}

			MLogger.LogInformation($"SERVICE 2 URL [{ServiceUrl}] !");

			string												Service2Result=await MClient.GetStringAsync(ServiceUrl);
			string												Service1Result=$"From SERVICE 1 [{Service2Result}].";

			return(Service1Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------