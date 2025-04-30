using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataAccess3Web;
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
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuNames()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetNames1(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}Names/GetNames1";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetNames2(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}Names/GetNames2";
			CMyHttpClientHeaders								Headers=null;
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

			CommandsCollection.Add(new CMenuCommand("1","GET NAMES 1",new EMenuCommandParameterType[0],ExecuteCommandGetNames1));
			CommandsCollection.Add(new CMenuCommand("2","GET NAMES 2",new EMenuCommandParameterType[0],ExecuteCommandGetNames2));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------