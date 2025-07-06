using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Dapr;
using Dapr.Client;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace PublishSubscribePublisher
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class MyPublisherServiceController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									SERVICE_NAME="pubsub";
		private const string									TOPIC_NAME="MyTopic";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<MyPublisherServiceController>	MLogger;
		private readonly DaprClient								MDaprClient;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyPublisherServiceController(ILogger<MyPublisherServiceController> Logger, DaprClient DaprClient)
		{
			MLogger=Logger;
			MDaprClient=DaprClient;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public async Task CallService(int Value1, int Value2)
		{
			MLogger.LogInformation($"PUBLISHER SERVICE CALLED with VALUE 1 [{Value1}] VALUE 2 [{Value2}] !");

			CMessage											Message=new CMessage(Value1,Value2);

			// !!!!! MESSAGE sa odosle do SUBSCRIBERS.
			await MDaprClient.PublishEventAsync<CMessage>(SERVICE_NAME,TOPIC_NAME,Message);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------