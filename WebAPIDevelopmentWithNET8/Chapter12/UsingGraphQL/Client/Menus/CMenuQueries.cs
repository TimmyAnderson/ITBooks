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
		private void ExecuteCommandQueryGetObjectsDataLoaderBatch(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsDataLoaderBatch
					{
						ObjectsDataLoaderBatch
						{
							principalID
							principalValue1
							principalValue2
							Dependent
							{
								ID
								VALUE1
								VALUE2
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
		private void ExecuteCommandQueryGetObjectsDataLoaderGroup(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsDataLoaderGroup
					{
						ObjectsDataLoaderGroup
						{
							principalID
							principalValue1
							principalValue2
							Dependents
							{
								ID
								VALUE1
								VALUE2
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
		private void ExecuteCommandQueryGetObjectsInterface(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectionInterface
					{
						ObjectsMyInterface
						{
							INTERFACE_ID
							INTERFACE_SHARED_VALUE_1
							INTERFACE_SHARED_VALUE_2
							... on CInterfacesMyInterface1
							{
								ID
								INTERFACE_ID
								INTERFACE_SHARED_VALUE_1
								INTERFACE_SHARED_VALUE_2
								SHARED_VALUE_1
								SHARED_VALUE_2
								CLASS_1_VALUE_1
								CLASS_1_VALUE_2
								__typename
							}
							... on CInterfacesMyInterface2
							{
								ID
								INTERFACE_ID
								INTERFACE_SHARED_VALUE_1
								INTERFACE_SHARED_VALUE_2
								SHARED_VALUE_1
								SHARED_VALUE_2
								CLASS_2_VALUE_1
								CLASS_2_VALUE_2
								__typename
							}
							__typename
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
		private void ExecuteCommandQueryGetObjectsUnions(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsUnions
					{
						ObjectsUnions
						{
							__typename
							... on CUnionsMyClass1
							{
								__typename
								ID
								SHARED_VALUE_1
								SHARED_VALUE_2
								CLASS_1_VALUE_1
								CLASS_1_VALUE_2
							}
							... on CUnionsMyClass2
							{
								__typename
								ID
								SHARED_VALUE_1
								SHARED_VALUE_2
								CLASS_2_VALUE_1
								CLASS_2_VALUE_2
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
		private void ExecuteCommandQueryGetObjectsFilteringByConventionString(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsFilteringByConvention
					{
						ObjectsFilteringByConvention(where: { stringValue: { startsWith: "AAA" } })
						{
							id
							stringValue
							intValue
							longValue
							doubleValue
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
		private void ExecuteCommandQueryGetObjectsFilteringByConventionInt(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsFilteringByConvention
					{
						ObjectsFilteringByConvention(where: 
						{
							intValue:
							{
								lt: 104
							}
						})
						{	
							id
							stringValue
							intValue
							longValue
							doubleValue
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
		private void ExecuteCommandQueryGetObjectsFilteringByConventionOperatorOr(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsFilteringByConvention
					{
						ObjectsFilteringByConvention(where: 
						{
							or:
							[
								{
									stringValue:
									{
										startsWith: "AAA"
									}
								},
								{
									stringValue:
									{
										endsWith: "2"
									}
								}
							]
						})
						{
							id
							stringValue
							intValue
							longValue
							doubleValue
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
		private void ExecuteCommandQueryGetObjectsFilteringByFluentAPIImplicit(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsFilteringByFluentAPIImplicit
					{
						ObjectsFilteringByFluentAPIImplicit(where: { stringValue: { startsWith: "AAA" } })
						{
							id
							stringValue
							intValue
							longValue
							doubleValue
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
		private void ExecuteCommandQueryGetObjectsFilteringByFluentAPIExplicit(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsFilteringByFluentAPIExplicit
					{
						ObjectsFilteringByFluentAPIExplicit(where: { stringValue: { startsWith: "AAA" } })
						{
							id
							stringValue
							intValue
							longValue
							doubleValue
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
		private void ExecuteCommandQueryGetObjectsFilteringManuallyNoFilter(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				"""
					query GetObjectsFilteringManually
					{
						ObjectsFilteringManually
						{
							id
							stringValue
							intValue
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
		private void ExecuteCommandQueryGetObjectsFilteringManuallyIDEquals(string CommandID, object[] Parameters)
		{
			int													ID=(int) Parameters[0];

			string												QueryContent=
				$$"""
					query GetObjectsFilteringManually
					{
						ObjectsFilteringManually(where: { ID: { eq: {{ID}} } })
						{
							id
							stringValue
							intValue
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
		private void ExecuteCommandQueryGetObjectsFilteringManuallyIDsIn(string CommandID, object[] Parameters)
		{
			int													ID1=(int) Parameters[0];
			int													ID2=(int) Parameters[1];

			string												QueryContent=
				$$"""
					query GetObjectsFilteringManually
					{
						ObjectsFilteringManually(where: { ID: { in: [{{ID1}},{{ID2}}] } })
						{
							id
							stringValue
							intValue
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
		private void ExecuteCommandQueryGetObjectsSortingByConvention(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsSortingByConvention
					{
						ObjectsSortingByConvention(order: { valueString: ASC, valueInt: DESC })
						{
							id
							valueInt
							valueString
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
		private void ExecuteCommandQueryGetObjectsSortingByFluentAPI(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsSortingByFluentAPI
					{
						ObjectsSortingByFluentAPI(order: { valueString: ASC, valueInt: DESC })
						{
							id
							valueInt
							valueString
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
		private void ExecuteCommandQueryGetObjectsSortingManually1(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsSortingManually
					{
						ObjectsSortingManually
						{
							id
							valueInt
							valueString
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
		private void ExecuteCommandQueryGetObjectsSortingManually2(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsSortingManually
					{
						ObjectsSortingManually(order: { valueString: ASC })
						{
							id
							valueInt
							valueString
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
		private void ExecuteCommandQueryGetObjectsSortingManually3(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsSortingManually
					{
						ObjectsSortingManually(order: { valueInt: DESC })
						{
							id
							valueInt
							valueString
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
		private void ExecuteCommandQueryGetObjectsSortingManually4(string CommandID, object[] Parameters)
		{
			string												QueryContent=
				$$"""
					query GetObjectsSortingManually
					{
						ObjectsSortingManually(order: { valueString: ASC, valueInt: DESC })
						{
							id
							valueInt
							valueString
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
			CommandsCollection.Add(new CMenuCommand("14","GET OBJECTS DATA LOADER BATCH",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsDataLoaderBatch));
			CommandsCollection.Add(new CMenuCommand("15","GET OBJECTS DATA LOADER GROUP",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsDataLoaderGroup));
			CommandsCollection.Add(new CMenuCommand("16","GET OBJECTS INTERFACE",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsInterface));
			CommandsCollection.Add(new CMenuCommand("17","GET OBJECTS UNIONS",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsUnions));
			CommandsCollection.Add(new CMenuCommand("18","GET OBJECTS FILTERING BY CONVENTION - STRING",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFilteringByConventionString));
			CommandsCollection.Add(new CMenuCommand("19","GET OBJECTS FILTERING BY CONVENTION - INT",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFilteringByConventionInt));
			CommandsCollection.Add(new CMenuCommand("20","GET OBJECTS FILTERING BY CONVENTION - OPERATOR OR",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFilteringByConventionOperatorOr));
			CommandsCollection.Add(new CMenuCommand("21","GET OBJECTS FILTERING BY FLUENT API IMPLICIT - STRING",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFilteringByFluentAPIImplicit));
			CommandsCollection.Add(new CMenuCommand("22","GET OBJECTS FILTERING BY FLUENT API EXPLICIT - STRING",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFilteringByFluentAPIExplicit));
			CommandsCollection.Add(new CMenuCommand("23","GET OBJECTS FILTERING MANUALLY - NO FILTER",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsFilteringManuallyNoFilter));
			CommandsCollection.Add(new CMenuCommand("24","GET OBJECTS FILTERING MANUALLY - FILTER - ID EQUALS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandQueryGetObjectsFilteringManuallyIDEquals));
			CommandsCollection.Add(new CMenuCommand("25","GET OBJECTS FILTERING MANUALLY - FILTER - IDs IN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandQueryGetObjectsFilteringManuallyIDsIn));
			CommandsCollection.Add(new CMenuCommand("26","GET OBJECTS SORTING BY CONVENTION",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsSortingByConvention));
			CommandsCollection.Add(new CMenuCommand("27","GET OBJECTS SORTING BY FLUENT API",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsSortingByFluentAPI));
			CommandsCollection.Add(new CMenuCommand("28","GET OBJECTS SORTING MANUALLY 1",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsSortingManually1));
			CommandsCollection.Add(new CMenuCommand("29","GET OBJECTS SORTING MANUALLY 2",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsSortingManually2));
			CommandsCollection.Add(new CMenuCommand("30","GET OBJECTS SORTING MANUALLY 3",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsSortingManually3));
			CommandsCollection.Add(new CMenuCommand("31","GET OBJECTS SORTING MANUALLY 4",new EMenuCommandParameterType[0],ExecuteCommandQueryGetObjectsSortingManually4));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------