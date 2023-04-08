using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ReliableSessionsService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	// !!! Vyziadam si pouzitie bindingu s Reliable Session.
	//[DeliveryRequirements(RequireOrderedDelivery=true)]
	public interface IToUpperService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string ToUpper(string Value);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------