using System;
using System.Threading.Tasks;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class ScalarTypesService : ScalarTypes.ScalarTypesBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<ScalarTypesService>			MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public ScalarTypesService(ILogger<ScalarTypesService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<ScalarTypesResponse> ProcessScalarTypes(ScalarTypesRequest Request, ServerCallContext Context)
		{
			Console.WriteLine($"FIELD [{nameof(Request.FieldDouble)}] VALUE [{Request.FieldDouble}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldFloat)}] VALUE [{Request.FieldFloat}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldInt32)}] VALUE [{Request.FieldInt32}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldInt64)}] VALUE [{Request.FieldInt64}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldUInt32)}] VALUE [{Request.FieldUInt32}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldUInt64)}] VALUE [{Request.FieldUInt64}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldSInt32)}] VALUE [{Request.FieldSInt32}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldSInt64)}] VALUE [{Request.FieldSInt64}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldFixed32)}] VALUE [{Request.FieldFixed32}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldFixed64)}] VALUE [{Request.FieldFixed64}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldSFixed32)}] VALUE [{Request.FieldSFixed32}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldSFixed64)}] VALUE [{Request.FieldSFixed64}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldBool)}] VALUE [{Request.FieldBool}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldString)}] VALUE [{Request.FieldString}].");
			Console.WriteLine($"FIELD [{nameof(Request.FieldBytes)}] VALUE [{Request.FieldBytes.ToStringUtf8()}].");
			
			ScalarTypesResponse									ResponseContent=new ScalarTypesResponse();

			ResponseContent.ResponseMessage=$"MESSAGE was SUCCESSFULLY PROCESSED.";

			Task<ScalarTypesResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------