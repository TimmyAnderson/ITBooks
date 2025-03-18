using System;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf.Collections;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using UsingGRPC;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingGRPCNames.Services
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class RepeatedTypesService : RepeatedTypes.RepeatedTypesBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<RepeatedTypesService>			MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public RepeatedTypesService(ILogger<RepeatedTypesService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static string ConvertToString<TType>(RepeatedField<TType> Collection)
		{
			StringBuilder										SB=new StringBuilder();

			for(int Index=0;Index<Collection.Count;Index++)
			{
				if (Index>0)
				{
					SB.Append(',');
				}

				TType											Value=Collection[Index];
				string											TextValue=Value.ToString();

				SB.Append(TextValue);
			}

			string												Text=SB.ToString();

			return(Text);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<RepeatedTypesResponse> ProcessRepeatedTypes(RepeatedTypesRequest Request, ServerCallContext Context)
		{
			Console.WriteLine($"FIELD [{nameof(Request.NoRepeatedField)}] VALUE [{Request.NoRepeatedField}].");

			string												RepeatedField1RepeatedField=ConvertToString(Request.RepeatedField1);

			Console.WriteLine($"FIELD [{nameof(Request.RepeatedField1)}] VALUE [{RepeatedField1RepeatedField}].");

			string												RepeatedField2RepeatedField=ConvertToString(Request.RepeatedField2);

			Console.WriteLine($"FIELD [{nameof(Request.RepeatedField2)}] VALUE [{RepeatedField2RepeatedField}].");
			
			RepeatedTypesResponse								ResponseContent=new RepeatedTypesResponse();

			ResponseContent.ResponseMessage=$"MESSAGE was SUCCESSFULLY PROCESSED.";

			Task<RepeatedTypesResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------