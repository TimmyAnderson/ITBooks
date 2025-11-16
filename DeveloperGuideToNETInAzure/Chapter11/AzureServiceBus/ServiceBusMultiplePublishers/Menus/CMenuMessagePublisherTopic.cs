using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusMultiplePublishers
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessagePublisherTopic : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessagePublisherTopic()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessages(string CommandID, object[] Parameters)
		{
			int													NumberOfMessages=((int) Parameters[0]);
			string												MessageContent=((string) Parameters[1]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;
					ServiceBusSender[]							Publishers=new ServiceBusSender[NumberOfMessages];

					try
					{
						for(int Index=0;Index<Publishers.Length;Index++)
						{
							Publishers[Index]=Client.CreateSender(CConstants.SERVICE_BUS_TOPIC_NAME);
						}

						Task[]									MessageTasks=new Task[NumberOfMessages];

						for(int Index=0;Index<Publishers.Length;Index++)
						{
							ServiceBusSender					Publisher=Publishers[Index];

							string								SingleMessageContent=$"MESSAGE [{MessageContent}] ID [{(Index+1)}].";
							ServiceBusMessage					Message=new ServiceBusMessage(SingleMessageContent);

							MessageTasks[Index]=Publisher.SendMessageAsync(Message);
						}

						Task.WaitAll(MessageTasks);

						Console.WriteLine("MESSAGES SENT !");
					}
					catch(Exception E)
					{
						Console.WriteLine($"EXCEPTION [{E.Message}].");
					}
					finally
					{
						for(int Index=0;Index<Publishers.Length;Index++)
						{
							ServiceBusSender					Publisher=Publishers[Index];

							if (Publisher!=null)
							{
								Publisher.DisposeAsync().AsTask().Wait();
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

			CommandsCollection.Add(new CMenuCommand("s","SEND MESSAGES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessages));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------