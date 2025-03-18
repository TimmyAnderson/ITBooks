using System;
using System.Threading;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class ServicesBidirectionalStreamingService : ServicesBidirectionalStreaming.ServicesBidirectionalStreamingBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<ServicesBidirectionalStreamingService>	MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public ServicesBidirectionalStreamingService(ILogger<ServicesBidirectionalStreamingService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static async Task MessageWriter(CancellationToken CancellationToken, IServerStreamWriter<ServicesBidirectionalStreamingResponse> ResponseStream)
		{
			Console.WriteLine("WRITER TASK STARTED.");

			int													Value1=0;
			int													Value2=0;

			try
			{
				while(true)
				{
					await Task.Delay(1000,CancellationToken);

					ServicesBidirectionalStreamingResponse		Response=new ServicesBidirectionalStreamingResponse();

					Response.Value1=++Value1;
					Response.Value2=--Value2;

					await ResponseStream.WriteAsync(Response,CancellationToken);
				}
			}
			catch(TaskCanceledException E)
			{
				Console.WriteLine($"MESSAGE WRITER was CANCELLED. EXCEPTION [{E.Message}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"MESSAGE WRITER has CAUGHT EXCEPTION [{E.Message}].");
			}

			Console.WriteLine("WRITER TASK FINISHED.");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override async Task ProcessServicesBidirectionalStreaming(IAsyncStreamReader<ServicesBidirectionalStreamingRequest> RequestStream, IServerStreamWriter<ServicesBidirectionalStreamingResponse> ResponseStream, ServerCallContext Context)
		{
			Task												WriterTask=Task.Run(async () => await MessageWriter(Context.CancellationToken,ResponseStream));

			try
			{
				// !!!!! STREAM je citany, az kym CLIENT nezavola METHOD [IClientStreamWriter<ServicesBidirectionalStreamingRequest>.CompleteAsync()].
				await foreach(ServicesBidirectionalStreamingRequest Request in RequestStream.ReadAllAsync(Context.CancellationToken))
				{
					Console.WriteLine($"MESSAGE with VALUE [{Request.Value}] RECEIVED.");
				}
			}
			catch(TaskCanceledException E)
			{
				Console.WriteLine($"MESSAGE READER was CANCELLED. EXCEPTION [{E.Message}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"READ MESSAGE EXCEPTION [{E.Message}].");
			}

			await WriterTask;
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------