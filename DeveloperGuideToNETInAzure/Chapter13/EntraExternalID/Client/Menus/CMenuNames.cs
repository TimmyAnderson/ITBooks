using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EntraExternalIDWebAPI;
using Microsoft.Identity.Client;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuNames : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! SETTINGS sa ziskava MENU [App registrations -> Overview] z VALUE [Application (client) ID] pre CLIENT PROGRAM.
		private static readonly string							CLIENT_ID="3eaa4193-5f8c-4750-92d4-043f5b779543";
		// !!! SETTINGS sa ziskava z VALUE [Value] po vytvoreni CLIENT SECRET pre CLIENT PROGRAM.
		private static readonly string							CLIENT_SECRET="tTY8Q~tu_ehOF_n_V1FuyLKABV~om6RMydnvPdpC";
		// !!! SETTINGS sa ziskava MENU [App registrations -> Overview] z VALUE [Application (client) ID] pre ASP.NET CORE API PROGRAM.
		private static readonly string[]						SCOPES=new string[]{"api://44cbea37-c6ee-4877-aa3b-8563198c769e/.default"};
		private static readonly string							TENANT_NAME="MyEntraExternalID";
		private static readonly string							AUTHORITY=$"https://{TENANT_NAME}.ciamlogin.com/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuNames()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private string GetAccessToken()
		{
			ConfidentialClientApplicationBuilder				Builder=ConfidentialClientApplicationBuilder.Create(CLIENT_ID);

			Builder.WithAuthority(AUTHORITY);
			Builder.WithClientSecret(CLIENT_SECRET);

			IConfidentialClientApplication						ConfidentialClientApplication=Builder.Build();

			AcquireTokenForClientParameterBuilder				AcquireTokenForClientParameterBuilder=ConfidentialClientApplication.AcquireTokenForClient(SCOPES);

			AuthenticationResult								AuthenticationResult=AcquireTokenForClientParameterBuilder.ExecuteAsync().Result;

			string												AccessToken=AuthenticationResult.AccessToken;

			return(AccessToken);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetNames(string CommandID, object[] Parameters)
		{
			string												AccessToken=GetAccessToken();

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}Names/GetNames";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",AccessToken);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
			else
			{
				Console.WriteLine("Can't get ACCESS TOKEN.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												AccessToken=GetAccessToken();

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}Names/GetName?ID={ID}";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",AccessToken);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
			else
			{
				Console.WriteLine("Can't get ACCESS TOKEN.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertName(string CommandID, object[] Parameters)
		{
			string												FirstName=((string) Parameters[0]);
			string												LastName=((string) Parameters[1]);
			int													Age=((int) Parameters[2]);
			ESex												Sex=((ESex) Parameters[3]);
			CName												RawContent=new CName(FirstName,LastName,Age,Sex);

			string												AccessToken=GetAccessToken();

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_POST;
				string											URL=$"{BASE_ADDRESS}Names/InsertName";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",AccessToken);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
			else
			{
				Console.WriteLine("Can't get ACCESS TOKEN.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);
			string												FirstName=((string) Parameters[1]);
			string												LastName=((string) Parameters[2]);
			int													Age=((int) Parameters[3]);
			ESex												Sex=((ESex) Parameters[4]);
			CName												RawContent=new CName(ID,FirstName,LastName,Age,Sex);

			string												AccessToken=GetAccessToken();

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_PUT;
				string											URL=$"{BASE_ADDRESS}Names/UpdateName";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",AccessToken);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
			else
			{
				Console.WriteLine("Can't get ACCESS TOKEN.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												AccessToken=GetAccessToken();

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_DELETE;
				string											URL=$"{BASE_ADDRESS}Names/DeleteName?ID={ID}";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",AccessToken);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
			else
			{
				Console.WriteLine("Can't get ACCESS TOKEN.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","GET NAMES",new EMenuCommandParameterType[0],ExecuteCommandGetNames));
			CommandsCollection.Add(new CMenuCommand("2","GET NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetName));
			CommandsCollection.Add(new CMenuCommand("3","INSERT NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandInsertName));
			CommandsCollection.Add(new CMenuCommand("4","UPDATE NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandUpdateName));
			CommandsCollection.Add(new CMenuCommand("5","DELETE NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandDeleteName));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------