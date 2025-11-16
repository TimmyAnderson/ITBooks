using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Identity;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusSubscriber
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessageSubscriberReceiverQueueClientCredentials : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessageSubscriberReceiverQueueClientCredentials()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private static ServiceBusClient CreateClient()
		{
			ClientSecretCredential								Credential=new ClientSecretCredential(CConstants.TENANT_ID,CConstants.CLIENT_CREDENTIALS_CLIENT_ID_SUBSCRIBER,CConstants.CLIENT_CREDENTIALS_CLIENT_SECRET_SUBSCRIBER);
			ServiceBusClient									Client=new ServiceBusClient(CConstants.SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE,Credential);

			return(Client);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandReceiveMessage(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(CreateClient()))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusReceiver> ReceiverWrapper=new CAsynchDisposable<ServiceBusReceiver>(Client.CreateReceiver(CConstants.SERVICE_BUS_QUEUE_NAME)))
					{
						ServiceBusReceiver						Receiver=ReceiverWrapper;

						TimeSpan								Time=TimeSpan.FromSeconds(WaitTimeInSeconds);

						ServiceBusReceivedMessage				Message=Receiver.ReceiveMessageAsync(Time).Result;

						if (Message!=null)
						{
							string								MessageID=Message.MessageId ?? "";
							string								ContentType=Message.ContentType ?? "";

							byte[]								BodyRaw=Message.Body?.ToArray();
							string								BodyString=(BodyRaw!=null) ? Encoding.UTF8.GetString(BodyRaw) : "";

							Console.WriteLine($"MESSAGE DETECTED. MESSAGE ID [{MessageID}] CONTENT TYPE [{ContentType}] BODY [{BodyString}].");

							// !!!!! MEESAGE bude odstranena z MESSAGE QUEUE.
							Receiver.CompleteMessageAsync(Message).Wait();
						}
						else
						{
							Console.WriteLine("NO MESSAGE RECEIVED !");
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
		private void ExecuteCommandReceiveMessages(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);
			int													MaxNumberOfMessages=((int) Parameters[1]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(CreateClient()))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusReceiver> ReceiverWrapper=new CAsynchDisposable<ServiceBusReceiver>(Client.CreateReceiver(CConstants.SERVICE_BUS_QUEUE_NAME)))
					{
						ServiceBusReceiver						Receiver=ReceiverWrapper;

						TimeSpan								Time=TimeSpan.FromSeconds(WaitTimeInSeconds);

						ServiceBusReceivedMessage[]				Messages=Receiver.ReceiveMessagesAsync(MaxNumberOfMessages,Time).Result.ToArray();

						if (Messages.Length>0)
						{
							for(int Index=0;Index<Messages.Length;Index++)
							{
								ServiceBusReceivedMessage		Message=Messages[Index];

								string							MessageID=Message.MessageId ?? "";
								string							ContentType=Message.ContentType ?? "";

								byte[]							BodyRaw=Message.Body?.ToArray();
								string							BodyString=(BodyRaw!=null) ? Encoding.UTF8.GetString(BodyRaw) : "";

								Console.WriteLine($"MESSAGE DETECTED. MESSAGE ID [{MessageID}] CONTENT TYPE [{ContentType}] BODY [{BodyString}].");

								// !!!!! MEESAGE bude odstranena z MESSAGE QUEUE.
								Receiver.CompleteMessageAsync(Message).Wait();
							}
						}
						else
						{
							Console.WriteLine("NO MESSAGES RECEIVED !");
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

			CommandsCollection.Add(new CMenuCommand("1","RECEIVE MESSAGE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessage));
			CommandsCollection.Add(new CMenuCommand("2","RECEIVE MESSAGES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessages));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------