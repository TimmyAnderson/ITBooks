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
	public sealed class CMenuPollyRateLimiter : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuPollyRateLimiter()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRateLimiterMyMethod1(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			int													NumberOfRequests=((int) Parameters[1]);
			int													PauseInSeconds=((int) Parameters[2]);
			int													NumberOfBatches=((int) Parameters[3]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}PollyRateLimiter/RateLimiterMethod1?ID={ID}&NumberOfRequests={NumberOfRequests}&PauseInSeconds={PauseInSeconds}&NumberOfBatches={NumberOfBatches}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRateLimiterMyMethod2(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			int													NumberOfRequests=((int) Parameters[1]);
			int													PauseInSeconds=((int) Parameters[2]);
			int													NumberOfBatches=((int) Parameters[3]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}PollyRateLimiter/RateLimiterMethod2?ID={ID}&NumberOfRequests={NumberOfRequests}&PauseInSeconds={PauseInSeconds}&NumberOfBatches={NumberOfBatches}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRateLimiterMyMethod3(string CommandID, object[] Parameters)
		{
			int													NumberOfRequests=((int) Parameters[0]);

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				string											ID=$"MY ID [{(Index+1)}]";

				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}PollyRateLimiter/RateLimiterMethod3?ID={ID}";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRateLimiterMyMethod4(string CommandID, object[] Parameters)
		{
			int													NumberOfRequests=((int) Parameters[0]);

			for(int Index=0;Index<NumberOfRequests;Index++)
			{
				string											ID=$"MY ID [{(Index+1)}]";

				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}PollyRateLimiter/RateLimiterMethod4?ID={ID}";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","CALL MY METHOD 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandRateLimiterMyMethod1));
			CommandsCollection.Add(new CMenuCommand("2","CALL MY METHOD 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandRateLimiterMyMethod2));
			CommandsCollection.Add(new CMenuCommand("3","CALL MY METHOD 3",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandRateLimiterMyMethod3));
			CommandsCollection.Add(new CMenuCommand("4","CALL MY METHOD 4",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandRateLimiterMyMethod4));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------