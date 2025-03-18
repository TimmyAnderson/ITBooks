using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class ServicesUnaryService : ServicesUnary.ServicesUnaryBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<ServicesUnaryService>			MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public ServicesUnaryService(ILogger<ServicesUnaryService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<ServicesUnaryResponse> ProcessServicesUnary1(ServicesUnaryRequest Request, ServerCallContext Context)
		{
			ServicesUnaryResponse								ResponseContent=new ServicesUnaryResponse();

			ResponseContent.Field1=$"METHOD 1 - {Request.Field1} {Request.Field2}";
			ResponseContent.Field2+=1000;

			Task<ServicesUnaryResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<ServicesUnaryResponse> ProcessServicesUnary2(ServicesUnaryRequest Request, ServerCallContext Context)
		{
			ServicesUnaryResponse								ResponseContent=new ServicesUnaryResponse();

			ResponseContent.Field1=$"METHOD 1 - {Request.Field1} {Request.Field2}";
			ResponseContent.Field2+=2000;

			Task<ServicesUnaryResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------