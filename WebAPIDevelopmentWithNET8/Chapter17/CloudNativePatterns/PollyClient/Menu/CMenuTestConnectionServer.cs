using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace PollyClient
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuTestConnectionServer : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:8000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuTestConnectionServer()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
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
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("test","TEST CONNECTION",new EMenuCommandParameterType[0],ExecuteCommandTestConnection));
			CommandsCollection.Add(new CMenuCommand("post","TEST CONNECTION POST",new EMenuCommandParameterType[0],ExecuteCommandTestConnectionPost));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------