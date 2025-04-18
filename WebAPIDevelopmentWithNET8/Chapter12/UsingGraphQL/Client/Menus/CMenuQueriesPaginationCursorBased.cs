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
	public sealed class CMenuQueriesPaginationCursorBased : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuQueriesPaginationCursorBased()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private CPaginationResultCursorBased ExecuteQuery(string CommandID, string QueryContent)
		{
			CGraphQLQuery										Query=new CGraphQLQuery(QueryContent);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}graphql";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(Query);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);
			CMyHttpClientOperationResponse						Response=CMyHttpClient.ExecuteMessage(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				CPaginationResultCursorBased					ResponseData=Response.Content.ConvertToObject<CPaginationResultCursorBased>();

				return(ResponseData);
			}
			else
			{
				return(null);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void PrintSeparator()
		{
			Console.WriteLine(new string('-',80));
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void PrintNodes(CPaginationCursorBasedEdge[] Edges)
		{
			foreach(CPaginationCursorBasedEdge Edge in Edges)
			{
				Console.WriteLine($"EDGE CURSOR [{Edge.Cursor}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsFirstPage(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsPaginationCursorBased
					{
						ObjectsPaginationCursorBased(order: { id: ASC })
						{
							pageInfo
							{
								startCursor
								endCursor
								hasPreviousPage
								hasNextPage
							}
							nodes
							{
								id
								value1
								value2
							}
							edges
							{
								cursor
								node
								{
									id
									value1
									value2
								}
							}
							totalCount
						}
					}
				""";

			CPaginationResultCursorBased						Result=ExecuteQuery(CommandID,QueryContent);

			if (Result!=null)
			{
				PrintSeparator();

				PrintNodes(Result.Data.Object.Edges);
			}
			else
			{
				Console.WriteLine("ERROR OCCURED !");
				return;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsNextPageAfter(string CommandID, object[] Parameters)
		{
			string												Cursor=null;

			{
				string											QueryContent=
					"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.Last().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(after: "{{Cursor}}", order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsNextPageAfterBefore(string CommandID, object[] Parameters)
		{
			string												Cursor=null;

			{
				string											QueryContent=
					"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.Last().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(after: "{{Cursor}}", order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.First().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(before: "{{Cursor}}", order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsFirstPageParameterFirst(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsPaginationCursorBased
					{
						ObjectsPaginationCursorBased(first: 3, order: { id: ASC })
						{
							pageInfo
							{
								startCursor
								endCursor
								hasPreviousPage
								hasNextPage
							}
							nodes
							{
								id
								value1
								value2
							}
							edges
							{
								cursor
								node
								{
									id
									value1
									value2
								}
							}
							totalCount
						}
					}
				""";

			CPaginationResultCursorBased						Result=ExecuteQuery(CommandID,QueryContent);

			if (Result!=null)
			{
				PrintSeparator();

				PrintNodes(Result.Data.Object.Edges);
			}
			else
			{
				Console.WriteLine("ERROR OCCURED !");
				return;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsNextPageAfterParameterFirst(string CommandID, object[] Parameters)
		{
			string												Cursor=null;

			{
				string											QueryContent=
					"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(first: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.Last().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(after: "{{Cursor}}", first: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsNextPageAfterBeforeParameterFirst(string CommandID, object[] Parameters)
		{
			string												Cursor=null;

			{
				string											QueryContent=
					"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(first: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.Last().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(after: "{{Cursor}}", first: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.First().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(before: "{{Cursor}}", first: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsFirstPageParameterLast(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsPaginationCursorBased
					{
						ObjectsPaginationCursorBased(last: 3, order: { id: ASC })
						{
							pageInfo
							{
								startCursor
								endCursor
								hasPreviousPage
								hasNextPage
							}
							nodes
							{
								id
								value1
								value2
							}
							edges
							{
								cursor
								node
								{
									id
									value1
									value2
								}
							}
							totalCount
						}
					}
				""";

			CPaginationResultCursorBased						Result=ExecuteQuery(CommandID,QueryContent);

			if (Result!=null)
			{
				PrintSeparator();

				PrintNodes(Result.Data.Object.Edges);
			}
			else
			{
				Console.WriteLine("ERROR OCCURED !");
				return;
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsNextPageBeforeParameterLast(string CommandID, object[] Parameters)
		{
			string												Cursor=null;

			{
				string											QueryContent=
					"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(last: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.First().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(before: "{{Cursor}}", last: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetObjectsNextPageBeforeAfterParameterLast(string CommandID, object[] Parameters)
		{
			string												Cursor=null;

			{
				string											QueryContent=
					"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(last: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.First().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(before: "{{Cursor}}", last: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);

					PrintSeparator();

					Cursor=Result.Data.Object.Edges.Last().Cursor;

					Console.WriteLine($"CURSOR [{Cursor}].");
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}

			PrintSeparator();
			PrintSeparator();
			PrintSeparator();

			{
				string											QueryContent=
					$$"""
						query GetObjectsPaginationCursorBased
						{
							ObjectsPaginationCursorBased(after: "{{Cursor}}", last: 3, order: { id: ASC })
							{
								pageInfo
								{
									startCursor
									endCursor
									hasPreviousPage
									hasNextPage
								}
								nodes
								{
									id
									value1
									value2
								}
								edges
								{
									cursor
									node
									{
										id
										value1
										value2
									}
								}
								totalCount
							}
						}
					""";

				CPaginationResultCursorBased					Result=ExecuteQuery(CommandID,QueryContent);

				if (Result!=null)
				{
					PrintSeparator();

					PrintNodes(Result.Data.Object.Edges);
				}
				else
				{
					Console.WriteLine("ERROR OCCURED !");
					return;
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","FIRST PAGE",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFirstPage));
			CommandsCollection.Add(new CMenuCommand("2","NEXT PAGE - AFTER",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsNextPageAfter));
			CommandsCollection.Add(new CMenuCommand("3","NEXT PAGE - AFTER - BEFORE",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsNextPageAfterBefore));
			CommandsCollection.Add(new CMenuCommand("4","FIRST PAGE - FIRST",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFirstPageParameterFirst));
			CommandsCollection.Add(new CMenuCommand("5","NEXT PAGE - AFTER - FIRST",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsNextPageAfterParameterFirst));
			CommandsCollection.Add(new CMenuCommand("6","NEXT PAGE - AFTER - BEFORE - FIRST",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsNextPageAfterBeforeParameterFirst));
			CommandsCollection.Add(new CMenuCommand("7","FIRST PAGE - LAST",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFirstPageParameterLast));
			CommandsCollection.Add(new CMenuCommand("8","NEXT PAGE - BEFORE - LAST",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsNextPageBeforeParameterLast));
			CommandsCollection.Add(new CMenuCommand("9","NEXT PAGE - BEFORE - AFTER - LAST",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsNextPageBeforeAfterParameterLast));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------