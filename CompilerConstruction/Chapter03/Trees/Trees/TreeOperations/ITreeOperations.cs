using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Trees
{
//-------------------------------------------------------------------------------------------------------
	public interface ITreeOperations
	{
//-------------------------------------------------------------------------------------------------------
		void InsertNew(CTreeNodeData NewTreeNodeData, CTreeNodeID ParentTreeNodeID);
		void InsertExisting(CTreeNodeID ParentTreeNodeID, CTreeNodeID ChildTreeNodeID);
		void UpdateObject(CTreeNodeData UpdatedTreeNodeData);
		void DeleteLink(CTreeNodeID ParentTreeNodeID, CTreeNodeID ChildTreeNodeID);
		void DeleteObject(CTreeNodeID TreeNodeID);
		CTreeSourceData CreateTreeSourceData();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------