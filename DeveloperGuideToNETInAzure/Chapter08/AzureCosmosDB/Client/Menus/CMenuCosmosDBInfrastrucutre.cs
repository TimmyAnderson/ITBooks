using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Azure.Cosmos;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuCosmosDBInfrastrucutre : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! CONNECTION STRING sa da ziskat pomocou COMMAND [az cosmosdb keys list]. Prikladom je COMMAND [az cosmosdb keys list --name mycosmosaccountta --resource-group Chapter08 --type connection-strings].
		private const string									CONNECTION_STRING="AccountEndpoint=https://mycosmosaccountta.documents.azure.com:443/;AccountKey=gp2H3aqeM8EBxwXWJek7CspKKpIUDjddXHzhfuGbfztNy4VntGzsjIJ5nc2Jcq6TK58o6Tfs1cAVACDbQ8qjVw==;";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuCosmosDBInfrastrucutre()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCreateDatabase(string CommandID, object[] Parameters)
		{
			string												DatabaseName=((string) Parameters[0]);

			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					DatabaseResponse							Response=Client.CreateDatabaseAsync(DatabaseName).Result;

					Console.WriteLine($"DATABASE [{DatabaseName}] was CREATED. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteDatabase(string CommandID, object[] Parameters)
		{
			string												DatabaseName=((string) Parameters[0]);

			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					Database									Database=Client.GetDatabase(DatabaseName);
					DatabaseResponse							Response=Database.DeleteAsync().Result;

					Console.WriteLine($"DATABASE [{DatabaseName}] was DELETED. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllDatabases(string CommandID, object[] Parameters)
		{
			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					FeedIterator<DatabaseProperties>			DatabaseIterator=Client.GetDatabaseQueryIterator<DatabaseProperties>();

					while(DatabaseIterator.HasMoreResults==true)
					{
						FeedResponse<DatabaseProperties>		Databases=DatabaseIterator.ReadNextAsync().Result;

						int										Index=0;
					
						foreach(DatabaseProperties Database in Databases)
						{
							Console.WriteLine($"[{++Index}]. DATABASE [{Database.Id}].");
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
		private void ExecuteCommandCreateContainer(string CommandID, object[] Parameters)
		{
			string												DatabaseName=((string) Parameters[0]);
			string												ContainerName=((string) Parameters[1]);
			string												PartitionKeyPath=((string) Parameters[2]);

			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					Database									Database=Client.GetDatabase(DatabaseName);

					ContainerResponse							Response=Database.CreateContainerAsync(ContainerName,PartitionKeyPath).Result;

					Console.WriteLine($"CONTAINER [{ContainerName}] was CREATED. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteContainer(string CommandID, object[] Parameters)
		{
			string												DatabaseName=((string) Parameters[0]);
			string												ContainerName=((string) Parameters[1]);

			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					Database									Database=Client.GetDatabase(DatabaseName);
					Container									Container=Database.GetContainer(ContainerName);

					ContainerResponse							Response=Container.DeleteContainerAsync().Result;

					Console.WriteLine($"CONTAINER [{ContainerName}] was DELETED. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetAllContainers(string CommandID, object[] Parameters)
		{
			string												DatabaseName=((string) Parameters[0]);

			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					Database									Database=Client.GetDatabase(DatabaseName);
					FeedIterator<ContainerProperties>			ContainerIterator=Database.GetContainerQueryIterator<ContainerProperties>();

					while(ContainerIterator.HasMoreResults==true)
					{
						FeedResponse<ContainerProperties>		Containers=ContainerIterator.ReadNextAsync().Result;

						int										Index=0;
					
						foreach(ContainerProperties Container in Containers)
						{
							Console.WriteLine($"[{++Index}]. CONTAINER [{Container.Id}].");
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
		private void ExecuteCommandGetContainerTimeToLive(string CommandID, object[] Parameters)
		{
			string												DatabaseName=((string) Parameters[0]);
			string												ContainerName=((string) Parameters[1]);

			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					Database									Database=Client.GetDatabase(DatabaseName);
					Container									Container=Database.GetContainer(ContainerName);

					ContainerResponse							Response=Container.ReadContainerAsync().Result;
					ContainerProperties							ContainerProperties=Response.Resource;

					Console.WriteLine($"CONTAINER [{ContainerName}] DEFAULT TIME TO LIVE [{ContainerProperties.DefaultTimeToLive}]. RESPONSE CODE [{Response.StatusCode}].");
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSetContainerTimeToLive(string CommandID, object[] Parameters)
		{
			string												DatabaseName=((string) Parameters[0]);
			string												ContainerName=((string) Parameters[1]);
			int													TimeToLive=((int) Parameters[2]);

			try
			{
				// !!!!! Pre vykonavanie ADMIN OPERATIONS je NUTNE vytvorit instanciu CLASS [CosmosClient] s pouzitim CONNECTION STRING. AUTHENTICATION cez ENTRA ID TOKEN NEFUNGUJE, pretoze AZURE ho ODMIETNE.
				using(CosmosClient Client=new CosmosClient(CONNECTION_STRING))
				{
					Database									Database=Client.GetDatabase(DatabaseName);
					Container									Container=Database.GetContainer(ContainerName);

					ContainerResponse							ResponseGet=Container.ReadContainerAsync().Result;
					ContainerProperties							ContainerProperties=ResponseGet.Resource;

					ContainerProperties.DefaultTimeToLive=TimeToLive;

					ContainerResponse							ResponseSet=Container.ReplaceContainerAsync(ContainerProperties).Result;

					Console.WriteLine($"CONTAINER [{ContainerName}] set DEFAULT TIME TO LIVE [{ContainerProperties.DefaultTimeToLive}]. RESPONSE CODE [{ResponseSet.StatusCode}].");
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

			CommandsCollection.Add(new CMenuCommand("1","CREATE DATABASE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandCreateDatabase));
			CommandsCollection.Add(new CMenuCommand("2","DELETE DATABASE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandDeleteDatabase));
			CommandsCollection.Add(new CMenuCommand("3","GET ALL DATABASES",new EMenuCommandParameterType[0],ExecuteCommandGetAllDatabases));
			CommandsCollection.Add(new CMenuCommand("4","CREATE CONTAINER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandCreateContainer));
			CommandsCollection.Add(new CMenuCommand("5","DELETE CONTAINER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandDeleteContainer));
			CommandsCollection.Add(new CMenuCommand("6","GET ALL CONTAINERS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandGetAllContainers));
			CommandsCollection.Add(new CMenuCommand("7","GET CONTAINER TIME TO LIVE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandGetContainerTimeToLive));
			CommandsCollection.Add(new CMenuCommand("8","SET CONTAINER TIME TO LIVE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT},ExecuteCommandSetContainerTimeToLive));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------