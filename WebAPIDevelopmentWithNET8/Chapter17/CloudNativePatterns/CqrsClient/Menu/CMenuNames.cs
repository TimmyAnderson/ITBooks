using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CqrsCore;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace CqrsClient
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
		private void ExecuteCommandGetNames(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}Names/GetNames";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}Names/GetName?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertName(string CommandID, object[] Parameters)
		{
			string												FirstName=((string) Parameters[0]);
			string												LastName=((string) Parameters[1]);
			int													Age=((int) Parameters[2]);
			EDtoSex												Sex=((EDtoSex) Parameters[3]);
			CDtoNameToInsert									RawContent=new CDtoNameToInsert(FirstName,LastName,Age,Sex);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}Names/InsertName";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);
			string												FirstName=((string) Parameters[1]);
			string												LastName=((string) Parameters[2]);
			int													Age=((int) Parameters[3]);
			EDtoSex												Sex=((EDtoSex) Parameters[4]);
			CDtoNameToUpdate									RawContent=new CDtoNameToUpdate(ID,FirstName,LastName,Age,Sex);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_PUT;
			string												URL=$"{BASE_ADDRESS}Names/UpdateName";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteName(string CommandID, object[] Parameters)
		{
			int													ID=((int) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_DELETE;
			string												URL=$"{BASE_ADDRESS}Names/DeleteName?ID={ID}";
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