using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusSubscriber
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessageSubscriberReceiverSubscriptionDeadLetterQueue : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessageSubscriberReceiverSubscriptionDeadLetterQueue()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandReceiveMessageFromQueue(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);
			int													RawSendMessageToDeadLetterQueue=((int) Parameters[1]);

			bool												SendMessageToDeadLetterQueue;

			if (RawSendMessageToDeadLetterQueue==1)
			{
				SendMessageToDeadLetterQueue=true;
			}
			else
			{
				SendMessageToDeadLetterQueue=false;
			}

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusReceiver> ReceiverWrapper=new CAsynchDisposable<ServiceBusReceiver>(Client.CreateReceiver(CConstants.SERVICE_BUS_TOPIC_NAME,CConstants.SERVICE_BUS_SUBSCRIPTION_NAME)))
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

							if (SendMessageToDeadLetterQueue==false)
							{
								// !!!!! MEESAGE bude odstranena z MESSAGE QUEUE.
								Receiver.CompleteMessageAsync(Message).Wait();
							}
							else
							{
								// !!!!! MESSAGE bude preposlana do DEAD LETTER QUEUE.
								Receiver.DeadLetterMessageAsync(Message,"SOME REASON.","SOME ERROR.").Wait();
							}
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
		private void ExecuteCommandReceiveMessagesFromQueue(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);
			int													MaxNumberOfMessages=((int) Parameters[1]);
			int													RawSendMessagesToDeadLetterQueue=((int) Parameters[2]);

			bool												SendMessagesToDeadLetterQueue;

			if (RawSendMessagesToDeadLetterQueue==1)
			{
				SendMessagesToDeadLetterQueue=true;
			}
			else
			{
				SendMessagesToDeadLetterQueue=false;
			}

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusReceiver> ReceiverWrapper=new CAsynchDisposable<ServiceBusReceiver>(Client.CreateReceiver(CConstants.SERVICE_BUS_TOPIC_NAME,CConstants.SERVICE_BUS_SUBSCRIPTION_NAME)))
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

								if (SendMessagesToDeadLetterQueue==false)
								{
									// !!!!! MEESAGE bude odstranena z MESSAGE QUEUE.
									Receiver.CompleteMessageAsync(Message).Wait();
								}
								else
								{
									string						Reason=$"SOME REASON [{(Index+1)}].";
									string						Error=$"SOME ERROR [{(Index+1)}].";

									// !!!!! MESSAGE bude preposlana do DEAD LETTER QUEUE.
									Receiver.DeadLetterMessageAsync(Message,Reason,Error).Wait();
								}
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
		private void ExecuteCommandReceiveMessageFromDeadLetterQueue(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;
					ServiceBusReceiverOptions					Options=new ServiceBusReceiverOptions();

					Options.SubQueue=SubQueue.DeadLetter;

					using(CAsynchDisposable<ServiceBusReceiver> ReceiverWrapper=new CAsynchDisposable<ServiceBusReceiver>(Client.CreateReceiver(CConstants.SERVICE_BUS_TOPIC_NAME,CConstants.SERVICE_BUS_SUBSCRIPTION_NAME,Options)))
					{
						ServiceBusReceiver						Receiver=ReceiverWrapper;

						TimeSpan								Time=TimeSpan.FromSeconds(WaitTimeInSeconds);

						ServiceBusReceivedMessage				Message=Receiver.ReceiveMessageAsync(Time).Result;

						if (Message!=null)
						{
							string								MessageID=Message.MessageId ?? "";
							string								ContentType=Message.ContentType ?? "";

							string								DeadLetterReason=Message.DeadLetterReason ?? "";
							string								DeadLetterErrorDescription=Message.DeadLetterErrorDescription ?? "";

							byte[]								BodyRaw=Message.Body?.ToArray();
							string								BodyString=(BodyRaw!=null) ? Encoding.UTF8.GetString(BodyRaw) : "";

							Console.WriteLine($"MESSAGE DETECTED. MESSAGE ID [{MessageID}] CONTENT TYPE [{ContentType}] DEAD LETTER REASON [{DeadLetterReason}] DEAD LETTER ERROR DESCRIPTION [{DeadLetterErrorDescription}] BODY [{BodyString}].");

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
		private void ExecuteCommandReceiveMessagesFromDeadLetterQueue(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);
			int													MaxNumberOfMessages=((int) Parameters[1]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;
					ServiceBusReceiverOptions					Options=new ServiceBusReceiverOptions();

					Options.SubQueue=SubQueue.DeadLetter;

					using(CAsynchDisposable<ServiceBusReceiver> ReceiverWrapper=new CAsynchDisposable<ServiceBusReceiver>(Client.CreateReceiver(CConstants.SERVICE_BUS_TOPIC_NAME,CConstants.SERVICE_BUS_SUBSCRIPTION_NAME,Options)))
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

								string							DeadLetterReason=Message.DeadLetterReason ?? "";
								string							DeadLetterErrorDescription=Message.DeadLetterErrorDescription ?? "";

								byte[]							BodyRaw=Message.Body?.ToArray();
								string							BodyString=(BodyRaw!=null) ? Encoding.UTF8.GetString(BodyRaw) : "";

								Console.WriteLine($"MESSAGE DETECTED. MESSAGE ID [{MessageID}] CONTENT TYPE [{ContentType}] DEAD LETTER REASON [{DeadLetterReason}] DEAD LETTER ERROR DESCRIPTION [{DeadLetterErrorDescription}] BODY [{BodyString}].");

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

			CommandsCollection.Add(new CMenuCommand("1","RECEIVE MESSAGE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessageFromQueue));
			CommandsCollection.Add(new CMenuCommand("2","RECEIVE MESSAGES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessagesFromQueue));
			CommandsCollection.Add(new CMenuCommand("3","RECEIVE MESSAGE FROM DEAD LETTER QUEUE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessageFromDeadLetterQueue));
			CommandsCollection.Add(new CMenuCommand("4","RECEIVE MESSAGES FROM DEAD LETTER QUEUE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessagesFromDeadLetterQueue));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------