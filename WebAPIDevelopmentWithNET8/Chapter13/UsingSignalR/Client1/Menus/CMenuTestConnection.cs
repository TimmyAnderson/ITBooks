using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client1
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuTestConnection : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuTestConnection()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void PrintSeparator()
		{
			Console.WriteLine(new string('-',80));
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestConnection(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}TestConnection";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandTestConnectionPost(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}TestConnection";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject("MY TEXT");
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLogin(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);
			CMyLoginModel										RawContent=new CMyLoginModel(UserName,Password);

			string												MessageID=CommandID;
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

				PrintSeparator();

				Console.WriteLine($"TOKEN [{Token}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("test","TEST CONNECTION",new EMenuCommandParameterType[0],ExecuteCommandTestConnection));
			CommandsCollection.Add(new CMenuCommand("post","TEST CONNECTION POST",new EMenuCommandParameterType[0],ExecuteCommandTestConnectionPost));
			CommandsCollection.Add(new CMenuCommand("login","LOGIN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandLogin));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------