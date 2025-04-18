using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
using Newtonsoft.Json;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuQueriesPaginationOffsetBased : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuQueriesPaginationOffsetBased()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsNoParameters(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsPaginationOffsetBased
					{
						ObjectsPaginationOffsetBased(order: { id: ASC })
						{
							totalCount
							pageInfo
							{
								hasNextPage
								hasPreviousPage
							}
							items
							{
								id
								value1
								value2
							}
						}
					}
				""";

			CGraphQLQuery										Query=new CGraphQLQuery(QueryContent);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}graphql";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(Query);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsParametersSkipAndTake(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsPaginationOffsetBased
					{
						ObjectsPaginationOffsetBased(order: { id: ASC }, skip: 5, take: 10)
						{
							totalCount
							pageInfo
							{
								hasNextPage
								hasPreviousPage
							}
							items
							{
								id
								value1
								value2
							}
						}
					}
				""";

			CGraphQLQuery										Query=new CGraphQLQuery(QueryContent);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}graphql";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(Query);
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

			CommandsCollection.Add(new CMenuCommand("1","NO PARAMETERS",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsNoParameters));
			CommandsCollection.Add(new CMenuCommand("2","PARAMETERS SKIP AND TAKE",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsParametersSkipAndTake));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------