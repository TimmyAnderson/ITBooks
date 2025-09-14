using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Core;
using Azure.Identity;
using Microsoft.Azure.Cosmos;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuCosmosDBItemsSameType : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! ENDPOINT URL je mozne ziskat z PROPERTY [documentEndpoint] ktoru vracia COMMAND [az cosmosdb show --name mycosmosaccountta --resource-group Chapter08].
		private const string									ENDPOINT_URL="https://mycosmosaccountta.documents.azure.com:443/";
		private const string									DATABASE_NAME="mydb";
		// !!!!! CONTAINER MUSI mat PARTITION KEY nastaveny na PATH [/sex].
		private const string									CONTAINER_NAME="names";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuCosmosDBItemsSameType()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static TokenCredential CreateIdentity()
		{
			TokenCredential										Identity=new DefaultAzureCredential();

			return(Identity);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllItemsLinqSql(string CommandID, object[] Parameters)
		{
			ESex												Sex=((ESex) Parameters[0]);

			if (Sex!=ESex.E_MALE && Sex!=ESex.E_FEMALE)
			{
				throw(new InvalidOperationException("Invalid value of SEX."));
			}

			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					QueryDefinition								Query=new QueryDefinition($"SELECT * FROM {CONTAINER_NAME} WHERE {CONTAINER_NAME}.sex=@Sex").WithParameter("@Sex",Sex.ToString());

					using(FeedIterator<CName> Iterator=Container.GetItemQueryIterator<CName>(Query))
					{
						while(Iterator.HasMoreResults==true)
						{
							FeedResponse<CName>					Response=Iterator.ReadNextAsync().Result;
							CName[]								Items=Response.ToArray();

							if (Items.Length>0)
							{
								for(int Index=0;Index<Items.Length;Index++)
								{
									CName						Item=Items[Index];

									Console.WriteLine($"{(Index+1)}. ID [{Item.ID}] FIRST NAME [{Item.FirstName}] LAST NAME [{Item.LastName}] AGE [{Item.Age}] SEX [{Item.Sex}].");
								}
							}
							else
							{
								Console.WriteLine("NO ITEMS were FOUND.");
							}
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllItemsLinqName(string CommandID, object[] Parameters)
		{
			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					CName[]										Items=Container.GetItemLinqQueryable<CName>(true).ToArray();

					if (Items.Length>0)
					{
						for(int Index=0;Index<Items.Length;Index++)
						{
							CName								Item=Items[Index];

							Console.WriteLine($"{(Index+1)}. ID [{Item.ID}] FIRST NAME [{Item.FirstName}] LAST NAME [{Item.LastName}] AGE [{Item.Age}] SEX [{Item.Sex}].");
						}
					}
					else
					{
						Console.WriteLine("NO ITEMS were FOUND.");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! CONTAINER MUSI mat PARTITION KEY nastaveny na PATH [/sex].
		private void ExecuteCommandInsertItemName(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												FirstName=((string) Parameters[1]);
			string												LastName=((string) Parameters[2]);
			int													Age=((int) Parameters[3]);
			ESex												Sex=((ESex) Parameters[4]);

			if (Sex!=ESex.E_MALE && Sex!=ESex.E_FEMALE)
			{
				throw(new InvalidOperationException("Invalid value of SEX."));
			}

			CName												Item=new CName(ID,FirstName,LastName,Age,Sex.ToString());

			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					ItemResponse<CName>							Response=Container.CreateItemAsync(Item).Result;

					Console.WriteLine($"INSERTING NEW ITEM. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! CONTAINER MUSI mat PARTITION KEY nastaveny na PATH [/sex].
		private void ExecuteCommandUpdateItemName(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												FirstName=((string) Parameters[1]);
			string												LastName=((string) Parameters[2]);
			int													Age=((int) Parameters[3]);
			ESex												Sex=((ESex) Parameters[4]);

			if (Sex!=ESex.E_MALE && Sex!=ESex.E_FEMALE)
			{
				throw(new InvalidOperationException("Invalid value of SEX."));
			}

			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(Sex.ToString());

					ItemResponse<CName>							ItemResponseRead=Container.ReadItemAsync<CName>(ID,PartitionKey).Result;
					CName										Item=ItemResponseRead.Resource;

					Item.FirstName=FirstName;
					Item.LastName=LastName;
					Item.Age=Age;

					ItemResponse<CName>							ItemResponseReplace=Container.ReplaceItemAsync<CName>(Item,ID).Result;

					Console.WriteLine($"UPDATING ITEM. RESPONSE CODE [{ItemResponseReplace.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! CONTAINER MUSI mat PARTITION KEY nastaveny na PATH [/sex].
		private void ExecuteCommandDeleteItemName(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			ESex												Sex=((ESex) Parameters[1]);

			if (Sex!=ESex.E_MALE && Sex!=ESex.E_FEMALE)
			{
				throw(new InvalidOperationException("Invalid value of SEX."));
			}

			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(Sex.ToString());

					ItemResponse<CName>							ItemResponseDelete=Container.DeleteItemAsync<CName>(ID,PartitionKey).Result;

					Console.WriteLine($"DELETING ITEM. RESPONSE CODE [{ItemResponseDelete.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","GET ALL ITEMS SQL",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandGetAllItemsLinqSql));
			CommandsCollection.Add(new CMenuCommand("2","GET ALL ITEMS LINQ",new EMenuCommandParameterType[0],ExecuteCommandGetAllItemsLinqName));
			CommandsCollection.Add(new CMenuCommand("3","INSERT ITEM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandInsertItemName));
			CommandsCollection.Add(new CMenuCommand("4","UPDATE ITEM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandUpdateItemName));
			CommandsCollection.Add(new CMenuCommand("5","DELETE ITEM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT},ExecuteCommandDeleteItemName));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------