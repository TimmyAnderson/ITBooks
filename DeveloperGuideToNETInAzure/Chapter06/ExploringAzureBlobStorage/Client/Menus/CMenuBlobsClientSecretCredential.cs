using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Azure;
using Azure.Core;
using Azure.Identity;
using Azure.Storage;
using Azure.Storage.Blobs;
using Azure.Storage.Blobs.Models;
using Azure.Storage.Sas;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuBlobsClientSecretCredential : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private static readonly string							STORAGE_ACCOUNT_NAME="mystorageta";
		// !!!!! TENANT ID, CLIENT ID a CLIENT SECRET vracia COMMAND [az ad app credential reset].
		// !!!!! SERVICE PRINCIPAL asociovany so CLIENT ID a CLIENT SECRET MUSI mat priradeny BLOB ROLE. To sa robi pomocou COMMAND [az role assignment create --assignee "221500d1-c96a-428e-a0dc-059c5484d23b" --scope "/subscriptions/b5f70a84-6ba2-4485-84cd-ac0883d618c5/resourceGroups/Chapter06/providers/Microsoft.Storage/storageAccounts/mystorageta" --role "Storage Blob Data Contributor"].
		private static readonly string							TENANT_ID="fb51fbc4-63c4-41a5-8b6a-6f6e1434b7dd";
		private static readonly string							CLIENT_ID="221500d1-c96a-428e-a0dc-059c5484d23b";
		private static readonly string							CLIENT_SECRET="lHf8Q~VJVdss.EV40e3aKXPmabAvNeOd5911Qcny";
		private static readonly Uri								BLOB_CONNECTION_STRING=new Uri($"https://{STORAGE_ACCOUNT_NAME}.blob.core.windows.net");
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuBlobsClientSecretCredential()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private BlobServiceClient CreateBlobServiceClient()
		{
			ClientSecretCredential								Credential=new ClientSecretCredential(TENANT_ID,CLIENT_ID,CLIENT_SECRET);
			BlobServiceClient									ServiceClient=new BlobServiceClient(BLOB_CONNECTION_STRING,Credential);

			return(ServiceClient);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandPrintAllContainersAndBlobs(string CommandID, object[] Parameters)
		{
			try
			{
				BlobServiceClient								ServiceClient=CreateBlobServiceClient();
				Pageable<BlobContainerItem>						Containers=ServiceClient.GetBlobContainers();

				foreach(BlobContainerItem Container in Containers)
				{
					Console.WriteLine($"CONTAINER [{Container.Name}].");

					BlobContainerClient							ContainerClient=ServiceClient.GetBlobContainerClient(Container.Name);
					Pageable<BlobItem>							Blobs=ContainerClient.GetBlobs();

					foreach(BlobItem Blob in Blobs)
					{
						Console.WriteLine($"\tBLOB [{Blob.Name}].");

						BlobClient								BlobClient=ContainerClient.GetBlobClient(Blob.Name);
						Response<BlobProperties>				ResponseBlobProperties=BlobClient.GetProperties();
						BlobProperties							BlobProperties=ResponseBlobProperties.Value;

						Console.WriteLine($"\t\tACCESS TIER [{BlobProperties.AccessTier}].");
						Console.WriteLine($"\t\tBLOB TYPE [{BlobProperties.BlobType}].");
						Console.WriteLine($"\t\tCONTENT LENGTH [{BlobProperties.ContentLength}].");
						Console.WriteLine($"\t\tCONTENT TYPE [{BlobProperties.ContentType}].");
						Console.WriteLine($"\t\tCREATED ON [{BlobProperties.CreatedOn}].");
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandCreateContainer(string CommandID, object[] Parameters)
		{
			string												ContainerName=((string) Parameters[0]);

			try
			{
				BlobServiceClient								ServiceClient=CreateBlobServiceClient();

				ServiceClient.CreateBlobContainer(ContainerName);

				Console.WriteLine($"CONTAINER [{ContainerName}] was CREATED.");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteContainer(string CommandID, object[] Parameters)
		{
			string												ContainerName=((string) Parameters[0]);

			try
			{
				BlobServiceClient								ServiceClient=CreateBlobServiceClient();

				ServiceClient.DeleteBlobContainer(ContainerName);

				Console.WriteLine($"CONTAINER [{ContainerName}] was DELETED.");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandUploadBlob(string CommandID, object[] Parameters)
		{
			string												ContainerName=((string) Parameters[0]);
			string												BlobName=((string) Parameters[1]);
			string												BlobFileName=((string) Parameters[2]);
			
			string												FilePath=$"Files\\{BlobFileName}";
			byte[]												FileContent=File.ReadAllBytes(FilePath);

			try
			{
				BlobServiceClient								ServiceClient=CreateBlobServiceClient();

				BlobContainerClient								ContainerClient=ServiceClient.GetBlobContainerClient(ContainerName);

				BinaryData										BinaryData=new BinaryData(FileContent);
				
				ContainerClient.UploadBlob(BlobName,BinaryData);

				Console.WriteLine($"BLOB [{BlobName}] was UPLOADED to CONTAINER [{ContainerName}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDownloadBlob(string CommandID, object[] Parameters)
		{
			string												ContainerName=((string) Parameters[0]);
			string												BlobName=((string) Parameters[1]);

			try
			{
				BlobServiceClient								ServiceClient=CreateBlobServiceClient();

				BlobContainerClient								ContainerClient=ServiceClient.GetBlobContainerClient(ContainerName);

				BlobClient										BlobClient=ContainerClient.GetBlobClient(BlobName);
				Response<BlobDownloadResult>					ResponseBlobDownloadResult=BlobClient.DownloadContent();
				BlobDownloadResult								BlobDownloadResult=ResponseBlobDownloadResult.Value;

				BinaryData										BlobContent=BlobDownloadResult.Content;

				Console.WriteLine($"BLOB [{BlobName}] was DOWNLOADED from CONTAINER [{ContainerName}]. CONTENT [{BlobContent}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDeleteBlob(string CommandID, object[] Parameters)
		{
			string												ContainerName=((string) Parameters[0]);
			string												BlobName=((string) Parameters[1]);

			try
			{
				BlobServiceClient								ServiceClient=CreateBlobServiceClient();

				BlobContainerClient								ContainerClient=ServiceClient.GetBlobContainerClient(ContainerName);

				ContainerClient.DeleteBlob(BlobName);

				Console.WriteLine($"BLOB [{BlobName}] was DELETED from CONTAINER [{ContainerName}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","PRINT ALL CONTAINERS AND BLOBS",new EMenuCommandParameterType[0],ExecuteCommandPrintAllContainersAndBlobs));
			CommandsCollection.Add(new CMenuCommand("2","CREATE CONTAINER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandCreateContainer));
			CommandsCollection.Add(new CMenuCommand("3","DELETE CONTAINER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandDeleteContainer));
			CommandsCollection.Add(new CMenuCommand("4","UPLOAD BLOB",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandUploadBlob));
			CommandsCollection.Add(new CMenuCommand("5","DOWNLOAD BLOB",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandDownloadBlob));
			CommandsCollection.Add(new CMenuCommand("6","DELETE BLOB",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandDeleteBlob));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------