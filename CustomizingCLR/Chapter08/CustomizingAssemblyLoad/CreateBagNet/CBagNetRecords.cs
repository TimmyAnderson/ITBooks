using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//------------------------------------------------------------------------------------------------------
namespace CreateBagNet
{
//------------------------------------------------------------------------------------------------------
	[DataContract]
	public sealed class CBagNetRecords
	{
//------------------------------------------------------------------------------------------------------
		private string											MBagExecutable;
		private string											MRunnableType;
		private CBagNetRecord[]									MBagNetRecords;
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		public CBagNetRecords(string BagExecutable, string RunnableType, CBagNetRecord[] BagNetRecords)
		{
			MBagExecutable=BagExecutable;
			MRunnableType=RunnableType;
			MBagNetRecords=BagNetRecords;
		}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											BagExecutable
		{
			get
			{
				return(MBagExecutable);
			}
			private set
			{
				MBagExecutable=value;
			}
		}
//------------------------------------------------------------------------------------------------------
		[DataMember]
		public string											RunnableType
		{
			get
			{
				return(MRunnableType);
			}
			private set
			{
				MRunnableType=value;
			}
		}
//------------------------------------------------------------------------------------------------------
		[DataMember]
		public CBagNetRecord[]									BagNetRecords
		{
			get
			{
				return(MBagNetRecords);
			}
			private set
			{
				MBagNetRecords=value;
			}
		}
//------------------------------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------