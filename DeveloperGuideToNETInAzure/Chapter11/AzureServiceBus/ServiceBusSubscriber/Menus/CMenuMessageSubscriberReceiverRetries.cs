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
	public sealed class CMenuMessageSubscriberReceiverRetries : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessageSubscriberReceiverRetries()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private ServiceBusRetryOptions CreateRetryOptionsExponential()
		{
			ServiceBusRetryOptions								RetryOptions=new ServiceBusRetryOptions();

			RetryOptions.Mode=ServiceBusRetryMode.Exponential;
			RetryOptions.MaxRetries=5;
			RetryOptions.Delay=TimeSpan.FromSeconds(1);
			RetryOptions.MaxDelay=TimeSpan.FromSeconds(30);

			return(RetryOptions);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private ServiceBusRetryOptions CreateRetryOptionsFixed()
		{
			ServiceBusRetryOptions								RetryOptions=new ServiceBusRetryOptions();

			RetryOptions.Mode=ServiceBusRetryMode.Fixed;
			RetryOptions.MaxRetries=5;
			RetryOptions.Delay=TimeSpan.FromSeconds(3);

			return(RetryOptions);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private ServiceBusRetryOptions CreateRetryOptionsCustom()
		{
			ServiceBusRetryOptions								RetryOptions=new ServiceBusRetryOptions();

			RetryOptions.CustomRetryPolicy=new CMyRetryPolicy();

			return(RetryOptions);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandReceiveMessageExponential(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);

			try
			{
				ServiceBusClientOptions							Options=new ServiceBusClientOptions();

				Options.RetryOptions=CreateRetryOptionsExponential();

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
		private void ExecuteCommandReceiveMessageFixed(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);

			try
			{
				ServiceBusClientOptions							Options=new ServiceBusClientOptions();

				Options.RetryOptions=CreateRetryOptionsFixed();

				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING,Options)))
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
		private void ExecuteCommandReceiveMessageCustom(string CommandID, object[] Parameters)
		{
			int													WaitTimeInSeconds=((int) Parameters[0]);

			try
			{
				ServiceBusClientOptions							Options=new ServiceBusClientOptions();

				Options.RetryOptions=CreateRetryOptionsCustom();

				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING,Options)))
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
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","RECEIVE MESSAGE EXPONENTIAL",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessageExponential));
			CommandsCollection.Add(new CMenuCommand("2","RECEIVE MESSAGE FIXED",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessageFixed));
			CommandsCollection.Add(new CMenuCommand("3","RECEIVE MESSAGE CUSTOM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandReceiveMessageCustom));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------