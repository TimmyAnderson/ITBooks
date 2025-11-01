using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using Azure;
using Azure.Messaging.EventHubs;
using Azure.Messaging.EventHubs.Producer;
using Constants.Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventPublisher
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuEventProducerSasCredentialEventHubsNamespace : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuEventProducerSasCredentialEventHubsNamespace()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static string CreateSaSToken(string ResourceUri, string KeyName, string Key)
		{
			TimeSpan											SinceEpoch=(DateTime.UtcNow-new DateTime(1970,1,1));
			int													Week=(60*60*24*7);
			string												Expiry=Convert.ToString((int)SinceEpoch.TotalSeconds+Week);

			string												StringToSign=$"{HttpUtility.UrlEncode(ResourceUri)}\n{Expiry}";
			byte[]												BytesToSign=Encoding.UTF8.GetBytes(StringToSign);
			byte[]												BytesKey=Encoding.UTF8.GetBytes(Key);
				
			using(HMACSHA256 HMAC=new HMACSHA256(BytesKey))
			{
				byte[]											Hash=HMAC.ComputeHash(BytesToSign);
				string											Signature=Convert.ToBase64String(Hash);

				string											SaSToken=string.Format(CultureInfo.InvariantCulture,"SharedAccessSignature sr={0}&sig={1}&se={2}&skn={3}",HttpUtility.UrlEncode(ResourceUri),HttpUtility.UrlEncode(Signature),Expiry,KeyName);

				return(SaSToken);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static EventHubProducerClient CreateClient()
		{
			string												SaSToken=CreateSaSToken(CConstants.EVENT_HUB_FULLY_QUALIFIED_NAMESPACE_URL,CConstants.SAS_AUTHORIZATION_RULE_EVENT_HUBS_NAMESPACE_NAME_PRODUCER,CConstants.SAS_AUTHORIZATION_RULE_EVENT_HUBS_NAMESPACE_KEY_PRODUCER);
			AzureSasCredential									SasCredential=new AzureSasCredential(SaSToken);
			EventHubProducerClient								Client=new EventHubProducerClient(CConstants.EVENT_HUB_FULLY_QUALIFIED_NAMESPACE,CConstants.EVENT_HUB_NAME,SasCredential);

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