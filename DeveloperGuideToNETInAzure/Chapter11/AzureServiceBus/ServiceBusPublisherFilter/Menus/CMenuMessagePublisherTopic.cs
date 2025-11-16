using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusPublisherFilter
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
		private static string[] ParsePropertyValuesString(string RawPropertyValues)
		{
			string[]											Values=RawPropertyValues.Split(',',StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries);

			return(Values);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private static int[] ParsePropertyValuesInt(string RawPropertyValues)
		{
			string[]											RawValues=RawPropertyValues.Split(',',StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries);
			int[]												ParsedValues=new int[RawValues.Length];

			for(int Index=0;Index<RawValues.Length;Index++)
			{
				string											RawValue=RawValues[Index];
				int												ParsedValue;

				if (int.TryParse(RawValue,out ParsedValue)==true)
				{
					ParsedValues[Index]=ParsedValue;
				}
				else
				{
					throw(new InvalidOperationException("Can't parse PROPERTY VALUES."));
				}
			}

			return(ParsedValues);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSendMessage(string CommandID, object[] Parameters)
		{
			string												MessageContent=((string) Parameters[0]);
			int													PropertyValue1=((int) Parameters[1]);
			int													PropertyValue2=((int) Parameters[2]);
			string												ToValue=((string) Parameters[3]);

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusSender> SenderWrapper=new CAsynchDisposable<ServiceBusSender>(Client.CreateSender(CConstants.SERVICE_BUS_TOPIC_NAME)))
					{
						ServiceBusSender						Sender=SenderWrapper;

						ServiceBusMessage						Message=new ServiceBusMessage(MessageContent);

						Message.To=ToValue;

						Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_1,PropertyValue1);
						Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_2,PropertyValue2);
						Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_3,CConstants.MESSAGE_FILTER_PROPERTY_VALUE_3);

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
			string												RawPropertyValues1=((string) Parameters[2]);
			string												RawPropertyValues2=((string) Parameters[3]);
			string												RawToValues=((string) Parameters[4]);
			int[]												PropertyValues1=ParsePropertyValuesInt(RawPropertyValues1);
			int[]												PropertyValues2=ParsePropertyValuesInt(RawPropertyValues2);
			string[]											ToValues=ParsePropertyValuesString(RawToValues);

			if (PropertyValues1.Length!=NumberOfMessages)
			{
				throw(new InvalidCastException("NUMBER of PROPERTY 1 VALUES doesn't match NUMBER of MESSAGES."));
			}

			if (PropertyValues2.Length!=NumberOfMessages)
			{
				throw(new InvalidCastException("NUMBER of PROPERTY 2 VALUES doesn't match NUMBER of MESSAGES."));
			}

			if (ToValues.Length!=NumberOfMessages)
			{
				throw(new InvalidCastException("NUMBER of TO VALUES doesn't match NUMBER of MESSAGES."));
			}

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
				{
					ServiceBusClient							Client=ClientWrapper;

					using(CAsynchDisposable<ServiceBusSender> SenderWrapper=new CAsynchDisposable<ServiceBusSender>(Client.CreateSender(CConstants.SERVICE_BUS_TOPIC_NAME)))
					{
						ServiceBusSender						Sender=SenderWrapper;

						ServiceBusMessage[]						MessageArray=new ServiceBusMessage[NumberOfMessages];

						for(int Index=0;Index<NumberOfMessages;Index++)
						{
							string								SingleMessageContent=$"MESSAGE [{MessageContent}] ID [{(Index+1)}].";

							ServiceBusMessage					Message=new ServiceBusMessage(SingleMessageContent);

							Message.To=ToValues[Index];

							Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_1,PropertyValues1[Index]);
							Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_2,PropertyValues2[Index]);
							Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_3,CConstants.MESSAGE_FILTER_PROPERTY_VALUE_3);

							MessageArray[Index]=Message;
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
			string												RawPropertyValues1=((string) Parameters[2]);
			string												RawPropertyValues2=((string) Parameters[3]);
			string												RawToValues=((string) Parameters[4]);
			int[]												PropertyValues1=ParsePropertyValuesInt(RawPropertyValues1);
			int[]												PropertyValues2=ParsePropertyValuesInt(RawPropertyValues2);
			string[]											ToValues=ParsePropertyValuesString(RawToValues);

			if (PropertyValues1.Length!=NumberOfMessages)
			{
				throw(new InvalidCastException("NUMBER of PROPERTY 1 VALUES doesn't match NUMBER of MESSAGES."));
			}

			if (PropertyValues2.Length!=NumberOfMessages)
			{
				throw(new InvalidCastException("NUMBER of PROPERTY 2 VALUES doesn't match NUMBER of MESSAGES."));
			}

			if (ToValues.Length!=NumberOfMessages)
			{
				throw(new InvalidCastException("NUMBER of TO VALUES doesn't match NUMBER of MESSAGES."));
			}

			try
			{
				using(CAsynchDisposable<ServiceBusClient> ClientWrapper=new CAsynchDisposable<ServiceBusClient>(new ServiceBusClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING)))
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

								Message.To=ToValues[Index];

								Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_1,PropertyValues1[Index]);
								Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_2,PropertyValues2[Index]);
								Message.ApplicationProperties.Add(CConstants.MESSAGE_FILTER_PROPERTY_NAME_3,CConstants.MESSAGE_FILTER_PROPERTY_VALUE_3);

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

			CommandsCollection.Add(new CMenuCommand("1","SEND MESSAGE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessage));
			CommandsCollection.Add(new CMenuCommand("2","SEND MESSAGES",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessages));
			CommandsCollection.Add(new CMenuCommand("3","SEND MESSAGES AS BATCH",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessagesAsBatch));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------