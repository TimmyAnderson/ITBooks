using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CallbackFaultsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public class CFaultDetails
	{
//-------------------------------------------------------------------------------------------------------
		private	string											MMyDetailedMessage;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFaultDetails(string MyDetailedMessage)
		{
			MMyDetailedMessage=MyDetailedMessage;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public string				MyDetailedMessage
		{
			get
			{
				return(MMyDetailedMessage);
			}
			internal set
			{
				MMyDetailedMessage=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MMyDetailedMessage);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------