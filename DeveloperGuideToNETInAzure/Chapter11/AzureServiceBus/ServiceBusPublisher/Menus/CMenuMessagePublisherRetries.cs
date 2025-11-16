using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusPublisher
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessagePublisherRetries : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessagePublisherRetries()
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
		private void ExecuteCommandSendMessageExponential(string CommandID, object[] Parameters)
		{
			string												MessageContent=((string) Parameters[0]);

			try
			{
				ServiceBusClientOptions							Options=new ServiceBusClientOptions();

				Options.RetryOptions=CreateRetryOptionsExponential();

				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING,Options)))
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
		private void ExecuteCommandSendMessageFixed(string CommandID, object[] Parameters)
		{
			string												MessageContent=((string) Parameters[0]);

			try
			{
				ServiceBusClientOptions							Options=new ServiceBusClientOptions();

				Options.RetryOptions=CreateRetryOptionsFixed();

				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING,Options)))
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
		private void ExecuteCommandSendMessageCustom(string CommandID, object[] Parameters)
		{
			string												MessageContent=((string) Parameters[0]);

			try
			{
				ServiceBusClientOptions							Options=new ServiceBusClientOptions();

				Options.RetryOptions=CreateRetryOptionsCustom();

				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING,Options)))
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
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","SEND MESSAGE EXPONENTIAL",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessageExponential));
			CommandsCollection.Add(new CMenuCommand("2","SEND MESSAGE FIXED",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessageFixed));
			CommandsCollection.Add(new CMenuCommand("3","SEND MESSAGE CUSTOM",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessageCustom));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------