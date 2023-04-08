using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using System.Net.Security;
//-------------------------------------------------------------------------------------------------------
namespace CustomDeadLetterQueueClient
{
//-------------------------------------------------------------------------------------------------------
	// Interface sluzi IBA na definiciu Contact. NIE JE VOCI NEMU VSAK POSTAVENY SERVICE, ABY SA SIMULOVALA MESSAGE VLOZENA DO DEAD LETTER QUEUE.
	[ServiceContract(SessionMode=SessionMode.NotAllowed,ProtectionLevel=ProtectionLevel.None)]
	public interface ICustomDLQTest
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(IsOneWay=true,ProtectionLevel=ProtectionLevel.None)]
		void SomeMethod1(string Value);
		[OperationContract(IsOneWay=true,ProtectionLevel=ProtectionLevel.None)]
		void SomeMethod2(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------