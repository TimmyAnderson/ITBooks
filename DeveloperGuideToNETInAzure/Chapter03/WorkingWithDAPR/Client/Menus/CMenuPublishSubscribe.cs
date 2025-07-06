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
	public sealed class CMenuPublishSubscribe : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS_SUBSCRIBER_SERVICE_1_LOCAL="http://localhost:5011/";
		private const string									BASE_ADDRESS_SUBSCRIBER_SERVICE_2_LOCAL="http://localhost:5012/";
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! DOCKER DESKTOP MUSI byt SPUSTENY.
		// !!!!! Pre DAPR sa pouziva HTTP a MAPPED PORT je PORT [10000].
		private const string									BASE_ADDRESS_PUBLISHER_SERVICE_DAPR="http://localhost:10000/";
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									DAPR_HEADER_NAME_APPLICATION_ID="dapr-app-id";
		// !!!!! APPLICATION ID je VALUE s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
		private const string									DAPR_HEADER_VALUE_APPLICATION_ID_PUBLISHER_SERVICE="MY_PUBLISHER_SERVICE";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuPublishSubscribe()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallSubscriberService1Local(string CommandID, object[] Parameters)
		{
			CMessage											Message=new CMessage(101,1001);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SUBSCRIBER_SERVICE_1_LOCAL}MySubscriberService1";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(Message);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallSubscriberService2Local(string CommandID, object[] Parameters)
		{
			CMessage											Message=new CMessage(102,1002);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SUBSCRIBER_SERVICE_2_LOCAL}MySubscriberService2";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(Message);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallPublisherServiceDapr(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_PUBLISHER_SERVICE_DAPR}MyPublisherService?Value1=10&Value2=20";

			// !!!!! REQUESTS na DAPR SIDECAR PROCESS MUSIA obsahovat HEADER [dapr-app-id], ktoreho VALUE je APPLICATION ID s ktorou bol PROGRAM vyuzivajuci DAPR spusteny pomocou COMMAND [dapr run].
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(DAPR_HEADER_NAME_APPLICATION_ID,DAPR_HEADER_VALUE_APPLICATION_ID_PUBLISHER_SERVICE);
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

			CommandsCollection.Add(new CMenuCommand("1","CALL SUBSCRIBER SERVICE 1 LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallSubscriberService1Local));
			CommandsCollection.Add(new CMenuCommand("2","CALL SUBSCRIBER SERVICE 2 LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallSubscriberService2Local));
			CommandsCollection.Add(new CMenuCommand("3","CALL PUBLISHER SERVICE DAPR",new EMenuCommandParameterType[0],ExecuteCommandCallPublisherServiceDapr));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------