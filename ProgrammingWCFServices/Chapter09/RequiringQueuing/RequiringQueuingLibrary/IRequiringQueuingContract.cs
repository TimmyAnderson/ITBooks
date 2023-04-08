using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Messaging;
//-------------------------------------------------------------------------------------------------------
namespace RequiringQueuingLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	[DeliveryRequirements(QueuedDeliveryRequirements=QueuedDeliveryRequirementsMode.Required,RequireOrderedDelivery=false)]
	public interface IRequiringQueuingContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract(IsOneWay=true)]
		void PrintText(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------