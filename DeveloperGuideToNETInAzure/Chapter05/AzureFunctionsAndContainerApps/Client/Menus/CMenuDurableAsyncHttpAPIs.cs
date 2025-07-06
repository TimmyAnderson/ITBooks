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
	public sealed class CMenuDurableAsyncHttpAPIs : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS_SERVICE_LOCAL="http://localhost:7000/";
		private const string									BASE_ADDRESS_SERVICE_AZURE="https://durfunctionta.azurewebsites.net/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuDurableAsyncHttpAPIs()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallDurableFunctionHttpSynchronousLocal(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/DurableAsyncHttpAPIs_HttpStartSynchronous";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				
			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallDurableFunctionHttpAsynchronousLocal(string CommandID, object[] Parameters)
		{
			CMyHttpClientOperationResponse						Response;

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/DurableAsyncHttpAPIs_HttpStartAsynchronous";
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
		private void ExecuteCommandCallDurableFunctionHttpSynchronousAzure(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/DurableAsyncHttpAPIs_HttpStartSynchronous";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
				
			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallDurableFunctionHttpAsynchronousAzure(string CommandID, object[] Parameters)
		{
			CMyHttpClientOperationResponse						Response;

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/DurableAsyncHttpAPIs_HttpStartAsynchronous";
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

			CommandsCollection.Add(new CMenuCommand("1","CALL FUNCTION HTTP SYNCHRONOUS LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallDurableFunctionHttpSynchronousLocal));
			CommandsCollection.Add(new CMenuCommand("2","CALL FUNCTION HTTP ASYNCHRONOUS LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallDurableFunctionHttpAsynchronousLocal));
			CommandsCollection.Add(new CMenuCommand("3","CALL FUNCTION HTTP SYNCHRONOUS AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallDurableFunctionHttpSynchronousAzure));
			CommandsCollection.Add(new CMenuCommand("4","CALL FUNCTION HTTP ASYNCHRONOUS AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallDurableFunctionHttpAsynchronousAzure));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------