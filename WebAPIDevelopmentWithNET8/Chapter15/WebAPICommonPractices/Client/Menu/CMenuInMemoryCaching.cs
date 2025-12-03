using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuInMemoryCaching : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuInMemoryCaching()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandAbsoluteExpiration(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}InMemoryCaching/AbsoluteExpiration";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
			HttpClientHandler									ClientHandler=new HttpClientHandler();

			CMyHttpClient.ExecuteMessage(Request,ClientHandler);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSlidingExpiration(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}InMemoryCaching/SlidingExpiration";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
			HttpClientHandler									ClientHandler=new HttpClientHandler();

			CMyHttpClient.ExecuteMessage(Request,ClientHandler);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetOrCreateInCache(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}InMemoryCaching/GetOrCreateInCache";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
			HttpClientHandler									ClientHandler=new HttpClientHandler();

			CMyHttpClient.ExecuteMessage(Request,ClientHandler);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCleanCache(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}InMemoryCaching/CleanCache";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
			HttpClientHandler									ClientHandler=new HttpClientHandler();

			CMyHttpClient.ExecuteMessage(Request,ClientHandler);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","IN MEMORY CACHING ABSOLUTE EXPIRATION",new EMenuCommandParameterType[0],ExecuteCommandAbsoluteExpiration));
			CommandsCollection.Add(new CMenuCommand("2","IN MEMORY CACHING SLIDING EXPIRATION",new EMenuCommandParameterType[0],ExecuteCommandSlidingExpiration));
			CommandsCollection.Add(new CMenuCommand("3","IN MEMORY CACHING GET OR CREATE",new EMenuCommandParameterType[0],ExecuteCommandGetOrCreateInCache));
			CommandsCollection.Add(new CMenuCommand("4","IN MEMORY CACHING CLEAN CACHE",new EMenuCommandParameterType[0],ExecuteCommandCleanCache));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------