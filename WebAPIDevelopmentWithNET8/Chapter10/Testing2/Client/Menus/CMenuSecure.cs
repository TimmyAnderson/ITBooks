using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
using Testing2;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuSecure : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuSecure()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private string PerformLogin(string UserName, string Password)
		{
			CMyLoginModel										RawContent=new CMyLoginModel(UserName,Password);

			string												MessageID="LOGIN";
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}MyAccount/Login";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClientOperationResponse						Response=CMyHttpClient.ExecuteMessage(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				CMyTokenModel									TokenResponse=Response.Content.ConvertToObject<CMyTokenModel>();
				string											Token=TokenResponse.Token;

				return(Token);
			}
			else
			{
				return(null);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandAnonymous(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}MySecure/Anonymous";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandForRole1(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);

			string												AccessToken=PerformLogin(UserName,Password);

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/ForRole1";
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
		private void ExecuteCommandForRole2(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);

			string												AccessToken=PerformLogin(UserName,Password);

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/ForRole2";
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
		private void ExecuteCommandForRole3(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);

			string												AccessToken=PerformLogin(UserName,Password);

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/ForRole3";
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
		private void ExecuteCommandGetClaims(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);

			string												AccessToken=PerformLogin(UserName,Password);

			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/GetClaims";
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

			CommandsCollection.Add(new CMenuCommand("1","ANONYMOUS",new EMenuCommandParameterType[0],ExecuteCommandAnonymous));
			CommandsCollection.Add(new CMenuCommand("2","FOR ROLE 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandForRole1));
			CommandsCollection.Add(new CMenuCommand("3","FOR ROLE 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandForRole2));
			CommandsCollection.Add(new CMenuCommand("4","FOR ROLE 3",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandForRole3));
			CommandsCollection.Add(new CMenuCommand("5","GET CLAIMS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandGetClaims));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------