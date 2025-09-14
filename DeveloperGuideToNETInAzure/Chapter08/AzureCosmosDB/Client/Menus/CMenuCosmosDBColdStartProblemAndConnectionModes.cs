using System;
using System.Collections.Generic;
using System.Diagnostics;
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
	public sealed class CMenuCosmosDBColdStartProblemAndConnectionModes : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									ENDPOINT_URL="https://mycosmosaccountta.documents.azure.com:443/";
		private const string									AUTHORIZATION_KEY="51z8O9MMit3An3m16wbFlRbzUX3uuU9XQic0WOBSb8E2tcXMvymbSTbF2AHazJdOzucqmx8L0lpnACDbJYRkeg==;";
		private const string									CONNECTION_STRING=$"AccountEndpoint={ENDPOINT_URL};AccountKey={AUTHORIZATION_KEY}";
		private const string									DATABASE_NAME="mydb";
		private const string									CONTAINER_NAME="names";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuCosmosDBColdStartProblemAndConnectionModes()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllItemsPreInitializeConnection(string CommandID, object[] Parameters)
		{
			try
			{
				Stopwatch										Stopwatch=new Stopwatch();

				Stopwatch.Start();

				List<(string DatabaseID, string ContainerID)>	DatabasesContainersList=new List<(string DatabaseID, string ContainerID)>();
				(string DatabaseID, string ContainerID)			DatabasesContainers=(DATABASE_NAME,CONTAINER_NAME);

				DatabasesContainersList.Add(DatabasesContainers);

				Console.WriteLine($"TIME 1 [{Stopwatch.ElapsedTicks}].");

				using(CosmosClient Client=CosmosClient.CreateAndInitializeAsync(CONNECTION_STRING,DatabasesContainersList).Result)
				{
					Console.WriteLine($"TIME 2 [{Stopwatch.ElapsedTicks}].");

					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					Console.WriteLine($"TIME 3 [{Stopwatch.ElapsedTicks}].");

					CName[]										Items=Container.GetItemLinqQueryable<CName>(true).ToArray();

					Console.WriteLine($"TIME 4 [{Stopwatch.ElapsedTicks}].");

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

				Stopwatch.Stop();
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllItemsGatewayMode(string CommandID, object[] Parameters)
		{
			try
			{
				Stopwatch										Stopwatch=new Stopwatch();

				Stopwatch.Start();

				CosmosClientOptions								CosmosClientOptions=new CosmosClientOptions();

				CosmosClientOptions.ConnectionMode=ConnectionMode.Gateway;

				Console.WriteLine($"TIME 1 [{Stopwatch.ElapsedTicks}].");

				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING,CosmosClientOptions))
				{
					Console.WriteLine($"TIME 2 [{Stopwatch.ElapsedTicks}].");

					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					Console.WriteLine($"TIME 3 [{Stopwatch.ElapsedTicks}].");

					CName[]										Items=Container.GetItemLinqQueryable<CName>(true).ToArray();

					Console.WriteLine($"TIME 4 [{Stopwatch.ElapsedTicks}].");

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

				Stopwatch.Stop();
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllItemsDirectMode(string CommandID, object[] Parameters)
		{
			try
			{
				Stopwatch										Stopwatch=new Stopwatch();

				Stopwatch.Start();

				CosmosClientOptions								CosmosClientOptions=new CosmosClientOptions();

				CosmosClientOptions.ConnectionMode=ConnectionMode.Direct;

				Console.WriteLine($"TIME 1 [{Stopwatch.ElapsedTicks}].");

				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING,CosmosClientOptions))
				{
					Console.WriteLine($"TIME 2 [{Stopwatch.ElapsedTicks}].");

					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					Console.WriteLine($"TIME 3 [{Stopwatch.ElapsedTicks}].");

					CName[]										Items=Container.GetItemLinqQueryable<CName>(true).ToArray();

					Console.WriteLine($"TIME 4 [{Stopwatch.ElapsedTicks}].");

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

				Stopwatch.Stop();
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertItem(string CommandID, object[] Parameters)
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

			try
			{
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
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
		private void ExecuteCommandUpdateItem(string CommandID, object[] Parameters)
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

			try
			{
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
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
		private void ExecuteCommandDeleteItem(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			ESex												Sex=((ESex) Parameters[1]);

			if (Sex!=ESex.E_MALE && Sex!=ESex.E_FEMALE)
			{
				throw(new InvalidOperationException("Invalid value of SEX."));
			}

			try
			{
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
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

			CommandsCollection.Add(new CMenuCommand("1","GET ALL ITEMS - PREINITIALIZE CONNECTION",new EMenuCommandParameterType[0],ExecuteCommandGetAllItemsPreInitializeConnection));
			CommandsCollection.Add(new CMenuCommand("2","GET ALL ITEMS - GATEWAY MODE",new EMenuCommandParameterType[0],ExecuteCommandGetAllItemsGatewayMode));
			CommandsCollection.Add(new CMenuCommand("3","GET ALL ITEMS - DIRECT MODE",new EMenuCommandParameterType[0],ExecuteCommandGetAllItemsDirectMode));
			CommandsCollection.Add(new CMenuCommand("4","INSERT ITEM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandInsertItem));
			CommandsCollection.Add(new CMenuCommand("5","UPDATE ITEM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandUpdateItem));
			CommandsCollection.Add(new CMenuCommand("6","DELETE ITEM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT},ExecuteCommandDeleteItem));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------