using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class ParallelCallsService : ParallelCalls.ParallelCallsBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private static object									MLock=new object();
		private static long										MCounter;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<ParallelCallsService>			MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public ParallelCallsService(ILogger<ParallelCallsService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<ParallelCallsResponse> ProcessParallelCalls(ParallelCallsRequest Request, ServerCallContext Context)
		{
			lock(MLock)
			{
				++MCounter;
			}

			ParallelCallsResponse								ResponseContent=new ParallelCallsResponse();
			Task<ParallelCallsResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<ParallelCallsResultResponse> ProcessParallelCallsResult(ParallelCallsResultRequest Request, ServerCallContext Context)
		{
			long												Counter;

			lock(MLock)
			{
				Counter=MCounter;
			}

			ParallelCallsResultResponse							ResponseContent=new ParallelCallsResultResponse();

			ResponseContent.Counter=Counter;

			Task<ParallelCallsResultResponse>					ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------