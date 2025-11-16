using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using Azure;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusPublisher
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessagePublisherTopicSaSCredentialsTopic : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessagePublisherTopicSaSCredentialsTopic()
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
		private static ServiceBusClient CreateClient()
		{
			string												SaSToken=CreateSaSToken(CConstants.SERVICE_BUS_FULLY_QUALIFIED_TOPIC_URL,CConstants.SAS_AUTHORIZATION_RULE_SERVICE_BUS_TOPIC_NAME_PUBLISHER,CConstants.SAS_AUTHORIZATION_RULE_SERVICE_BUS_TOPIC_KEY_PUBLISHER);
			AzureSasCredential									Credential=new AzureSasCredential(SaSToken);
			ServiceBusClient									Client=new ServiceBusClient(CConstants.SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE,Credential);

			return(Client);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessage(string CommandID, object[] Parameters)
		{
			string												MessageContent=((string) Parameters[0]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(CreateClient()))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusSender> SenderWrapper=new CAsynchDisposable<ServiceBusSender>(Client.CreateSender(CConstants.SERVICE_BUS_TOPIC_NAME)))
					{
						ServiceBusSender						Sender=SenderWrapper;

						ServiceBusMessage						Message=new ServiceBusMessage(MessageContent);

						Sender.SendMessageAsync(Message).Wait();

						Console.WriteLine("MESSAGE SENT !");
					}
				}
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessages(string CommandID, object[] Parameters)
		{
			int													NumberOfMessages=((int) Parameters[0]);
			string												MessageContent=((string) Parameters[1]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(CreateClient()))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusSender> SenderWrapper=new CAsynchDisposable<ServiceBusSender>(Client.CreateSender(CConstants.SERVICE_BUS_TOPIC_NAME)))
					{
						ServiceBusSender						Sender=SenderWrapper;

						ServiceBusMessage[]						MessageArray=new ServiceBusMessage[NumberOfMessages];

						for(int Index=0;Index<NumberOfMessages;Index++)
						{
							string								SingleMessageContent=$"MESSAGE [{MessageContent}] ID [{(Index+1)}].";

							MessageArray[Index]=new ServiceBusMessage(SingleMessageContent);
						}

						Sender.SendMessagesAsync(MessageArray).Wait();

						Console.WriteLine("MESSAGES SENT !");
					}
				}
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessagesAsBatch(string CommandID, object[] Parameters)
		{
			int													NumberOfMessages=((int) Parameters[0]);
			string												MessageContent=((string) Parameters[1]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(CreateClient()))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusSender> SenderWrapper=new CAsynchDisposable<ServiceBusSender>(Client.CreateSender(CConstants.SERVICE_BUS_TOPIC_NAME)))
					{
						ServiceBusSender						Sender=SenderWrapper;

						using(ServiceBusMessageBatch Batch=Sender.CreateMessageBatchAsync().AsTask().Result)
						{
							for(int Index=0;Index<NumberOfMessages;Index++)
							{
								string							SingleMessageContent=$"MESSAGE [{MessageContent}] ID [{(Index+1)}].";
								ServiceBusMessage				Message=new ServiceBusMessage(SingleMessageContent);

								bool							MessageAdded=Batch.TryAddMessage(Message);

								if (MessageAdded==true)
								{
									Console.WriteLine("MESSAGE ADDED to BATCH !");
								}
								else
								{
									Console.WriteLine("MESSAGE NOT ADDED to BATCH !");
								}
							}

							Sender.SendMessagesAsync(Batch).Wait();

							Console.WriteLine("MESSAGES SENT !");
						}
					}
				}
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
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