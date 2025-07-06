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
	public sealed class CMenuAzureFunctions : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS_SERVICE_LOCAL="http://localhost:7000/";
		private const string									BASE_ADDRESS_SERVICE_AZURE="https://myfunctionta.azurewebsites.net/";
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									HEADER_NAME_AUTHORIZATION="x-functions-key";
		// !!! ACCESS KEYS je mozne ziskat pomocou COMMAND [az functionapp keys list --name myfunctionta --resource-group MyBook].
		private const string									ACCESS_KEY="6q2aTgYn1_SktrYft4p9oQDdjGw2hn4N2-4EuqibngGQAzFukaedBw==";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuAzureFunctions()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpGetLocal(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/HelloWorld";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpPostLocal(string CommandID, object[] Parameters)
		{
			string												FirstName="Timmy";
			string												LastName="Anderson";
			int													Age=12;
			CName												RawContent=new CName(FirstName,LastName,Age);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/ToUpper";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpGetSecureQueryStringLocal(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/HelloWorldSecure?code={ACCESS_KEY}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpPostSecureQueryStringLocal(string CommandID, object[] Parameters)
		{
			string												FirstName="Timmy";
			string												LastName="Anderson";
			int													Age=12;
			CName												RawContent=new CName(FirstName,LastName,Age);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/ToUpperSecure?code={ACCESS_KEY}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpGetSecureHttpHeaderLocal(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/HelloWorldSecure";
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(HEADER_NAME_AUTHORIZATION,ACCESS_KEY);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpPostSecureHttpHeaderLocal(string CommandID, object[] Parameters)
		{
			string												FirstName="Timmy";
			string												LastName="Anderson";
			int													Age=12;
			CName												RawContent=new CName(FirstName,LastName,Age);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SERVICE_LOCAL}api/ToUpperSecure";
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(HEADER_NAME_AUTHORIZATION,ACCESS_KEY);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpGetAzure(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/HelloWorld";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpPostAzure(string CommandID, object[] Parameters)
		{
			string												FirstName="Timmy";
			string												LastName="Anderson";
			int													Age=12;
			CName												RawContent=new CName(FirstName,LastName,Age);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/ToUpper";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpGetSecureQueryStringAzure(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/HelloWorldSecure?code={ACCESS_KEY}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpPostSecureQueryStringAzure(string CommandID, object[] Parameters)
		{
			string												FirstName="Timmy";
			string												LastName="Anderson";
			int													Age=12;
			CName												RawContent=new CName(FirstName,LastName,Age);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/ToUpperSecure?code={ACCESS_KEY}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpGetSecureHttpHeaderAzure(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/HelloWorldSecure";
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(HEADER_NAME_AUTHORIZATION,ACCESS_KEY);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCallFunctionHttpPostSecureHttpHeaderAzure(string CommandID, object[] Parameters)
		{
			string												FirstName="Timmy";
			string												LastName="Anderson";
			int													Age=12;
			CName												RawContent=new CName(FirstName,LastName,Age);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS_SERVICE_AZURE}api/ToUpperSecure";
			CMyHttpClientHeader									Header=new CMyHttpClientHeader(HEADER_NAME_AUTHORIZATION,ACCESS_KEY);
			CMyHttpClientHeaders								Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{Header});
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
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

			CommandsCollection.Add(new CMenuCommand("1","CALL FUNCTION HTTP GET LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpGetLocal));
			CommandsCollection.Add(new CMenuCommand("2","CALL FUNCTION HTTP POST LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpPostLocal));
			CommandsCollection.Add(new CMenuCommand("3","CALL FUNCTION HTTP GET SECURE QUERY STRING LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpGetSecureQueryStringLocal));
			CommandsCollection.Add(new CMenuCommand("4","CALL FUNCTION HTTP POST SECURE QUERY STRING LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpPostSecureQueryStringLocal));
			CommandsCollection.Add(new CMenuCommand("5","CALL FUNCTION HTTP GET SECURE HTTP HEADER LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpGetSecureHttpHeaderLocal));
			CommandsCollection.Add(new CMenuCommand("6","CALL FUNCTION HTTP POST SECURE HTTP HEADER LOCAL",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpPostSecureHttpHeaderLocal));
			CommandsCollection.Add(new CMenuCommand("7","CALL FUNCTION HTTP GET AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpGetAzure));
			CommandsCollection.Add(new CMenuCommand("8","CALL FUNCTION HTTP POST AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpPostAzure));
			CommandsCollection.Add(new CMenuCommand("9","CALL FUNCTION HTTP GET SECURE QUERY STRING AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpGetSecureQueryStringAzure));
			CommandsCollection.Add(new CMenuCommand("10","CALL FUNCTION HTTP POST SECURE QUERY STRING AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpPostSecureQueryStringAzure));
			CommandsCollection.Add(new CMenuCommand("11","CALL FUNCTION HTTP GET SECURE HTTP HEADER AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpGetSecureHttpHeaderAzure));
			CommandsCollection.Add(new CMenuCommand("12","CALL FUNCTION HTTP POST SECURE HTTP HEADER AZURE",new EMenuCommandParameterType[0],ExecuteCommandCallFunctionHttpPostSecureHttpHeaderAzure));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------