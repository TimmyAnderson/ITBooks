using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Trees
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CTreeOperations : ITreeOperations
	{
//-------------------------------------------------------------------------------------------------------
		private CTreeNodeID									MRootNodeID;
		private List<CTreeNodeData>							MAllNodeData;
		private List<CTreeEdge>								MAllEdges;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// For empty trees. Just root object must be created.
		public CTreeOperations(CTreeNodeData RootNodeData)
		{
			MAllNodeData=new List<CTreeNodeData>();
			MAllEdges=new List<CTreeEdge>();

			MAllNodeData.Add(RootNodeData);
			MRootNodeID=RootNodeData.TreeNodeID;
		}
//-------------------------------------------------------------------------------------------------------
		// For existing CTreeSourceData.
		public CTreeOperations(CTreeSourceData TreeSourceData)
		{
			MRootNodeID=TreeSourceData.RootNodeID;
			MAllNodeData=TreeSourceData.AllNodeData.ToList();
			MAllEdges=TreeSourceData.AllEdges.ToList();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void InsertNew(CTreeNodeData NewTreeNode, CTreeNodeID ParentTreeNodeID)
		{
			if (MAllNodeData.Where(P => P.TreeNodeID==NewTreeNode.TreeNodeID).FirstOrDefault()!=null)
				throw(new ArgumentException(string.Format("Tree already contains object with CTreeNodeID [{0}] !",NewTreeNode.TreeNodeID)));

			if (MAllNodeData.Where(P => P.TreeNodeID==ParentTreeNodeID).FirstOrDefault()==null)
				throw(new ArgumentException(string.Format("Tree doesn't contain object with CTreeNodeID [{0}] !",ParentTreeNodeID)));

			// Insert Object.
			MAllNodeData.Add(NewTreeNode);
			MAllEdges.Add(new CTreeEdge(ParentTreeNodeID,NewTreeNode.TreeNodeID));
		}
//-------------------------------------------------------------------------------------------------------
		public void InsertExisting(CTreeNodeID ParentTreeNodeID, CTreeNodeID ChildTreeNodeID)
		{
			if (MAllNodeData.Where(P => P.TreeNodeID==ParentTreeNodeID).FirstOrDefault()==null)
				throw(new ArgumentException(string.Format("Tree doesn't contain object with CTreeNodeID [{0}] !",ParentTreeNodeID)));

			if (MAllNodeData.Where(P => P.TreeNodeID==ChildTreeNodeID).FirstOrDefault()==null)
				throw(new ArgumentException(string.Format("Tree doesn't contain object with CTreeNodeID [{0}] !",ParentTreeNodeID)));
			
			MAllEdges.Add(new CTreeEdge(ParentTreeNodeID,ChildTreeNodeID));
		}
//-------------------------------------------------------------------------------------------------------
		public void UpdateObject(CTreeNodeData UpdatedTreeNode)
		{
			// Update NODE DATA.
			for (int i=0;i<MAllNodeData.Count;i++)
			{
				if (MAllNodeData[i].TreeNodeID==UpdatedTreeNode.TreeNodeID)
				{
					MAllNodeData[i]=UpdatedTreeNode;
					break;
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void DeleteLink(CTreeNodeID ParentTreeObjectID, CTreeNodeID ChildTreeObjectID)
		{
			// Remove links.
			MAllEdges.RemoveAll(P => P.ParentNodeID==ParentTreeObjectID && P.ChildNodeID==ChildTreeObjectID);

			CTreeSourceData				TempTreeSourceData=new CTreeSourceData(MRootNodeID,MAllNodeData.ToArray(),MAllEdges.ToArray());

			// Create new TempTree.
			CTree						TempTree=new CTree(TempTreeSourceData);

			MAllNodeData=TempTree.AllNodes.Select(P => P.TreeNodeData).ToList();
			MAllEdges=TempTree.AllLinks.SelectMany((P) => P.Children).Select(P => new CTreeEdge(P.Parent.TreeNodeID,P.TreeNodeID)).ToList();
		}
//-------------------------------------------------------------------------------------------------------
		public void DeleteObject(CTreeNodeID TreeNodeID)
		{
			if (TreeNodeID==MRootNodeID)
				throw(new ArgumentException("Can't delete ROOT object !"));

			// Remove object.
			MAllNodeData.RemoveAll(P => P.TreeNodeID==TreeNodeID);

			// Remove links.
			MAllEdges.RemoveAll(P => P.ChildNodeID==TreeNodeID);

			CTreeSourceData				TempTreeSourceData=new CTreeSourceData(MRootNodeID,MAllNodeData.ToArray(),MAllEdges.ToArray());

			// Create new TempTree.
			CTree						TempTree=new CTree(TempTreeSourceData);

			MAllNodeData=TempTree.AllNodes.Select(P => P.TreeNodeData).ToList();
			MAllEdges=TempTree.AllLinks.SelectMany((P) => P.Children).Select(P => new CTreeEdge(P.Parent.TreeNodeID,P.TreeNodeID)).ToList();
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeSourceData CreateTreeSourceData()
		{
			CTreeSourceData			Ret=new CTreeSourceData(MRootNodeID,MAllNodeData.ToArray(),MAllEdges.ToArray());

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------