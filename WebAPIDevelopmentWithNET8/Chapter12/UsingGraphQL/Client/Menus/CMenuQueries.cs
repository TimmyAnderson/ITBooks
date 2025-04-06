using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
using Newtonsoft.Json;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuQueries : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuQueries()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandQueryGetNames(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetNames
					{
						myNames
						{
							id
							firstName
							lastName
							age
							sex
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
		private void ExecuteCommandQueryGetName(string CommandID, object[] Parameters)
		{
			int													ID=(int) Parameters[0];

			string												QueryContent=
				$$"""
					query GetName
					{
						myName(id:{{ID}})
						{
							id
							firstName
							lastName
							age
							sex
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
		private void ExecuteCommandQueryGetNameWithParameters(string CommandID, object[] Parameters)
		{
			int													ID=(int) Parameters[0];

			string												QueryContent=
				$$"""
					query GetNameWithParameters($MyId: Int!)
					{
						myName(id: $MyId)
						{
							id
							firstName
							lastName
							age
							sex
						}
					}				
				""";

			CVariablesNamesID									Variables=new CVariablesNamesID(ID);

			CGraphQLQuery										Query=new CGraphQLQuery(QueryContent,Variables);

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
		private void ExecuteCommandMutationAddName(string CommandID, object[] Parameters)
		{
			string												FirstName=(string) Parameters[0];
			string												LastName=(string) Parameters[1];
			int													Age=(int) Parameters[2];
			int													RawSex=(int) Parameters[3];
			string												Sex;

			if (RawSex==1)
			{
				Sex="E_MALE";
			}
			else if (RawSex==2)
			{
				Sex="E_FEMALE";
			}
			else
			{
				Console.WriteLine($"UNSUPPORTED VALUE for SEX [{RawSex}].");
				return;
			}

			string												QueryContent=
				$$"""
					mutation AddName
					{
						myAddName(myInput:
						{
							firstName: "{{FirstName}}", 
							lastName: "{{LastName}}", 
							age: {{Age}}, 
							sex: {{Sex}} 
						})
						{
							id
							firstName
							lastName
							age
							sex
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
		private void ExecuteCommandQueryGetTypes(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetTypes
					{
						myTypes
						{
							valueByte
							valueShort
							valueInt
							valueLong
							valueDecimal
							valueDouble
							valueString
							valueDateTime
							valueDateTimeOffset
							valueTimeSpan
							valueUri
							valueGuid
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
		private void ExecuteCommandQueryGetRelations11(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetRelations11
					{
						myRelations11
						{
							valueParent1
							valueParent2
							valueChild
							{
								valueChild1
								valueChild2
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
		private void ExecuteCommandQueryGetRelations1N(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetRelations1N
					{
						myRelations1N
						{
							valueParent1
							valueParent2
							valueChildren
							{
								valueChild1
								valueChild2
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
		private void ExecuteCommandQueryGetObjectsOneToOne1(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsOneToOne
					{
						ObjectsOneToOne1
						{
							principalID
							principalValue
							myOneToOneDependent1
							{
								ID
								VALUE
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
		private void ExecuteCommandQueryGetObjectOneToOne1(string CommandID, object[] Parameters)
		{
			int													ID=(int) Parameters[0];

			string												QueryContent=
				$$"""
					query GetObjectOneToOne
					{
						ObjectOneToOne1(id: {{ID}})
						{
							principalID
							principalValue
							myOneToOneDependent1
							{
								ID
								VALUE
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
		private void ExecuteCommandQueryGetObjectsOneToOne2(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsOneToOne
					{
						ObjectsOneToOne2
						{
							principalID
							principalValue
							myOneToOneDependent2
							{
								ID
								VALUE
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
		private void ExecuteCommandQueryGetObjectOneToOne2(string CommandID, object[] Parameters)
		{
			int													ID=(int) Parameters[0];

			string												QueryContent=
				$$"""
					query GetObjectOneToOne
					{
						ObjectOneToOne2(id: {{ID}})
						{
							principalID
							principalValue
							myOneToOneDependent2
							{
								ID
								VALUE
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
		private void ExecuteCommandQueryGetObjectsOneToMany(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsOneToMany
					{
						ObjectsOneToMany
						{
							principalID
							principalValue
							Dependents
							{
								ID
								VALUE
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
		private void ExecuteCommandQueryGetObjectOneToMany(string CommandID, object[] Parameters)
		{
			int													ID=(int) Parameters[0];

			string												QueryContent=
				$$"""
					query GetObjectOneToMany
					{
						ObjectOneToMany(id: {{ID}})
						{
							principalID
							principalValue
							Dependents
							{
								ID
								VALUE
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

			CommandsCollection.Add(new CMenuCommand("1","GET NAMES",new EMenuCommandParameterType[0],ExecuteCommandQueryGetNames));
			CommandsCollection.Add(new CMenuCommand("2","GET NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandQueryGetName));
			CommandsCollection.Add(new CMenuCommand("3","GET NAME with PARAMETERS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandQueryGetNameWithParameters));
			CommandsCollection.Add(new CMenuCommand("4","ADD NAME",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandMutationAddName));
			CommandsCollection.Add(new CMenuCommand("5","GET TYPES",new EMenuCommandParameterType[0],ExecuteCommandQueryGetTypes));
			CommandsCollection.Add(new CMenuCommand("6","GET RELATIONS 1:1",new EMenuCommandParameterType[0],ExecuteCommandQueryGetRelations11));
			CommandsCollection.Add(new CMenuCommand("7","GET RELATIONS 1:N",new EMenuCommandParameterType[0],ExecuteCommandQueryGetRelations1N));
			CommandsCollection.Add(new CMenuCommand("8","GET OBJECTS ONE TO ONE 1",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsOneToOne1));
			CommandsCollection.Add(new CMenuCommand("9","GET OBJECT ONE TO ONE 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandQueryGetObjectOneToOne1));
			CommandsCollection.Add(new CMenuCommand("10","GET OBJECTS ONE TO ONE 2",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsOneToOne2));
			CommandsCollection.Add(new CMenuCommand("11","GET OBJECT ONE TO ONE 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandQueryGetObjectOneToOne2));
			CommandsCollection.Add(new CMenuCommand("12","GET OBJECTS ONE TO MANY",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsOneToMany));
			CommandsCollection.Add(new CMenuCommand("13","GET OBJECT ONE TO MANY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandQueryGetObjectOneToMany));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------