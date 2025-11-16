using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusMultipleSubscribers
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessageSubscriberReceiver : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessageSubscriberReceiver()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessages(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);
			int													MaxNumberOfMessages=((int) Parameters[1]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;
					ServiceBusReceiver[]						Receivers=new ServiceBusReceiver[MaxNumberOfMessages];

					try
					{
						for(int Index=0;Index<Receivers.Length;Index++)
						{
							Receivers[Index]=Client.CreateReceiver(CConstants.SERVICE_BUS_TOPIC_NAME,CConstants.SERVICE_BUS_SUBSCRIPTION_NAME);
						}

						TimeSpan								Time=TimeSpan.FromSeconds(WaitTimeInSeconds);
						Task<ServiceBusReceivedMessage>[]		ReceivedMessageTasks=new Task<ServiceBusReceivedMessage>[MaxNumberOfMessages];

						for(int Index=0;Index<Receivers.Length;Index++)
						{
							ServiceBusReceiver					Receiver=Receivers[Index];

							ReceivedMessageTasks[Index]=Receiver.ReceiveMessageAsync(Time);
						}

						Task.WaitAll(ReceivedMessageTasks);

						for(int Index=0;Index<ReceivedMessageTasks.Length;Index++)
						{
							Task<ServiceBusReceivedMessage>		ReceivedMessageTask=ReceivedMessageTasks[Index];
							ServiceBusReceivedMessage			Message=ReceivedMessageTask.Result;

							if (Message!=null)
							{
								ServiceBusReceiver				Receiver=Receivers[Index];

								string							MessageID=Message.MessageId ?? "";
								string							ContentType=Message.ContentType ?? "";

								byte[]							BodyRaw=Message.Body?.ToArray();
								string							BodyString=(BodyRaw!=null) ? Encoding.UTF8.GetString(BodyRaw) : "";

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
					catch(Exception E)
					{
						Console.WriteLine($"EXCEPTION [{E.Message}].");
					}
					finally
					{
						for(int Index=0;Index<Receivers.Length;Index++)
						{
							ServiceBusReceiver					Receiver=Receivers[Index];

							if (Receiver!=null)
							{
								Receiver.DisposeAsync().AsTask().Wait();
							}
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

			CommandsCollection.Add(new CMenuCommand("m","RECEIVE MESSAGES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandSendMessages));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------