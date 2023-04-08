using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Trees
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CTreeLink
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CTreeNode								MTreeNodeData;
		private readonly CTreeLink								MParent;
		private readonly CTreeLinkCollection					MChildren;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTreeLink(CTreeNode TreeNodeData, CTreeLink ParentNode)
		{
			MTreeNodeData=TreeNodeData;
			MParent=ParentNode;
			MChildren=new CTreeLinkCollection();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTreeNode										TreeNode
		{
			get
			{
				return(MTreeNodeData);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLink										Parent
		{
			get
			{
				return(MParent);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeLinkCollection								Children
		{
			get
			{
				return(MChildren);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsRoot
		{
			get
			{
				return(MParent==null);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeNodeID										TreeNodeID
		{
			get
			{
				return(MTreeNodeData.TreeNodeID);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void InternalGetChildrenByPredicate(List<CTreeNode> TreeObjects, Predicate<CTreeNode> Predicate)
		{
			if (Predicate(MTreeNodeData)==true)
				TreeObjects.Add(MTreeNodeData);

			foreach(CTreeLink Child in MChildren)
				Child.InternalGetChildrenByPredicate(TreeObjects,Predicate);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Add(CTreeLink Child)
		{
			MChildren.Add(Child);
		}
//-------------------------------------------------------------------------------------------------------
		public bool PointsToTreeObject(CTreeNodeID TreeNodeID)
		{
			if (this.MTreeNodeData.TreeNodeID==TreeNodeID)
				return(true);
			else
				return(false);
		}
//-------------------------------------------------------------------------------------------------------
		public CTreeNode[] GetChildrenByPredicate(Predicate<CTreeNode> Predicate, bool Distinct)
		{
			List<CTreeNode>			TreeObjects=new List<CTreeNode>();

			InternalGetChildrenByPredicate(TreeObjects,Predicate);

			if (Distinct==true)
			{
				HashSet<CTreeNode>	DistinctTreeObjects=new HashSet<CTreeNode>();

				foreach(CTreeNode TreeObject in TreeObjects)
					if (DistinctTreeObjects.Contains(TreeObject)==false)
						DistinctTreeObjects.Add(TreeObject);

				return(DistinctTreeObjects.ToArray());
			}
			else
				return(TreeObjects.ToArray());
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder		SB=new StringBuilder();

			SB.Append(this.GetType().Name);
			SB.AppendFormat(", TreeNode: [{0}]",TreeNode);
			SB.AppendFormat(", Parent: [{0}]",Parent);
			SB.AppendFormat(", Children.Count: [{0}]",Children.Count);

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------