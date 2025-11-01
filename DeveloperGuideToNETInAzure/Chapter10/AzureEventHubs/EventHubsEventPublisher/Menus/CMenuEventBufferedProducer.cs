using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Messaging.EventHubs;
using Azure.Messaging.EventHubs.Producer;
using Constants.Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventPublisher
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuEventBufferedProducer : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private EventHubBufferedProducerClient					MClient;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuEventBufferedProducer()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void CloseProducer()
		{
			if (MClient==null)
			{
				return;
			}

			try
			{
				//MClient.SendEventBatchSucceededAsync-=MClientSendEventBatchSucceededAsync;
				//MClient.SendEventBatchFailedAsync-=MClientSendEventBatchFailedAsync;

				MClient.CloseAsync().Wait();

				Console.WriteLine("EVENT PRODUCER STOPPED.");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}

			MClient=null;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private Task MClientSendEventBatchSucceededAsync(SendEventBatchSucceededEventArgs Args)
		{
			string												PartitionID=Args.PartitionId;
			
			Console.WriteLine($"EVENT BATCH SENT DETECTED. PARTITION ID [{PartitionID}].");

			Task												Result=Task.CompletedTask;

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task MClientSendEventBatchFailedAsync(SendEventBatchFailedEventArgs Args)
		{
			string												PartitionID=Args.PartitionId;
			Exception											Exception=Args.Exception;
			
			string												ExceptionMessage=Exception?.Message ?? "";

			if ((Exception is EventHubsException)==true)
			{
				EventHubsException								TypedException=(EventHubsException) Exception;

				string											EventHubName=TypedException.EventHubName ?? "";
				string											FailureReason=TypedException.Reason.ToString() ?? "";

				Console.WriteLine($"ERROR DETECTED. PARTITION ID [{PartitionID}] EXCEPTION [{ExceptionMessage}] EVENT HUB NAME [{EventHubName}] REASON [{FailureReason}].");
			}
			else
			{
				Console.WriteLine($"ERROR DETECTED. PARTITION ID [{PartitionID}] EXCEPTION [{ExceptionMessage}].");
			}
			
			Task												Result=Task.CompletedTask;

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStartClient(string CommandID, object[] Parameters)
		{
			if (MClient!=null)
			{
				Console.WriteLine("EVENT PRODUCER is ALREADY CREATED.");
				return;
			}

			try
			{
				MClient=new EventHubBufferedProducerClient(CConstants.EVENT_HUBS_CONNECTION_STRING,CConstants.EVENT_HUB_NAME);

				MClient.SendEventBatchSucceededAsync+=MClientSendEventBatchSucceededAsync;
				MClient.SendEventBatchFailedAsync+=MClientSendEventBatchFailedAsync;

				Console.WriteLine("EVENT PRODUCER STARTED.");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				CloseProducer();
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStopClient(string CommandID, object[] Parameters)
		{
			if (MClient==null)
			{
				Console.WriteLine("EVENT PRODUCER doesn't EXIST.");
				return;
			}

			CloseProducer();

			Console.WriteLine("EVENT PRODUCER STOPPED.");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandAddEventToBuffer(string CommandID, object[] Parameters)
		{
			if (MClient==null)
			{
				Console.WriteLine("EVENT PRODUCER doesn't EXIST.");
				return;
			}

			string												Message=((string) Parameters[0]);

			try
			{
				EventData										EventData=new EventData(Message);

				int												NumberOfEvenetsInBuffer=MClient.EnqueueEventAsync(EventData).Result;

				Console.WriteLine($"EVENT WRITTEN to BUFFER ! EVENT BUFFER SIZE [{NumberOfEvenetsInBuffer}].");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandAddEventsToBuffer(string CommandID, object[] Parameters)
		{
			if (MClient==null)
			{
				Console.WriteLine("EVENT PRODUCER doesn't EXIST.");
				return;
			}

			int													NumberOfMessages=((int) Parameters[0]);
			string												Message=((string) Parameters[1]);

			try
			{
				EventData[]										EventDataArray=new EventData[NumberOfMessages];

				for(int Index=0;Index<NumberOfMessages;Index++)
				{
					string										MessageContent=$"MESSAGE [{Message}] ID [{(Index+1)}].";

					EventDataArray[Index]=new EventData(MessageContent);
				}

				int												NumberOfEvenetsInBuffer=MClient.EnqueueEventsAsync(EventDataArray).Result;

				Console.WriteLine($"EVENTS WRITTEN to BUFFER ! EVENT BUFFER SIZE [{NumberOfEvenetsInBuffer}].");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
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

			CommandsCollection.Add(new CMenuCommand("1","START PRODUCER",new EMenuCommandParameterType[0],ExecuteCommandStartClient));
			CommandsCollection.Add(new CMenuCommand("2","STOP PRODUCER",new EMenuCommandParameterType[0],ExecuteCommandStopClient));
			CommandsCollection.Add(new CMenuCommand("3","ADD EVENT to BUFFER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandAddEventToBuffer));
			CommandsCollection.Add(new CMenuCommand("4","ADD EVENTS to BUFFER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandAddEventsToBuffer));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------