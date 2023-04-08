using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace Contracts
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(Namespace = "http://contoso.com/Restaurant")]
	public interface IRestaurantService3
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(Action="urn:SomeAction")]
		int? RequestReservation(CRequestReservationParams ResParams);
		[OperationContract]
		void ChangeReservation(CChangeReservationNewDateTime NewDateTime);
		[OperationContract(IsOneWay=true)]
		void CancelReservation(int? ReservationID);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------