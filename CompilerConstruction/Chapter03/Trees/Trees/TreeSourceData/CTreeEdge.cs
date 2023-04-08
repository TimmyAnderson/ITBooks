using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace Trees
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public sealed class CTreeEdge : IEquatable<CTreeEdge>
	{
//-------------------------------------------------------------------------------------------------------
		private CTreeNodeID										MParentNodeID;
		private CTreeNodeID										MChildNodeID;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTreeEdge(CTreeNodeID ParentNodeID, CTreeNodeID ChildNodeID)
		{
			MParentNodeID=ParentNodeID;
			MChildNodeID=ChildNodeID;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public CTreeNodeID										ParentNodeID
		{
			get
			{
				return(MParentNodeID);
			}
			private set
			{
				MParentNodeID=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public CTreeNodeID										ChildNodeID
		{
			get
			{
				return(MChildNodeID);
			}
			private set
			{
				MChildNodeID=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool Equals(CTreeEdge Other)
		{
			if (Other==null)
				return(false);

			if (MParentNodeID!=Other.MParentNodeID)
				return(false);

			if (MChildNodeID!=Other.MChildNodeID)
				return(false);

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder		SB=new StringBuilder();

			SB.Append(this.GetType().Name);
			SB.AppendFormat(", ParentNodeID: [{0}]",MParentNodeID);
			SB.AppendFormat(", ChildNodeID: [{0}]",MChildNodeID);

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------