using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuDurableMonitoring : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS_SERVICE_LOCAL="http://localhost:7000/";
		private const string									BASE_ADDRESS_SERVICE_AZURE="https://durfunctionta.azurewebsites.net/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuDurableMonitoring()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallDurableFunctionHttpGetLocal(string CommandID, object[] Parameters)
		{
			CMyHttpClientOperationResponse						Response;

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/DurableMonitoring_HttpStart";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				
				Response=CMyHttpClient.ExecuteMessage(Request);
			}

			if (Response.StatusCode==HttpStatusCode.Accepted)
			{
				CDurableAzureFunctionResponse					DurableAzureFunctionResponse=Response.Content.ConvertToObject<CDurableAzureFunctionResponse>();

				while(true)
				{
					Console.WriteLine("Press [q] to QUIT or anything else to do request.");

					string										Command=Console.ReadLine();

					if (Command.StartsWith('Q')==true || Command.StartsWith('q')==true)
					{
						break;
					}

					string										MessageID=CommandID;
					EMyHttpClientHttpMethod						Method=EMyHttpClientHttpMethod.E_GET;
					string										URL=DurableAzureFunctionResponse.StatusQueryGetUri;
					CMyHttpClientHeaders						Headers=null;
					CMyHttpClientContent						Content=null;
					TimeSpan									Timeout=TimeSpan.FromHours(1);
					CMyHttpClientOperationRequest				Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				
					CMyHttpClient.ExecuteMessage(Request);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallDurableFunctionHttpGetAzure(string CommandID, object[] Parameters)
		{
			CMyHttpClientOperationResponse						Response;

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/DurableMonitoring_HttpStart";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				
				Response=CMyHttpClient.ExecuteMessage(Request);
			}

			if (Response.StatusCode==HttpStatusCode.Accepted)
			{
				CDurableAzureFunctionResponse					DurableAzureFunctionResponse=Response.Content.ConvertToObject<CDurableAzureFunctionResponse>();

				while(true)
				{
					Console.WriteLine("Press [q] to QUIT or anything else to do request.");

					string										Command=Console.ReadLine();

					if (Command.StartsWith('Q')==true || Command.StartsWith('q')==true)
					{
						break;
					}

					string										MessageID=CommandID;
					EMyHttpClientHttpMethod						Method=EMyHttpClientHttpMethod.E_GET;
					string										URL=DurableAzureFunctionResponse.StatusQueryGetUri;
					CMyHttpClientHeaders						Headers=null;
					CMyHttpClientContent						Content=null;
					TimeSpan									Timeout=TimeSpan.FromHours(1);
					CMyHttpClientOperationRequest				Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				
					CMyHttpClient.ExecuteMessage(Request);
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","CALL FUNCTION HTTP GET LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallDurableFunctionHttpGetLocal));
			CommandsCollection.Add(new CMenuCommand("2","CALL FUNCTION HTTP GET AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallDurableFunctionHttpGetAzure));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------