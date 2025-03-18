using System;
using System.Collections.Generic;
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
	public class MapTypesService : MapTypes.MapTypesBase
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<MapTypesService>				MLogger;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public MapTypesService(ILogger<MapTypesService> Logger)
		{
			MLogger=Logger;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static string ConvertToString<TTypeKey,TTypeValue>(MapField<TTypeKey,TTypeValue> Collection)
		{
			StringBuilder										SB=new StringBuilder();
			bool												IsFirst=true;

			foreach(KeyValuePair<TTypeKey,TTypeValue> Pair in Collection)
			{
				if (IsFirst==true)
				{
					IsFirst=false;
				}
				else
				{
					SB.Append(',');
				}

				TTypeKey										Key=Pair.Key;
				TTypeValue										Value=Pair.Value;
				string											TextKey=Key.ToString();
				string											TextValue=Value.ToString();

				SB.Append($"[{TextKey} - {TextValue}]");
			}

			string												Text=SB.ToString();

			return(Text);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public override Task<MapTypesResponse> ProcessMapTypes(MapTypesRequest Request, ServerCallContext Context)
		{
			Console.WriteLine($"FIELD [{nameof(Request.NoMapField)}] VALUE [{Request.NoMapField}].");

			string												MapField1MapField=ConvertToString(Request.MapField1);

			Console.WriteLine($"FIELD [{nameof(Request.MapField1)}] VALUE [{MapField1MapField}].");

			string												MapField2MapField=ConvertToString(Request.MapField2);

			Console.WriteLine($"FIELD [{nameof(Request.MapField2)}] VALUE [{MapField2MapField}].");
			
			MapTypesResponse								ResponseContent=new MapTypesResponse();

			ResponseContent.ResponseMessage=$"MESSAGE was SUCCESSFULLY PROCESSED.";

			Task<MapTypesResponse>							ResponseTask=Task.FromResult(ResponseContent);

			return(ResponseTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------