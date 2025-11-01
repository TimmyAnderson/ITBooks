using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using Azure;
using Azure.Identity;
using Azure.Messaging.EventHubs;
using Azure.Messaging.EventHubs.Consumer;
using Azure.Messaging.EventHubs.Processor;
using Azure.Storage.Blobs;
using Constants.Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventConsumer1
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuEventConsumerClientSecretCredential : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private EventProcessorClient							MEventProcessorClient;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuEventConsumerClientSecretCredential()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static EventProcessorClient CreateClient(BlobContainerClient BlobContainerClient)
		{
			ClientSecretCredential								Credential=new ClientSecretCredential(CConstants.TENANT_ID,CConstants.CLIENT_CREDENTIALS_CLIENT_ID_CONSUMER,CConstants.CLIENT_CREDENTIALS_CLIENT_SECRET_CONSUMER);
			EventProcessorClient								Client=new EventProcessorClient(BlobContainerClient,EventHubConsumerClient.DefaultConsumerGroupName,CConstants.EVENT_HUB_FULLY_QUALIFIED_NAMESPACE,CConstants.EVENT_HUB_NAME,Credential);

			return(Client);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void CloseProcessor()
		{
			if (MEventProcessorClient==null)
			{
				return;
			}

			try
			{
				MEventProcessorClient.StopProcessingAsync().Wait();

				Console.WriteLine("EVENT PROCESSING STOPPED.");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}

			MEventProcessorClient.ProcessEventAsync-=MEventProcessorClientProcessEventAsync;
			MEventProcessorClient.ProcessErrorAsync-=MEventProcessorClientProcessErrorAsync;

			MEventProcessorClient=null;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private Task MEventProcessorClientProcessEventAsync(ProcessEventArgs Args)
		{
			PartitionContext									PartitionContext=Args.Partition;
			EventData											EventData=Args.Data;

			string												PartitionID=PartitionContext?.PartitionId ?? "";
			string												FullyQualifiedNamespace=PartitionContext?.FullyQualifiedNamespace ?? "";
			string												EventHubName=PartitionContext?.EventHubName ?? "";
			string												ConsumerGroup=PartitionContext?.ConsumerGroup ?? "";

			string												MessageID=EventData?.MessageId ?? "";
			string												ContentType=EventData?.ContentType ?? "";
			
			byte[]												BodyRaw=EventData?.EventBody?.ToArray();
			string												BodyString=(BodyRaw!=null) ? Encoding.UTF8.GetString(BodyRaw) : "";

			Console.WriteLine($"EVENT DETECTED. PARTITION ID [{PartitionID}] NAMESPACE [{FullyQualifiedNamespace}] HUB NAME [{EventHubName}] CONSUMER GROUP [{ConsumerGroup}] MESSAGE ID [{MessageID}] CONTENT TYPE [{ContentType}] BODY [{BodyString}].");

			// !!!!! Vykona sa UPDATE CHECKPOINT, aby EVENT bol oznaceny ako spracovany a nebol opatovne vyberany z EVENT HUBS PARTITION.
			Args.UpdateCheckpointAsync().Wait();

			Task												Result=Task.CompletedTask;

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task MEventProcessorClientProcessErrorAsync(ProcessErrorEventArgs Args)
		{
			string												PartitionID=Args.PartitionId;
			string												Operation=Args.Operation;
			Exception											Exception=Args.Exception;
			
			string												ExceptionMessage=Exception?.Message ?? "";

			if ((Exception is EventHubsException)==true)
			{
				EventHubsException								TypedException=(EventHubsException) Exception;

				string											EventHubName=TypedException.EventHubName ?? "";
				string											FailureReason=TypedException.Reason.ToString() ?? "";

				Console.WriteLine($"ERROR DETECTED. PARTITION ID [{PartitionID}] OPERATION [{Operation}] EXCEPTION [{ExceptionMessage}] EVENT HUB NAME [{EventHubName}] REASON [{FailureReason}].");
			}
			else
			{
				Console.WriteLine($"ERROR DETECTED. PARTITION ID [{PartitionID}] OPERATION [{Operation}] EXCEPTION [{ExceptionMessage}].");
			}

			Task												Result=Task.CompletedTask;

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStartReceivingMessages(string CommandID, object[] Parameters)
		{
			if (MEventProcessorClient!=null)
			{
				Console.WriteLine("EVENT PROCESSOR CLIENT is ALREADY CREATED.");
				return;
			}

			try
			{
				BlobContainerClient								BlobContainerClient=new BlobContainerClient(CConstants.BLOB_STORAGE_CONNECTION_STRING,CConstants.BLOB_CONTAINER_NAME);

				MEventProcessorClient=CreateClient(BlobContainerClient);

				MEventProcessorClient.ProcessEventAsync+=MEventProcessorClientProcessEventAsync;
				MEventProcessorClient.ProcessErrorAsync+=MEventProcessorClientProcessErrorAsync;

				MEventProcessorClient.StartProcessingAsync().Wait();

				Console.WriteLine("EVENT PROCESSING STARTED.");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				CloseProcessor();
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStopReceivingMessages(string CommandID, object[] Parameters)
		{
			if (MEventProcessorClient==null)
			{
				Console.WriteLine("EVENT PROCESSOR CLIENT doesn't EXIST.");
				return;
			}

			CloseProcessor();
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","START RECEIVING MESSAGES",new EMenuCommandParameterType[0],ExecuteCommandStartReceivingMessages));
			CommandsCollection.Add(new CMenuCommand("2","STOP RECEIVING MESSAGES",new EMenuCommandParameterType[0],ExecuteCommandStopReceivingMessages));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------