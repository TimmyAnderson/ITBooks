using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace Contracts
{
//-------------------------------------------------------------------------------------------------------
	[DataContract(Namespace="http://contoso.com/Restaurant")]
	public sealed class CChangeReservationFault
	{
//-------------------------------------------------------------------------------------------------------
		[DataMember(Name="FaultReason", IsRequired=true)]
		private string											MReason;
		[DataMember(Name="ReservationId", EmitDefaultValue=true, IsRequired=false)]
		private int?											MReservationID;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationFault(string Reason, int? ReservationID)
		{
			MReason=Reason;
			MReservationID=ReservationID;
		}
//-------------------------------------------------------------------------------------------------------
		public CChangeReservationFault(string Reason)
		{
			MReason=Reason;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Reason
		{
			get
			{
				return(MReason);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int?												ReservationID
		{
			get
			{
				return(MReservationID);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------