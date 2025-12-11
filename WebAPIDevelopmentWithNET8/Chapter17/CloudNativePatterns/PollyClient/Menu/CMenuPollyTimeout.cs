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
	public sealed class CMenuPollyTimeout : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuPollyTimeout()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandPollyTimeoutCallSlowMethod1(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			int													TimeoutInMS=((int) Parameters[1]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}PollyTimeout/CallSlowMethod1?ID={ID}&TimeoutInMS={TimeoutInMS}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandPollyTimeoutCallSlowMethod2(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			int													TimeoutInMS=((int) Parameters[1]);
			int													WaitTimeoutInMS=((int) Parameters[2]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}PollyTimeout/CallSlowMethod2?ID={ID}&TimeoutInMS={TimeoutInMS}&WaitTimeoutInMS={WaitTimeoutInMS}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandPollyTimeoutCallSlowMethod3(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			int													TimeoutInMS=((int) Parameters[1]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}PollyTimeout/CallSlowMethod3?ID={ID}&TimeoutInMS={TimeoutInMS}";
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

			CommandsCollection.Add(new CMenuCommand("1","POLLY TIMEOUT 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT},ExecuteCommandPollyTimeoutCallSlowMethod1));
			CommandsCollection.Add(new CMenuCommand("2","POLLY TIMEOUT 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandPollyTimeoutCallSlowMethod2));
			CommandsCollection.Add(new CMenuCommand("3","POLLY TIMEOUT 3",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT},ExecuteCommandPollyTimeoutCallSlowMethod3));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------