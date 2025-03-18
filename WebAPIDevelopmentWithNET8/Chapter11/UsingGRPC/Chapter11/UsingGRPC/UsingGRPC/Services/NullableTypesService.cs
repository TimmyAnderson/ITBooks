using System;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class NullableTypesService : NullableTypes.NullableTypesBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<NullableTypesService>			MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public NullableTypesService(ILogger<NullableTypesService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<NullableTypesResponse> ProcessNullableTypes(NullableTypesRequest Request, ServerCallContext Context)
		{
			Console.WriteLine($"FIELD [{nameof(Request.FieldDoubleValue)}] VALUE [{Request.FieldDoubleValue}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldFloatValue)}] VALUE [{Request.FieldFloatValue}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldInt32Value)}] VALUE [{Request.FieldInt32Value}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldInt64Value)}] VALUE [{Request.FieldInt64Value}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldUInt32Value)}] VALUE [{Request.FieldUInt32Value}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldUInt64Value)}] VALUE [{Request.FieldUInt64Value}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldBoolValue)}] VALUE [{Request.FieldBoolValue}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldStringValue)}] VALUE [{Request.FieldStringValue}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldBytesValue)}] VALUE [{Request.FieldBytesValue?.ToStringUtf8()}].");
			
			NullableTypesResponse								ResponseContent=new NullableTypesResponse();

			ResponseContent.ResponseMessage=$"MESSAGE was SUCCESSFULLY PROCESSED.";

			Task<NullableTypesResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------