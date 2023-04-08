using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ReceiveContextService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CReceiveContextContract2 : IReceiveContextContract
	{
//-------------------------------------------------------------------------------------------------------
		static private int										MCounter;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Aby som simulovat POISON MESSAGE MUSIM POUZIVAT SERVER SIDE TRANSACTIONS.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
		[ReceiveContextEnabled(ManualControl=true)]
        public void PrintMessage(string Message)
		{
			MCounter++;

			ReceiveContext				RC;

			ReceiveContext.TryGet(OperationContext.Current.IncomingMessageProperties,out RC);

			Console.WriteLine(string.Format("SERVICE 2 - Date: [{0}], Message: [{1}], State: [{2}] !",DateTime.Now.ToShortTimeString(),Message,RC.State));

			// Spravi COMPLETE - MESSAGE sa ODSTRANI z QUEUE.
			RC.Complete(TimeSpan.FromSeconds(3));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------