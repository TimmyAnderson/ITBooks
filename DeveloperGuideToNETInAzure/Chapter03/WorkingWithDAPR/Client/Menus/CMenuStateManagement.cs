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
	public sealed class CMenuStateManagement : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! DOCKER DESKTOP MUSI byt SPUSTENY.
		// !!!!! Pre DAPR sa pouziva HTTP a MAPPED PORT je PORT [10000].
		private const string									BASE_ADDRESS_SERVICE_DAPR="http://localhost:10000/";
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									DAPR_HEADER_NAME_APPLICATION_ID="dapr-app-id";
		// !!!!! APPLICATION ID je VALUE s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
		private const string									DAPR_HEADER_VALUE_APPLICATION_ID_SERVICE="MY_SERVICE";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuStateManagement()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void CallServiceDapr(int ID, int DelayInMS)
		{
			string												MessageID=ID.ToString();
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_DAPR}MyStateManagement?ID={ID}&DelayInMS={DelayInMS}";

			// !!!!! REQUESTS na DAPR SIDECAR PROCESS MUSIA obsahovat HEADER [dapr-app-id], ktoreho VALUE je APPLICATION ID s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(DAPR_HEADER_NAME_APPLICATION_ID,DAPR_HEADER_VALUE_APPLICATION_ID_SERVICE);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallServiceDapr(string CommandID, object[] Parameters)
		{
			CallServiceDapr(0,0);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandMultiCallServiceDapr(string CommandID, object[] Parameters)
		{
			Task												Task1=new Task(() => CallServiceDapr(1,5000));
			Task												Task2=new Task(() => CallServiceDapr(2,5000));

			Task1.Start();
			Task2.Start();

			Task.WaitAll(Task1,Task2);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","CALL SERVICE DAPR",new EMenuCommandParameterType[0],ExecuteCommandCallServiceDapr));
			CommandsCollection.Add(new CMenuCommand("2","MULTI CALL SERVICE DAPR",new EMenuCommandParameterType[0],ExecuteCommandMultiCallServiceDapr));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------