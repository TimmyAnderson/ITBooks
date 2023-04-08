using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Trees
{
//-------------------------------------------------------------------------------------------------------
	public class CTree
	{
//-------------------------------------------------------------------------------------------------------
		protected CTreeLink										MRootLink;
		protected CTreeNodeCollection							MAllNodes;
		protected CTreeLinkCollection							MAllLinks;
		protected CTreeNodeDictionary							MNodeDictionary;
		protected CTreeNodeChildrenDictionary					MTreeNodeChildrenDictionary;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTree(CTreeSourceData TreeSourceData)
		{
			MRootLink=null;
			MAllNodes=new CTreeNodeCollection();
			MAllLinks=new CTreeLinkCollection();
			MNodeDictionary=new CTreeNodeDictionary();

			// Method calls som virtual methods.
			ConstructTree(TreeSourceData);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTreeNodeCollection								AllNodes
		{
			get
			{
				return(MAllNodes);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLink										RootLink
		{
			get
			{
				return(MRootLink);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLinkCollection								AllLinks
		{
			get
			{
				return(MAllLinks);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeNodeDictionary								ObjectDictionary
		{
			get
			{
				return(MNodeDictionary);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void ConstructTree(CTreeSourceData TreeSourceData)
		{
			TreeConstructionStartedEvent(TreeSourceData);

			// Add all NODES.
			foreach(CTreeNodeData TND in TreeSourceData.AllNodeData)
			{
				CTreeNode			Node=new CTreeNode(TND);

				MAllNodes.Add(Node);
				MNodeDictionary.Add(Node.TreeNodeID,Node);
			}

			MTreeNodeChildrenDictionary=new CTreeNodeChildrenDictionary();

			// Add all NODES to dictionary.
			foreach(CTreeEdge Edge in TreeSourceData.AllEdges)
				MTreeNodeChildrenDictionary.Add(Edge.ParentNodeID,Edge.ChildNodeID);
			
			// Find root.
			CTreeNode				Root=MAllNodes.Find(P => P.TreeNodeID.Equals(TreeSourceData.RootNodeID));
			
			if (Root==null)
				throw(new InvalidOperationException("Can't find Root object in CTreeNodeCollection !"));

			Root.TreeOccurrences++;
			MRootLink=new CTreeLink(Root,null);
			MAllLinks.Add(MRootLink);

			FillNode(TreeSourceData,MRootLink);

			RemoveNotConnectedObjects();

			TreeConstructionCompleteEvent();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private bool CanInsertExistingDirect(CTreeNodeID ChildObjectID, CTreeLink ParentNode)
		{
			CTreeLink		Node=ParentNode;

			if (Node!=null && Node.PointsToTreeObject(ChildObjectID)==true)
				return(true);

			while(Node!=null)
			{
				if (Node.PointsToTreeObject(ChildObjectID)==true)
					return(true);

				Node=Node.Parent;
			}

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		private void FillNode(CTreeSourceData TreeSourceData, CTreeLink TreeLink)
		{
			if (MTreeNodeChildrenDictionary[TreeLink.TreeNodeID]==null)
				return;

			// Find ALL CHILDREN for LINK.
			CTreeNodeID[]						Children=MTreeNodeChildrenDictionary[TreeLink.TreeNodeID].ToArray();

			foreach(CTreeNodeID NodeID in Children)
			{
				// For NODE for NodeID
				CTreeNode						ChildNode=MNodeDictionary[NodeID];
				
				if (ChildNode==null)
					throw(new InvalidOperationException(string.Format("Can't find CHILD NODE for ID: [{0}] !",TreeLink.TreeNodeID)));

				ChildNode.TreeOccurrences++;

				CTreeLink						ChildLink=new CTreeLink(ChildNode,TreeLink);

				MAllLinks.Add(ChildLink);
				
				TreeLink.Children.Add(ChildLink);

				// Do recursion.
				FillNode(TreeSourceData,ChildLink);
			}
		}
//-----------------------------------------------------------------------------
		private void FindSubNodesByPredicate(Predicate<CTreeLink> AddNodePredicate, Predicate<CTreeLink> SearchSubNodesPredicate, CTreeLink TreeNode, List<CTreeLink> FoundNodes, int NumberOfNodesToFound)
		{
			if (FoundNodes.Count==NumberOfNodesToFound && NumberOfNodesToFound>0)
				return;

			if (AddNodePredicate(TreeNode)==true)
			{
				FoundNodes.Add(TreeNode);

				if (FoundNodes.Count==NumberOfNodesToFound && NumberOfNodesToFound>0)
					return;
			}

			foreach(CTreeLink TN in TreeNode.Children.Collection)
				if (SearchSubNodesPredicate(TN)==true)
					FindSubNodesByPredicate(AddNodePredicate,SearchSubNodesPredicate,TN,FoundNodes,NumberOfNodesToFound);
		}
//-------------------------------------------------------------------------------------------------------
		private void RemoveNotConnectedObjects()
		{
			MAllNodes=new CTreeNodeCollection(MAllNodes.Where(P => P.TreeOccurrences>0).ToArray());

			CTreeNodeDictionary				ObjectDictionary=new CTreeNodeDictionary();

			foreach(CTreeNode TOW in MAllNodes)
				ObjectDictionary.Add(TOW.TreeNodeID,TOW);

			MNodeDictionary=ObjectDictionary;
		}
//-------------------------------------------------------------------------------------------------------
		private void InternalTraverseTree(Action<CTreeNodeData,int,object> NodeAction, CTreeNodeID TreeNodeID, object Param, int Level)
		{
			CTreeNode				TreeNode=MNodeDictionary[TreeNodeID];

			NodeAction(TreeNode.TreeNodeData,Level,Param);

			List<CTreeNodeID>		ChildNodes=MTreeNodeChildrenDictionary[TreeNodeID];

			Level++;

			if (ChildNodes!=null)
			{
				foreach(CTreeNodeID ChildNode in ChildNodes)
					InternalTraverseTree(NodeAction,ChildNode,Param,Level);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected virtual void TreeConstructionStartedEvent(CTreeSourceData TreeSourceData)
		{
			// Empty.
		}
//-------------------------------------------------------------------------------------------------------
		protected virtual void TreeConstructionCompleteEvent()
		{
			// Empty.
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool CanInsertExisting(CTreeNodeID ChildObjectID, CTreeLink ParentNode)
		{
			CTreeLink[]						ChildNodes=MAllLinks.Collection.Where(P => P.PointsToTreeObject(ParentNode.TreeNodeID)==true).ToArray();

			foreach(CTreeLink Child in ParentNode.Children.Collection)
				if (Child.TreeNodeID==ChildObjectID)
					return(true);

			foreach(CTreeLink TL in ChildNodes)
				if (CanInsertExistingDirect(ChildObjectID,TL)==true)
					return(true);

			return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLink GetFirstNodePointingToObject(CTreeNodeID TreeObjectID)
		{
			CTreeLink						Ret=MAllLinks.Collection.Where(P => P.PointsToTreeObject(TreeObjectID)==true).FirstOrDefault();

			return(Ret);
		}
//-----------------------------------------------------------------------------
		public CTreeLink[] GetAllNodesPointingToObject(CTreeNodeID TreeObjectID)
		{
			CTreeLink[]					Ret=MAllLinks.Collection.Where(P => P.PointsToTreeObject(TreeObjectID)==true).ToArray();

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeNode GetObjectByObjectID(CTreeNodeID TreeObjectID)
		{
			CTreeNode					Ret=MNodeDictionary[TreeObjectID];
				
			if (Ret!=null)
				return(Ret);
			else
				return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLink GetFirstNodeByPredicate(Predicate<CTreeLink> Predicate)
		{
			CTreeLink						Ret=MAllLinks.Collection.Where(P => Predicate(P)==true).FirstOrDefault();

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLink[] GetAllNodesByPredicate(Predicate<CTreeLink> Predicate)
		{
			CTreeLink[]						Ret=MAllLinks.Collection.Where(P => Predicate(P)==true).ToArray();

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeNode GetFirstObjectByPredicate(Predicate<CTreeNode> Predicate)
		{
			CTreeNode						Ret=MAllNodes.Collection.Where(P => Predicate(P)==true).FirstOrDefault();

			if (Ret!=null)
				return(Ret);
			else
				return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeNode[] GetAllObjectsByPredicate(Predicate<CTreeNode> Predicate)
		{
			CTreeNode[]						Ret=MAllNodes.Collection.Where(P => Predicate(P)==true).ToArray();

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		public TTreeObject[] GetAllObjectsByPredicate<TTreeObject>(Predicate<TTreeObject> Predicate)
		{
			if (Predicate!=null)
			{
				TTreeObject[]				Ret=MAllNodes.Collection.Select(P => P).OfType<TTreeObject>().Where(P => Predicate(P)==true).ToArray();

				return(Ret);
			}
			else
			{
				TTreeObject[]				Ret=MAllNodes.Collection.Select(P => P).OfType<TTreeObject>().ToArray();

				return(Ret);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLink GetFirstSubNodeByPredicate(Predicate<CTreeLink> AddNodePredicate, Predicate<CTreeLink> SearchSubNodesPredicate, CTreeLink TreeNode)
		{
			List<CTreeLink>			Nodes=new List<CTreeLink>();

			FindSubNodesByPredicate(AddNodePredicate,SearchSubNodesPredicate,TreeNode,Nodes,1);

			if (Nodes.Count>0)
				return(Nodes[0]);
			else
				return(null);
		}
//-------------------------------------------------------------------------------------------------------
		public List<CTreeLink> GetAllSubNodesByPredicate(Predicate<CTreeLink> AddNodePredicate, Predicate<CTreeLink> SearchSubNodesPredicate, CTreeLink TreeNode, bool DistinctObjects)
		{
			List<CTreeLink>			Nodes=new List<CTreeLink>();

			FindSubNodesByPredicate(AddNodePredicate,SearchSubNodesPredicate,TreeNode,Nodes,0);

			if (DistinctObjects==true)
			{
				List<CTreeLink>		Ret=new List<CTreeLink>();

				foreach(CTreeLink TN in Nodes)
				{
					bool			Add=true;

					foreach(CTreeLink TNAdded in Ret)
					{
						if (TN.TreeNodeID==TNAdded.TreeNodeID)
						{
							Add=false;
							break;
						}
					}

					if (Add==true)
						Ret.Add(TN);
				}

				return(Ret);
			}
			else
				return(Nodes);
		}
//-------------------------------------------------------------------------------------------------------
		public void TraverseTree(Action<CTreeNodeData,int,object> NodeAction, object Param)
		{
			InternalTraverseTree(NodeAction, MRootLink.TreeNodeID, Param, 1);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------