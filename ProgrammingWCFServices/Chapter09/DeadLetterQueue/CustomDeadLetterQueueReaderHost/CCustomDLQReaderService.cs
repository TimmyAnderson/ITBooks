using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using CustomDeadLetterQueueClient;
//-------------------------------------------------------------------------------------------------------
namespace CustomDeadLetterQueueReaderHost
{
//-------------------------------------------------------------------------------------------------------
	// !!!!! AdressFilter MUSI BYT VYBLOKOVANY, pretoze POVODNA MESSAGE BOLA SMEROVANA DO DESTINATION QUEUE a NIE DO DEAD LETTER MESSAGE. Ak by som to NESPRAVIL, tak by MESSAGE BOLA ZAHODENA, lebo NESEDI ADRESA.
	[ServiceBehavior(AddressFilterMode=AddressFilterMode.Any)]
	public class CCustomDLQReaderService : ICustomDLQTest
	{
//-------------------------------------------------------------------------------------------------------
		public void SomeMethod1(string Value)
		{
			Console.WriteLine(string.Format("Message in DEAD LETTER QUEUE - parameter: [{0}] !",Value));

			// Ziskam MSMQ PROPERTY.
			MsmqMessageProperty			MQ=OperationContext.Current.IncomingMessageProperties[MsmqMessageProperty.Name] as MsmqMessageProperty;

			Console.WriteLine(string.Format("AbortCount: [{0}] !",MQ.AbortCount));
			Console.WriteLine(string.Format("DeliveryFailure: [{0}] !",MQ.DeliveryFailure));
			Console.WriteLine(string.Format("DeliveryStatus: [{0}] !",MQ.DeliveryStatus));
			Console.WriteLine(string.Format("MoveCount: [{0}] !",MQ.MoveCount));
			Console.WriteLine("");
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeMethod2(string Value)
		{
			Console.WriteLine(string.Format("Message in DEAD LETTER QUEUE - parameter: [{0}] !",Value));

			// Ziskam MSMQ PROPERTY.
			MsmqMessageProperty			MQ=OperationContext.Current.IncomingMessageProperties[MsmqMessageProperty.Name] as MsmqMessageProperty;

			Console.WriteLine(string.Format("AbortCount: [{0}] !",MQ.AbortCount));
			Console.WriteLine(string.Format("DeliveryFailure: [{0}] !",MQ.DeliveryFailure));
			Console.WriteLine(string.Format("DeliveryStatus: [{0}] !",MQ.DeliveryStatus));
			Console.WriteLine(string.Format("MoveCount: [{0}] !",MQ.MoveCount));
			Console.WriteLine("");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------