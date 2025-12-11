using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace PollyClient
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuPollyCircuitBreaker : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuPollyCircuitBreaker()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCircuitBreakerMyMethod1(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			int													NumberOfRequests=((int) Parameters[1]);
			int													PauseInSeconds=((int) Parameters[2]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}PollyCircuitBreaker/CircuitBreakerMethod1?ID={ID}&NumberOfRequests={NumberOfRequests}&PauseInSeconds={PauseInSeconds}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCircuitBreakerMyMethod2(string CommandID, object[] Parameters)
		{
			int													NumberOfRequests=((int) Parameters[0]);
			int													PauseInSeconds=((int) Parameters[1]);

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				string											ID=$"MY ID [{(Index+1)}]";

				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}PollyCircuitBreaker/CircuitBreakerMethod2?ID={ID}";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);

				Thread.Sleep(1000*PauseInSeconds);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","CALL MY METHOD 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandCircuitBreakerMyMethod1));
			CommandsCollection.Add(new CMenuCommand("2","CALL MY METHOD 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandCircuitBreakerMyMethod2));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------