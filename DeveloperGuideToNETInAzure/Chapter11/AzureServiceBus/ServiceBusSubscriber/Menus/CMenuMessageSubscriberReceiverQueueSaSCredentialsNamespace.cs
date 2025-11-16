using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using Azure;
using Azure.Identity;
using Azure.Messaging.ServiceBus;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusSubscriber
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessageSubscriberReceiverQueueSaSCredentialsNamespace : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessageSubscriberReceiverQueueSaSCredentialsNamespace()
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
			string												SaSToken=CreateSaSToken(CConstants.SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE_URL,CConstants.SAS_AUTHORIZATION_RULE_SERVICE_BUS_NAMESPACE_NAME_SUBSCRIBER,CConstants.SAS_AUTHORIZATION_RULE_SERVICE_BUS_NAMESPACE_KEY_SUBSCRIBER);
			AzureSasCredential									Credential=new AzureSasCredential(SaSToken);
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