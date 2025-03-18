using System;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class ServicesClientStreamingService : ServicesClientStreaming.ServicesClientStreamingBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<ServicesClientStreamingService>	MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public ServicesClientStreamingService(ILogger<ServicesClientStreamingService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override async Task<ServicesClientStreamingResponse> ProcessServicesClientStreaming(IAsyncStreamReader<ServicesClientStreamingRequest> RequestStream, ServerCallContext Context)
		{
			int													Sum=0;
			int													NumberOfMessages=0;

			// !!!!! STREAM je citany, az kym CLIENT nezavola METHOD [IClientStreamWriter<ServicesClientStreamingRequest>.CompleteAsync()].
			await foreach(ServicesClientStreamingRequest Request in RequestStream.ReadAllAsync())
			{
				Console.WriteLine($"MESSAGE with VALUE [{Request.Value}] RECEIVED.");

				Sum+=Request.Value;
				++NumberOfMessages;
			}

			Console.WriteLine($"RETURNING RESPONSE MESSAGE.");

			// !!! RESPONSE MESSAGE sa vracia ako RETURN VALUE.
			ServicesClientStreamingResponse						ResponseMessage=new ServicesClientStreamingResponse();

			ResponseMessage.Message=$"RESPONSE - SUM [{Sum}] NUMBER OF MESSAGES [{NumberOfMessages}].";

			return(ResponseMessage);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------