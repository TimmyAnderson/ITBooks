using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Azure.Core;
using Azure.Identity;
using Microsoft.Azure.Cosmos;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuCosmosDBItemsDifferentTypes : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		// !!! ENDPOINT URL je mozne ziskat z PROPERTY [documentEndpoint] ktoru vracia COMMAND [az cosmosdb show --name mycosmosaccountta --resource-group Chapter08].
		private const string									ENDPOINT_URL="https://mycosmosaccountta.documents.azure.com:443/";
		private const string									DATABASE_NAME="mydb";
		// !!!!! CONTAINER MUSI mat PARTITION KEY nastaveny na PATH [/userID].
		private const string									CONTAINER_NAME="differenttypes";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private Thread											MThread;
		private ManualResetEvent								MManualResetEvent;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuCosmosDBItemsDifferentTypes()
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
		private Task ChangesHandlerItem1(IReadOnlyCollection<CUserItem1> Changes, CancellationToken CancellationToken)
		{
			foreach(CUserItem1 Change in Changes)
			{
				if (Change.Type==EUserInfoType.E_TYPE_1)
				{
					Console.WriteLine($"ITEM 1 CHANGED. ID [{Change.ID}] USER ID [{Change.UserID}] PARAMETER 1 [{Change.Parameter1}] PARAMETER 2 [{Change.Parameter2}].");
				}
			}

			return(Task.CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task ChangesHandlerItem2(IReadOnlyCollection<CUserItem2> Changes, CancellationToken CancellationToken)
		{
			foreach(CUserItem2 Change in Changes)
			{
				if (Change.Type==EUserInfoType.E_TYPE_2)
				{
					Console.WriteLine($"ITEM 2 CHANGED. ID [{Change.ID}] USER ID [{Change.UserID}] PARAMETER 1 [{Change.Parameter1}] PARAMETER 2 [{Change.Parameter2}] PARAMETER 3 [{Change.Parameter3}].");
				}
			}

			return(Task.CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task ChangesHandlerItem3(IReadOnlyCollection<CUserItem3> Changes, CancellationToken CancellationToken)
		{
			foreach(CUserItem3 Change in Changes)
			{
				if (Change.Type==EUserInfoType.E_TYPE_3)
				{
					Console.WriteLine($"ITEM 3 CHANGED. ID [{Change.ID}] USER ID [{Change.UserID}] PARAMETER 1 [{Change.Parameter1}] PARAMETER 2 [{Change.Parameter2}] PARAMETER 3 [{Change.Parameter3}] PARAMETER 4 [{Change.Parameter4}].");
				}
			}

			return(Task.CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ChangeFeedThread()
		{
			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					Console.WriteLine($"CHANGE FEED PROCCESSORS STARTING.");

					ChangeFeedProcessor							ChangeFeedProcessor1=Container.GetChangeFeedProcessorBuilder<CUserItem1>("Processor1",ChangesHandlerItem1).WithInstanceName("Instance1").WithInMemoryLeaseContainer().Build();
					ChangeFeedProcessor							ChangeFeedProcessor2=Container.GetChangeFeedProcessorBuilder<CUserItem2>("Processor2",ChangesHandlerItem2).WithInstanceName("Instance2").WithInMemoryLeaseContainer().Build();
					ChangeFeedProcessor							ChangeFeedProcessor3=Container.GetChangeFeedProcessorBuilder<CUserItem3>("Processor3",ChangesHandlerItem3).WithInstanceName("Instance3").WithInMemoryLeaseContainer().Build();

					ChangeFeedProcessor1.StartAsync().Wait();
					ChangeFeedProcessor2.StartAsync().Wait();
					ChangeFeedProcessor3.StartAsync().Wait();

					Console.WriteLine($"CHANGE FEED PROCCESSORS STARTED.");

					MManualResetEvent.WaitOne();

					Console.WriteLine($"CHANGE FEED PROCCESSORS STOPPING.");

					ChangeFeedProcessor1.StopAsync().Wait();
					ChangeFeedProcessor2.StopAsync().Wait();
					ChangeFeedProcessor3.StopAsync().Wait();

					Console.WriteLine($"CHANGE FEED PROCCESSORS STOPPED.");
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
		private void ExecuteCommandGetAllItems1(string CommandID, object[] Parameters)
		{
			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					CUserItem1[]								Items=Container.GetItemLinqQueryable<CUserItem1>(true).Where(P => P.Type==EUserInfoType.E_TYPE_1).ToArray();

					if (Items.Length>0)
					{
						for(int Index=0;Index<Items.Length;Index++)
						{
							CUserItem1							Item=Items[Index];

							Console.WriteLine($"{(Index+1)}. ITEM 1 - ID [{Item.ID}] USER ID [{Item.UserID}] PARAMETER 1 [{Item.Parameter1}] PARAMETER 2 [{Item.Parameter2}].");
						}
					}
					else
					{
						Console.WriteLine("NO ITEMS 1 FOUND.");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllItems2(string CommandID, object[] Parameters)
		{
			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					CUserItem2[]								Items=Container.GetItemLinqQueryable<CUserItem2>(true).Where(P => P.Type==EUserInfoType.E_TYPE_2).ToArray();

					if (Items.Length>0)
					{
						for(int Index=0;Index<Items.Length;Index++)
						{
							CUserItem2							Item=Items[Index];

							Console.WriteLine($"{(Index+1)}. ITEM 2 - ID [{Item.ID}] USER ID [{Item.UserID}] PARAMETER 1 [{Item.Parameter1}] PARAMETER 2 [{Item.Parameter2}] PARAMETER 3 [{Item.Parameter3}].");
						}
					}
					else
					{
						Console.WriteLine("NO ITEMS 2 FOUND.");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllItems3(string CommandID, object[] Parameters)
		{
			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					CUserItem3[]								Items=Container.GetItemLinqQueryable<CUserItem3>(true).Where(P => P.Type==EUserInfoType.E_TYPE_3).ToArray();

					if (Items.Length>0)
					{
						for(int Index=0;Index<Items.Length;Index++)
						{
							CUserItem3							Item=Items[Index];

							Console.WriteLine($"{(Index+1)}. ITEM 3 - ID [{Item.ID}] USER ID [{Item.UserID}] PARAMETER 1 [{Item.Parameter1}] PARAMETER 2 [{Item.Parameter2}] PARAMETER 3 [{Item.Parameter3}] PARAMETER 4 [{Item.Parameter4}].");
						}
					}
					else
					{
						Console.WriteLine("NO ITEMS 3 FOUND.");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetItem1(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem1>					ItemResponseRead=Container.ReadItemAsync<CUserItem1>(ID,PartitionKey).Result;
					CUserItem1									Item=ItemResponseRead.Resource;

					if (Item!=null)
					{
						Console.WriteLine($"ITEM 1 - ID [{Item.ID}] USER ID [{Item.UserID}] PARAMETER 1 [{Item.Parameter1}] PARAMETER 2 [{Item.Parameter2}].");
					}
					else
					{
						Console.WriteLine($"NO ITEM 1 FOUND.");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetItem2(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem2>					ItemResponseRead=Container.ReadItemAsync<CUserItem2>(ID,PartitionKey).Result;
					CUserItem2									Item=ItemResponseRead.Resource;

					if (Item!=null)
					{
						Console.WriteLine($"ITEM 2 - ID [{Item.ID}] USER ID [{Item.UserID}] PARAMETER 1 [{Item.Parameter1}] PARAMETER 2 [{Item.Parameter2}] PARAMETER 3 [{Item.Parameter3}].");
					}
					else
					{
						Console.WriteLine($"NO ITEM 2 FOUND.");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetItem3(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem3>					ItemResponseRead=Container.ReadItemAsync<CUserItem3>(ID,PartitionKey).Result;
					CUserItem3									Item=ItemResponseRead.Resource;

					if (Item!=null)
					{
						Console.WriteLine($"ITEM 3 - ID [{Item.ID}] USER ID [{Item.UserID}] PARAMETER 1 [{Item.Parameter1}] PARAMETER 2 [{Item.Parameter2}] PARAMETER 3 [{Item.Parameter3}] PARAMETER 4 [{Item.Parameter4}].");
					}
					else
					{
						Console.WriteLine($"NO ITEM 3 FOUND.");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertItem1(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);
			string												Parameter1=((string) Parameters[2]);
			string												Parameter2=((string) Parameters[3]);

			CUserItem1											Item=new CUserItem1(ID,UserID,Parameter1,Parameter2);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					ItemResponse<CUserItem1>					Response=Container.CreateItemAsync(Item).Result;

					Console.WriteLine($"INSERTING ITEM 1. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertItem2(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);
			string												Parameter1=((string) Parameters[2]);
			string												Parameter2=((string) Parameters[3]);
			string												Parameter3=((string) Parameters[4]);

			CUserItem2											Item=new CUserItem2(ID,UserID,Parameter1,Parameter2,Parameter3);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					ItemResponse<CUserItem2>					Response=Container.CreateItemAsync(Item).Result;

					Console.WriteLine($"INSERTING ITEM 2. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInsertItem3(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);
			string												Parameter1=((string) Parameters[2]);
			string												Parameter2=((string) Parameters[3]);
			string												Parameter3=((string) Parameters[4]);
			string												Parameter4=((string) Parameters[5]);

			CUserItem3											Item=new CUserItem3(ID,UserID,Parameter1,Parameter2,Parameter3,Parameter4);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					ItemResponse<CUserItem3>					Response=Container.CreateItemAsync(Item).Result;

					Console.WriteLine($"INSERTING ITEM 3. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateItem1(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);
			string												Parameter1=((string) Parameters[2]);
			string												Parameter2=((string) Parameters[3]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem2>					ItemResponseRead=Container.ReadItemAsync<CUserItem2>(ID,PartitionKey).Result;
					CUserItem2									Item=ItemResponseRead.Resource;

					Item.Parameter1=Parameter1;
					Item.Parameter2=Parameter2;

					ItemResponse<CUserItem2>					ItemResponseReplace=Container.ReplaceItemAsync<CUserItem2>(Item,ID).Result;

					Console.WriteLine($"UPDATING ITEM 1. RESPONSE CODE [{ItemResponseReplace.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateItem2(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);
			string												Parameter1=((string) Parameters[2]);
			string												Parameter2=((string) Parameters[3]);
			string												Parameter3=((string) Parameters[4]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem2>					ItemResponseRead=Container.ReadItemAsync<CUserItem2>(ID,PartitionKey).Result;
					CUserItem2									Item=ItemResponseRead.Resource;

					Item.Parameter1=Parameter1;
					Item.Parameter2=Parameter2;
					Item.Parameter3=Parameter3;

					ItemResponse<CUserItem2>					ItemResponseReplace=Container.ReplaceItemAsync<CUserItem2>(Item,ID).Result;

					Console.WriteLine($"UPDATING ITEM 2. RESPONSE CODE [{ItemResponseReplace.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUpdateItem3(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);
			string												Parameter1=((string) Parameters[2]);
			string												Parameter2=((string) Parameters[3]);
			string												Parameter3=((string) Parameters[4]);
			string												Parameter4=((string) Parameters[5]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				// !!!!! Pre vykonavanie NON-ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim ENTRA ID AUTHENTICATION.
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem3>					ItemResponseRead=Container.ReadItemAsync<CUserItem3>(ID,PartitionKey).Result;
					CUserItem3									Item=ItemResponseRead.Resource;

					Item.Parameter1=Parameter1;
					Item.Parameter2=Parameter2;
					Item.Parameter3=Parameter3;
					Item.Parameter4=Parameter4;

					ItemResponse<CUserItem3>					ItemResponseReplace=Container.ReplaceItemAsync<CUserItem3>(Item,ID).Result;

					Console.WriteLine($"UPDATING ITEM 3. RESPONSE CODE [{ItemResponseReplace.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteItem1(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem1>					ItemResponseDelete=Container.DeleteItemAsync<CUserItem1>(ID,PartitionKey).Result;

					Console.WriteLine($"DELETING ITEM 1. RESPONSE CODE [{ItemResponseDelete.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteItem2(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem2>					ItemResponseDelete=Container.DeleteItemAsync<CUserItem2>(ID,PartitionKey).Result;

					Console.WriteLine($"DELETING ITEM 2. RESPONSE CODE [{ItemResponseDelete.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteItem3(string CommandID, object[] Parameters)
		{
			string												ID=((string) Parameters[0]);
			string												UserID=((string) Parameters[1]);

			TokenCredential										Identity=CreateIdentity();

			try
			{
				using(CosmosClient Client=new CosmosClient(ENDPOINT_URL,Identity))
				{
					Database									Database=Client.GetDatabase(DATABASE_NAME);
					Container									Container=Database.GetContainer(CONTAINER_NAME);

					PartitionKey								PartitionKey=new PartitionKey(UserID);

					ItemResponse<CUserItem3>					ItemResponseDelete=Container.DeleteItemAsync<CUserItem3>(ID,PartitionKey).Result;

					Console.WriteLine($"DELETING ITEM 3. RESPONSE CODE [{ItemResponseDelete.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStartItemsChangeFeed(string CommandID, object[] Parameters)
		{
			if (MThread!=null)
			{
				Console.WriteLine("CHANGE FEED THREAD is already RUNNING.");
				return;
			}

			MManualResetEvent=new ManualResetEvent(false);

			MThread=new Thread(ChangeFeedThread);

			MThread.Start();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStopItemsChangeFeed(string CommandID, object[] Parameters)
		{
			if (MThread==null)
			{
				Console.WriteLine("CHANGE FEED THREAD is NOT RUNNING.");
				return;
			}

			MManualResetEvent.Set();

			MThread.Join();

			MThread=null;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","GET ALL ITEMS 1",new EMenuCommandParameterType[0],ExecuteCommandGetAllItems1));
			CommandsCollection.Add(new CMenuCommand("2","GET ALL ITEMS 2",new EMenuCommandParameterType[0],ExecuteCommandGetAllItems2));
			CommandsCollection.Add(new CMenuCommand("3","GET ALL ITEMS 3",new EMenuCommandParameterType[0],ExecuteCommandGetAllItems3));
			CommandsCollection.Add(new CMenuCommand("4","GET ITEM 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandGetItem1));
			CommandsCollection.Add(new CMenuCommand("5","GET ITEM 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandGetItem2));
			CommandsCollection.Add(new CMenuCommand("6","GET ITEM 3",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandGetItem3));
			CommandsCollection.Add(new CMenuCommand("7","INSERT ITEM 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInsertItem1));
			CommandsCollection.Add(new CMenuCommand("8","INSERT ITEM 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInsertItem2));
			CommandsCollection.Add(new CMenuCommand("9","INSERT ITEM 3",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInsertItem3));
			CommandsCollection.Add(new CMenuCommand("10","UPDATE ITEM 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUpdateItem1));
			CommandsCollection.Add(new CMenuCommand("11","UPDATE ITEM 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUpdateItem2));
			CommandsCollection.Add(new CMenuCommand("12","UPDATE ITEM 3",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUpdateItem3));
			CommandsCollection.Add(new CMenuCommand("13","DELETE ITEM 1",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandDeleteItem1));
			CommandsCollection.Add(new CMenuCommand("14","DELETE ITEM 2",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandDeleteItem2));
			CommandsCollection.Add(new CMenuCommand("15","DELETE ITEM 3",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandDeleteItem3));
			CommandsCollection.Add(new CMenuCommand("16","START ITEMS CHANGE FEED",new EMenuCommandParameterType[0],ExecuteCommandStartItemsChangeFeed));
			CommandsCollection.Add(new CMenuCommand("17","STOP ITEMS CHANGE FEED",new EMenuCommandParameterType[0],ExecuteCommandStopItemsChangeFeed));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------