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
	public sealed class CMenuEventProducer : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuEventProducer()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessage(string CommandID, object[] Parameters)
		{
			string												Message=((string) Parameters[0]);

			EventHubProducerClient								Client=null;

			try
			{
				Client=new EventHubProducerClient(CConstants.EVENT_HUBS_CONNECTION_STRING,CConstants.EVENT_HUB_NAME);

				EventData										EventData=new EventData(Message);
				EventData[]										EventDataArray=new EventData[]{EventData};

				Client.SendAsync(EventDataArray).Wait();

				Console.WriteLine("EVENT SENT !");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
			finally
			{
				if (Client!=null)
				{
					Client.DisposeAsync().AsTask().Wait();
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessages(string CommandID, object[] Parameters)
		{
			int													NumberOfMessages=((int) Parameters[0]);
			string												Message=((string) Parameters[1]);

			EventHubProducerClient								Client=null;

			try
			{
				Client=new EventHubProducerClient(CConstants.EVENT_HUBS_CONNECTION_STRING,CConstants.EVENT_HUB_NAME);

				EventData[]										EventDataArray=new EventData[NumberOfMessages];

				for(int Index=0;Index<NumberOfMessages;Index++)
				{
					string										MessageContent=$"MESSAGE [{Message}] ID [{(Index+1)}].";

					EventDataArray[Index]=new EventData(MessageContent);
				}

				Client.SendAsync(EventDataArray).Wait();

				Console.WriteLine("EVENTS SENT !");
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
			finally
			{
				if (Client!=null)
				{
					Client.DisposeAsync().AsTask().Wait();
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessagesAsBatch(string CommandID, object[] Parameters)
		{
			int													NumberOfMessages=((int) Parameters[0]);
			string												Message=((string) Parameters[1]);

			EventHubProducerClient								Client=null;

			try
			{
				Client=new EventHubProducerClient(CConstants.EVENT_HUBS_CONNECTION_STRING,CConstants.EVENT_HUB_NAME);

				using(EventDataBatch Batch=Client.CreateBatchAsync().Result)
				{
					for(int Index=0;Index<NumberOfMessages;Index++)
					{
						string									MessageContent=$"MESSAGE [{Message}] ID [{(Index+1)}].";
						EventData								EventData=new EventData(MessageContent);

						bool									EventAdded=Batch.TryAdd(EventData);

						if (EventAdded==true)
						{
							Console.WriteLine("EVENT ADDED to BATCH !");
						}
						else
						{
							Console.WriteLine("EVENT NOT ADDED to BATCH !");
						}
					}

					Client.SendAsync(Batch).Wait();

					Console.WriteLine("EVENTS SENT !");
				}
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
			finally
			{
				if (Client!=null)
				{
					Client.DisposeAsync().AsTask().Wait();
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessagesAsBatchPartitionID(string CommandID, object[] Parameters)
		{
			string												ParitionID=((string) Parameters[0]);
			int													NumberOfMessages=((int) Parameters[1]);
			string												Message=((string) Parameters[2]);

			EventHubProducerClient								Client=null;

			try
			{
				Client=new EventHubProducerClient(CConstants.EVENT_HUBS_CONNECTION_STRING,CConstants.EVENT_HUB_NAME);

				CreateBatchOptions								Options=new CreateBatchOptions();

				Options.PartitionId=ParitionID;

				using(EventDataBatch Batch=Client.CreateBatchAsync(Options).Result)
				{
					for(int Index=0;Index<NumberOfMessages;Index++)
					{
						string									MessageContent=$"MESSAGE [{Message}] ID [{(Index+1)}].";
						EventData								EventData=new EventData(MessageContent);

						bool									EventAdded=Batch.TryAdd(EventData);

						if (EventAdded==true)
						{
							Console.WriteLine("EVENT ADDED to BATCH !");
						}
						else
						{
							Console.WriteLine("EVENT NOT ADDED to BATCH !");
						}
					}

					Client.SendAsync(Batch).Wait();

					Console.WriteLine("EVENTS SENT !");
				}
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
			finally
			{
				if (Client!=null)
				{
					Client.DisposeAsync().AsTask().Wait();
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessagesAsBatchPartitionKey(string CommandID, object[] Parameters)
		{
			string												ParitionKey=((string) Parameters[0]);
			int													NumberOfMessages=((int) Parameters[1]);
			string												Message=((string) Parameters[2]);

			EventHubProducerClient								Client=null;

			try
			{
				Client=new EventHubProducerClient(CConstants.EVENT_HUBS_CONNECTION_STRING,CConstants.EVENT_HUB_NAME);

				CreateBatchOptions								Options=new CreateBatchOptions();

				Options.PartitionKey=ParitionKey;

				using(EventDataBatch Batch=Client.CreateBatchAsync(Options).Result)
				{
					for(int Index=0;Index<NumberOfMessages;Index++)
					{
						string									MessageContent=$"MESSAGE [{Message}] ID [{(Index+1)}].";
						EventData								EventData=new EventData(MessageContent);

						bool									EventAdded=Batch.TryAdd(EventData);

						if (EventAdded==true)
						{
							Console.WriteLine("EVENT ADDED to BATCH !");
						}
						else
						{
							Console.WriteLine("EVENT NOT ADDED to BATCH !");
						}
					}

					Client.SendAsync(Batch).Wait();

					Console.WriteLine("EVENTS SENT !");
				}
			}
			catch(EventHubsException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. EVENT HUB NAME [{E.EventHubName}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
			finally
			{
				if (Client!=null)
				{
					Client.DisposeAsync().AsTask().Wait();
				}
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","SEND MESSAGE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessage));
			CommandsCollection.Add(new CMenuCommand("2","SEND MESSAGES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessages));
			CommandsCollection.Add(new CMenuCommand("3","SEND MESSAGES AS BATCH",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessagesAsBatch));
			CommandsCollection.Add(new CMenuCommand("4","SEND MESSAGES AS BATCH USING PARTITION ID",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessagesAsBatchPartitionID));
			CommandsCollection.Add(new CMenuCommand("5","SEND MESSAGES AS BATCH USING PARTITION KEY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessagesAsBatchPartitionKey));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------