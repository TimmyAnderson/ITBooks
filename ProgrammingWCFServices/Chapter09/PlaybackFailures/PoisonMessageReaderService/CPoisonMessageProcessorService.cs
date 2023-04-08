using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.CompilerServices;
using System.ServiceModel;
using TestPoisonMessageService;
//-------------------------------------------------------------------------------------------------------
namespace PoisonMessageReaderService
{
//-------------------------------------------------------------------------------------------------------
	// Tento SERVICE SPRACOVAVA POISON MESSAGES.
	[ServiceBehavior(AddressFilterMode=AddressFilterMode.Any,InstanceContextMode=InstanceContextMode.PerCall)]
	public class CPoisonMessageProcessorService : IPoisonMessageContract
	{
//-------------------------------------------------------------------------------------------------------
        public void ThrowException(string Message)
		{
			Console.WriteLine(string.Format("POISON MESSAGE - Date: [{0}], Message: [{1}] !",DateTime.Now,Message));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------