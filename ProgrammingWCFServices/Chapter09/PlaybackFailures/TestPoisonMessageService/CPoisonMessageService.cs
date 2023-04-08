using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace TestPoisonMessageService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CPoisonMessageService : IPoisonMessageContract
	{
//-------------------------------------------------------------------------------------------------------
		static private int										MCounter;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Aby som simulovat POISON MESSAGE MUSIM POUZIVAT SERVER SIDE TRANSACTIONS.
		[OperationBehavior(TransactionScopeRequired=true,TransactionAutoComplete=true)]
        public void ThrowException(string Message)
		{
			MCounter++;

			Console.WriteLine(string.Format("Date: [{0}], Message: [{1}] !",DateTime.Now,Message));

			// Service stale hodi EXCEPTION a tym padom vytvori POISON MESSAGE.
			throw(new Exception("SOME ERROR !"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------