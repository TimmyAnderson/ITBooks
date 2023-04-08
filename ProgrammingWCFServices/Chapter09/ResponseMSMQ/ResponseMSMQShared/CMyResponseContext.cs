using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace ResponseMSMQShared
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CMyResponseContext
	{
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		private string											MResponseAddress;
		[DataMember]
		private string											MFaultAddress;
		[DataMember]
		private string											MMethodID;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyResponseContext(string ResponseAddress,string FaultAddress,string MethodID)
		{
			MResponseAddress=ResponseAddress;
			MFaultAddress=FaultAddress;
			MMethodID=MethodID;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											ResponseAddress
		{
			get
			{
				return(MResponseAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											FaultAddress
		{
			get
			{
				return(MFaultAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											MethodID
		{
			get
			{
				return(MMethodID);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------