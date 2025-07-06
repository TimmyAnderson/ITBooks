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
	public sealed class CMenuWorkingWithDAPR : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS_LOCAL="https://localhost:7000/";
		// !!!!! Pre DAPR sa pouziva HTTP a MAPPED PORT je PORT [10000].
		// !!!!! DOCKER DESKTOP MUSI byt SPUSTENY.
		private const string									BASE_ADDRESS_DAPR="http://localhost:10000/";
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									DAPR_HEADER_NAME_APPLICATION_ID="dapr-app-id";
		// !!!!! APPLICATION ID je VALUE s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
		private const string									DAPR_HEADER_VALUE_APPLICATION_ID="WorkingWithDAPR";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuWorkingWithDAPR()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestConnectionGetLocal(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_LOCAL}TestConnection";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestConnectionPostLocal(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_LOCAL}TestConnection";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject("MY TEXT");
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestConnectionGetDapr(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_DAPR}TestConnection";

			// !!!!! REQUESTS na DAPR SIDECAR PROCESS MUSIA obsahovat HEADER [dapr-app-id], ktoreho VALUE je APPLICATION ID s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(DAPR_HEADER_NAME_APPLICATION_ID,DAPR_HEADER_VALUE_APPLICATION_ID);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestConnectionPostDapr(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_DAPR}TestConnection";

			// !!!!! REQUESTS na DAPR SIDECAR PROCESS MUSIA obsahovat HEADER [dapr-app-id], ktoreho VALUE je APPLICATION ID s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(DAPR_HEADER_NAME_APPLICATION_ID,DAPR_HEADER_VALUE_APPLICATION_ID);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject("MY TEXT");
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

			CommandsCollection.Add(new CMenuCommand("1","TEST CONNECTION GET LOCAL",new EMenuCommandParameterType[0],ExecuteCommandTestConnectionGetLocal));
			CommandsCollection.Add(new CMenuCommand("2","TEST CONNECTION POST LOCAL",new EMenuCommandParameterType[0],ExecuteCommandTestConnectionPostLocal));
			CommandsCollection.Add(new CMenuCommand("3","TEST CONNECTION GET DAPR",new EMenuCommandParameterType[0],ExecuteCommandTestConnectionGetDapr));
			CommandsCollection.Add(new CMenuCommand("4","TEST CONNECTION POST DAPR",new EMenuCommandParameterType[0],ExecuteCommandTestConnectionPostDapr));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------