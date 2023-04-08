using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace Contracts
{
//-------------------------------------------------------------------------------------------------------
	[MessageContract(WrapperName="CChangeReservationNewDateTime", WrapperNamespace="http://contoso.com/Restaurant")]
	public sealed class CChangeReservationNewDateTime2
	{
//-------------------------------------------------------------------------------------------------------
		[MessageHeader(Name="ReservationID", MustUnderstand=true)]
		private int?											MReservationID;
		[MessageBodyMember(Name="NewReservationInfo")]
		private CRequestReservationParams						MNewReservationInfo;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationNewDateTime2()
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationNewDateTime2(int? ReservationID, CRequestReservationParams NewInfo)
		{
			MNewReservationInfo=NewInfo;
			MReservationID=ReservationID;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int?												ReservationID
		{
			get
			{
				return(MReservationID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CRequestReservationParams						NewReservationInfo
		{
			get
			{
				return(MNewReservationInfo);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------