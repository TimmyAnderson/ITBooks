using System;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Azure.Cosmos;
//----------------------------------------------------------------------------------------------------------------------
namespace AzureCosmosDB
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CCosmosDBService : IDisposable
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! CLASS [CosmosClient] je THREAD SAFE.
		private readonly CosmosClient							MCosmosClient;
		private readonly Database								MDatabase;
		private readonly Container								MContainer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CCosmosDBService(string ConnectionString, string DatabaseName, string ContainerName)
		{
			MCosmosClient=new CosmosClient(ConnectionString);
			MDatabase=MCosmosClient.GetDatabase(DatabaseName);
			MContainer=MDatabase.GetContainer(ContainerName);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CItemName[] GetNames()
		{
			try
			{
				CItemName[]										Items=MContainer.GetItemLinqQueryable<CItemName>(true).ToArray();
				
				return(Items);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
				throw;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CItemName> GetName(string ID, string Sex)
		{
			PartitionKey										PartitionKey=new PartitionKey(Sex);

			ItemResponse<CItemName>								ItemResponseRead=await MContainer.ReadItemAsync<CItemName>(ID,PartitionKey);
			CItemName											Item=ItemResponseRead.Resource;

			return(Item);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CItemName> InsertName(CItemName Name)
		{
			ItemResponse<CItemName>								Response=await MContainer.CreateItemAsync(Name);
			CItemName											ResponseItem=Response.Resource;

			Console.WriteLine($"INSERTING NEW ITEM. RESPONSE CODE [{Response.StatusCode}].");

			return(ResponseItem);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task<CItemName> UpdateName(CItemName Name)
		{
			PartitionKey										PartitionKey=new PartitionKey(Name.Sex);

			ItemResponse<CItemName>								ItemResponseRead=await MContainer.ReadItemAsync<CItemName>(Name.ID,PartitionKey);
			CItemName											Item=ItemResponseRead.Resource;

			Item.FirstName=Name.FirstName;
			Item.LastName=Name.LastName;
			Item.Age=Name.Age;

			ItemResponse<CItemName>								ItemResponseReplace=await MContainer.ReplaceItemAsync<CItemName>(Item,Name.ID);
			CItemName											ResponseItem=ItemResponseReplace.Resource;

			Console.WriteLine($"UPDATING ITEM. RESPONSE CODE [{ItemResponseReplace.StatusCode}].");

			return(ResponseItem);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task DeleteName(string ID, string Sex)
		{
			PartitionKey										PartitionKey=new PartitionKey(Sex);

			ItemResponse<CItemName>								ItemResponseDelete=await MContainer.DeleteItemAsync<CItemName>(ID,PartitionKey);

			Console.WriteLine($"DELETING ITEM. RESPONSE CODE [{ItemResponseDelete.StatusCode}].");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			MCosmosClient.Dispose();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------