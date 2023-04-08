using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.IO;
//-------------------------------------------------------------------------------------------------------
namespace Trees
{
//-------------------------------------------------------------------------------------------------------
	[DataContract]
	public sealed class CTreeSourceData
	{
//-------------------------------------------------------------------------------------------------------
		private CTreeNodeID										MRootNodeID;
		private CTreeNodeData[]									MAllNodeData;
		private CTreeEdge[]										MAllEdges;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTreeSourceData(CTreeNodeID RootNodeID, CTreeNodeData[] AllNodes, CTreeEdge[] AllEdges)
		{
			for (int i=0;i<(AllNodes.Length-1);i++)
				for (int j=i+1;j<AllNodes.Length;j++)
					if (AllNodes[i].Equals(AllNodes[j])==true)
						throw(new ArgumentException(string.Format("Two NODES [{0}] and [{1}] are EQUAL !",AllNodes[i].TreeNodeID,AllNodes[j].TreeNodeID),"AllObjects"));

			for (int i=0;i<(AllEdges.Length-1);i++)
				for (int j=i+1;j<AllEdges.Length;j++)
					if (AllEdges[i].Equals(AllEdges[j])==true)
						throw(new ArgumentException(string.Format("Two EDGES [{0}] and [{1}] are EQUAL !",AllEdges[i],AllEdges[j]),"AllNodes"));

			MRootNodeID=RootNodeID;
			MAllNodeData=AllNodes;
			MAllEdges=AllEdges;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public CTreeNodeID										RootNodeID
		{
			get
			{
				return(MRootNodeID);
			}
			private set
			{
				MRootNodeID=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public CTreeNodeData[]									AllNodeData
		{
			get
			{
				return(MAllNodeData);
			}
			private set
			{
				MAllNodeData=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
		[DataMember]
		public CTreeEdge[]										AllEdges
		{
			get
			{
				return(MAllEdges);
			}
			private set
			{
				MAllEdges=value;
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static CTreeSourceData DeserializeFromStream(Stream SerializationStream)
		{
			DataContractSerializer			DCS=new DataContractSerializer(typeof(CTreeSourceData));
			CTreeSourceData					TreeDataSource=(CTreeSourceData) DCS.ReadObject(SerializationStream);

			return(TreeDataSource);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SerializeToStream(Stream SerializationStream)
		{
			DataContractSerializer			DCS=new DataContractSerializer(typeof(CTreeSourceData));

			DCS.WriteObject(SerializationStream,this);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------