using System;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class ExtensionTypesService : ExtensionTypes.ExtensionTypesBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<ExtensionTypesService>			MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public ExtensionTypesService(ILogger<ExtensionTypesService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<ExtensionTypesResponse> ProcessExtensionTypes(ExtensionTypesRequest Request, ServerCallContext Context)
		{
			Console.WriteLine($"FIELD [{nameof(Request.FieldTimestamp)}] VALUE [{Request.FieldTimestamp.ToDateTime().Second}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldDuration)}] VALUE [{Request.FieldDuration.ToTimeSpan().Seconds}].");
			
			ExtensionTypesResponse								ResponseContent=new ExtensionTypesResponse();

			ResponseContent.ResponseMessage=$"MESSAGE was SUCCESSFULLY PROCESSED.";

			Task<ExtensionTypesResponse>						ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------