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
	public sealed class CMenuServiceToServiceInvocation : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS_SERVICE_1_LOCAL="http://localhost:5001/";
		private const string									BASE_ADDRESS_SERVICE_2_LOCAL="http://localhost:5002/";
		// !!!!! DOCKER DESKTOP MUSI byt SPUSTENY.
		// !!!!! Pre DAPR sa pouziva HTTP a MAPPED PORT je PORT [10001].
		private const string									BASE_ADDRESS_SERVICE_1_DAPR="http://localhost:10001/";
		// !!!!! Pre DAPR sa pouziva HTTP a MAPPED PORT je PORT [10002].
		private const string									BASE_ADDRESS_SERVICE_2_DAPR="http://localhost:10002/";
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									DAPR_HEADER_NAME_APPLICATION_ID="dapr-app-id";
		// !!!!! APPLICATION ID je VALUE s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
		private const string									DAPR_HEADER_VALUE_APPLICATION_ID_SERVICE_1="SERVICE_1";
		private const string									DAPR_HEADER_VALUE_APPLICATION_ID_SERVICE_2="SERVICE_2";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuServiceToServiceInvocation()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallService1Local(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_1_LOCAL}MyService1";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallService2Local(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_2_LOCAL}MyService2";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallService1Dapr(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_1_DAPR}MyService1";

			// !!!!! REQUESTS na DAPR SIDECAR PROCESS MUSIA obsahovat HEADER [dapr-app-id], ktoreho VALUE je APPLICATION ID s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(DAPR_HEADER_NAME_APPLICATION_ID,DAPR_HEADER_VALUE_APPLICATION_ID_SERVICE_1);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallService2Dapr(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_2_DAPR}MyService2";

			// !!!!! REQUESTS na DAPR SIDECAR PROCESS MUSIA obsahovat HEADER [dapr-app-id], ktoreho VALUE je APPLICATION ID s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(DAPR_HEADER_NAME_APPLICATION_ID,DAPR_HEADER_VALUE_APPLICATION_ID_SERVICE_2);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","CALL SERVICE 1 LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallService1Local));
			CommandsCollection.Add(new CMenuCommand("2","CALL SERVICE 2 LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallService2Local));
			CommandsCollection.Add(new CMenuCommand("3","CALL SERVICE 1 DAPR",new EMenuCommandParameterType[0],ExecuteCommandCallService1Dapr));
			CommandsCollection.Add(new CMenuCommand("4","CALL SERVICE 2 DAPR",new EMenuCommandParameterType[0],ExecuteCommandCallService2Dapr));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------