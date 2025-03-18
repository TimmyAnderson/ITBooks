using System;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class EnumTypesService : EnumTypes.EnumTypesBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<EnumTypesService>			MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public EnumTypesService(ILogger<EnumTypesService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<EnumTypesResponse> ProcessEnumTypes(EnumTypesRequest Request, ServerCallContext Context)
		{
			Console.WriteLine($"FIELD [{nameof(Request.Field1)}] VALUE [{Request.Field1}].");
			Console.WriteLine($"FIELD [{nameof(Request.Field2)}] VALUE [{Request.Field2}].");
			Console.WriteLine($"FIELD [{nameof(Request.Field3)}] VALUE [{Request.Field3}].");
			
			EnumTypesResponse								ResponseContent=new EnumTypesResponse();

			ResponseContent.ResponseMessage=$"MESSAGE was SUCCESSFULLY PROCESSED.";

			Task<EnumTypesResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------