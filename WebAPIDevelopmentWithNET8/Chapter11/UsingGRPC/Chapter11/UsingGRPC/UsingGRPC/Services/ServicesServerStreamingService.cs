using System;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class ServicesServerStreamingService : ServicesServerStreaming.ServicesServerStreamingBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<ServicesServerStreamingService>	MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public ServicesServerStreamingService(ILogger<ServicesServerStreamingService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override async Task ProcessServicesServerStreaming(ServicesServerStreamingRequest Request, IServerStreamWriter<ServicesServerStreamingResponse> ResponseStream, ServerCallContext Context)
		{
			int													Counter=1;

			try
			{
				// !!! Vykonava sa kontrola ci CHANNEL nebol z CLIENT SIDE uzatvoreny.
				while(Context.CancellationToken.IsCancellationRequested==false)
				{
					await Task.Delay(1000,Context.CancellationToken);

					ServicesServerStreamingResponse				ResponseMessage=new ServicesServerStreamingResponse();

					Console.WriteLine($"SENDING MESSAGE with COUNTER [{Counter}].");

					ResponseMessage.Counter=Counter++;

					// !!! Odosle sa MESSAGE na CLIENT.
					await ResponseStream.WriteAsync(ResponseMessage,Context.CancellationToken);

					if (Counter>Request.NumberOfMessages)
					{
						break;
					}
				}
			}
			catch(TaskCanceledException E)
			{
				Console.WriteLine($"TASK was CANCELLED. EXCEPTION [{E.Message}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------