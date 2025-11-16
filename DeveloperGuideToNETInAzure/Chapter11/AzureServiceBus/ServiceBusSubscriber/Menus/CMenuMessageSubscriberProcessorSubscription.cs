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
	public sealed class CMenuMessageSubscriberProcessorSubscription : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private ServiceBusClient								MClient;
		private ServiceBusProcessor								MMessageProcessor;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessageSubscriberProcessorSubscription()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private Task MMessageProcessorProcessMessageAsync(ProcessMessageEventArgs Args)
		{
			ServiceBusReceivedMessage							ReceivedMessage=Args.Message;

			string												Identifier=Args?.Identifier ?? "";
			string												EntityPath=Args?.EntityPath ?? "";
			string												FullyQualifiedNamespace=Args?.FullyQualifiedNamespace ?? "";
			
			string												MessageID=ReceivedMessage?.MessageId ?? "";
			string												ContentType=ReceivedMessage?.ContentType ?? "";

			byte[]												BodyRaw=ReceivedMessage?.Body?.ToArray();
			string												BodyString=(BodyRaw!=null) ? Encoding.UTF8.GetString(BodyRaw) : "";

			Console.WriteLine($"MESSAGE DETECTED. IDENTIFIER [{Identifier}] ENTITY PATH [{EntityPath}] FULLY QUALIFIED NAMESPACE [{FullyQualifiedNamespace}] MESSAGE ID [{MessageID}] CONTENT TYPE [{ContentType}] BODY [{BodyString}].");

			// !!!!! MEESAGE bude odstranena z MESSAGE QUEUE.
			Args.CompleteMessageAsync(ReceivedMessage).Wait();

			Task												Result=Task.CompletedTask;

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task MMessageProcessorProcessErrorAsync(ProcessErrorEventArgs Args)
		{
			string												Identifier=Args.Identifier ?? "";
			string												EntityPath=Args.EntityPath ?? "";
			string												FullyQualifiedNamespace=Args.FullyQualifiedNamespace ?? "";
			ServiceBusErrorSource								ErrorSource=Args.ErrorSource;
			Exception											Exception=Args.Exception;

			string												ExceptionMessage=Exception?.Message ?? "";

			if ((Exception is ServiceBusException)==true)
			{
				ServiceBusException								TypedException=(ServiceBusException) Exception;

				string											FailureReason=TypedException.Reason.ToString() ?? "";

				Console.WriteLine($"ERROR DETECTED. IDENTIFIER [{Identifier}] ENTITY PATH [{EntityPath}] FULLY QUALIFIED NAMESPACE [{FullyQualifiedNamespace}] ERROR SOURCE [{ErrorSource}] EXCEPTION [{ExceptionMessage}] REASON [{FailureReason}].");
			}
			else
			{
				Console.WriteLine($"ERROR DETECTED. IDENTIFIER [{Identifier}] ENTITY PATH [{EntityPath}] FULLY QUALIFIED NAMESPACE [{FullyQualifiedNamespace}] ERROR SOURCE [{ErrorSource}] EXCEPTION [{ExceptionMessage}].");
			}

			Task												Result=Task.CompletedTask;

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void CloseProcessor()
		{
			if (MClient==null)
			{
				return;
			}

			if (MMessageProcessor!=null)
			{
				try
				{
					MMessageProcessor.StopProcessingAsync().Wait();

					Console.WriteLine("MESSAGE PROCESSING STOPPED.");
				}
				catch(ServiceBusException E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
				}
				catch(Exception E)
				{
					Console.WriteLine($"EXCEPTION [{E.Message}].");
				}

				try
				{
					MMessageProcessor.ProcessMessageAsync-=MMessageProcessorProcessMessageAsync;
				}
				catch
				{
				}

				try
				{
					MMessageProcessor.ProcessErrorAsync-=MMessageProcessorProcessErrorAsync;
				}
				catch
				{
				}

				MMessageProcessor.DisposeAsync().AsTask().Wait();

				MMessageProcessor=null;
			}

			MClient.DisposeAsync().AsTask().Wait();

			Console.WriteLine("CLIENT DISPOSED.");

			MClient=null;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStartReceivingMessages(string CommandID, object[] Parameters)
		{
			if (MClient!=null)
			{
				Console.WriteLine("CLIENT is ALREADY CREATED.");
				return;
			}

			try
			{
				MClient=new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING);

				MMessageProcessor=MClient.CreateProcessor(CConstants.SERVICE_BUS_TOPIC_NAME,CConstants.SERVICE_BUS_SUBSCRIPTION_NAME);

				MMessageProcessor.ProcessMessageAsync+=MMessageProcessorProcessMessageAsync;
				MMessageProcessor.ProcessErrorAsync+=MMessageProcessorProcessErrorAsync;

				MMessageProcessor.StartProcessingAsync().Wait();

				Console.WriteLine("MESSAGE PROCESSING STARTED.");
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				CloseProcessor();
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStopReceivingMessages(string CommandID, object[] Parameters)
		{
			if (MClient==null)
			{
				Console.WriteLine("CLIENT doesn't EXIST.");
				return;
			}

			CloseProcessor();
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","START RECEIVING MESSAGES",new EMenuCommandParameterType[0],ExecuteCommandStartReceivingMessages));
			CommandsCollection.Add(new CMenuCommand("2","STOP RECEIVING MESSAGES",new EMenuCommandParameterType[0],ExecuteCommandStopReceivingMessages));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------