using System;
using Azure;
using Azure.Core;
using Azure.Identity;
using Azure.Storage.Blobs;
using Azure.Storage.Blobs.Models;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuBlobsDefaultAzureCredential					Menu=new CMenuBlobsDefaultAzureCredential();
			//CMenuBlobsStorageSharedKeyCredential				Menu=new CMenuBlobsStorageSharedKeyCredential();
			CMenuBlobsAzureSasCredential						Menu=new CMenuBlobsAzureSasCredential();
			//CMenuBlobsClientSecretCredential					Menu=new CMenuBlobsClientSecretCredential();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------