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
using Azure.Messaging.EventHubs.Producer;
using Constants.Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventPublisher
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuEventProducerClientSecretCredential : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuEventProducerClientSecretCredential()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static EventHubProducerClient CreateClient()
		{
			ClientSecretCredential								Credential=new ClientSecretCredential(CConstants.TENANT_ID,CConstants.CLIENT_CREDENTIALS_CLIENT_ID_PRODUCER,CConstants.CLIENT_CREDENTIALS_CLIENT_SECRET_PRODUCER);
			EventHubProducerClient								Client=new EventHubProducerClient(CConstants.EVENT_HUB_FULLY_QUALIFIED_NAMESPACE,CConstants.EVENT_HUB_NAME,Credential);

			return(Client);
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
				Client=CreateClient();

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
				Client=CreateClient();

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
				Client=CreateClient();

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
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","SEND MESSAGE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessage));
			CommandsCollection.Add(new CMenuCommand("2","SEND MESSAGES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessages));
			CommandsCollection.Add(new CMenuCommand("3","SEND MESSAGES AS BATCH",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessagesAsBatch));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------