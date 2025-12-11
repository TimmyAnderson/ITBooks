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
	public sealed class CMenuDotNetRateLimiter : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:8000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuDotNetRateLimiter()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRateLimiterMyMethod(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}DotNetRateLimiter/MyMethod?ID={ID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRateLimiterMyMethods(string CommandID, object[] Parameters)
		{
			int													NumberOfRequest=((int) Parameters[0]);

			for(int Index=0;Index<NumberOfRequest;Index++)
			{
				string											ID=$"MY ID [{(Index+1)}]";

				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}DotNetRateLimiter/MyMethod?ID={ID}";
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

			CommandsCollection.Add(new CMenuCommand("1","CALL METHOD",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandRateLimiterMyMethod));
			CommandsCollection.Add(new CMenuCommand("2","CALL METHODS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandRateLimiterMyMethods));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------