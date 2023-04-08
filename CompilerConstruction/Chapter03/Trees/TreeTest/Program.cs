using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Trees;
//-----------------------------------------------------------------------------------------------------------
namespace TreeTest
{
//-----------------------------------------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			List<CTreeNodeData>					NodeData=new List<CTreeNodeData>();

			NodeData.Add(new CTreeNodeData(new CTreeNodeID("UsersAndGroups")));

			NodeData.Add(new CTreeNodeData(new CTreeNodeID("Administrators")));
			NodeData.Add(new CTreeNodeData(new CTreeNodeID("Users")));

			NodeData.Add(new CTreeNodeData(new CTreeNodeID("Timmy")));
			NodeData.Add(new CTreeNodeData(new CTreeNodeID("Atreyu")));
			NodeData.Add(new CTreeNodeData(new CTreeNodeID("Jenny")));

			List<CTreeEdge>						AllEdges=new List<CTreeEdge>();

			AllEdges.Add(new CTreeEdge(new CTreeNodeID("Administrators"),new CTreeNodeID("Timmy")));
			AllEdges.Add(new CTreeEdge(new CTreeNodeID("Administrators"),new CTreeNodeID("Jenny")));

			AllEdges.Add(new CTreeEdge(new CTreeNodeID("Users"),new CTreeNodeID("Timmy")));
			AllEdges.Add(new CTreeEdge(new CTreeNodeID("Users"),new CTreeNodeID("Atreyu")));
			AllEdges.Add(new CTreeEdge(new CTreeNodeID("Users"),new CTreeNodeID("Jenny")));

			AllEdges.Add(new CTreeEdge(new CTreeNodeID("UsersAndGroups"),new CTreeNodeID("Administrators")));
			AllEdges.Add(new CTreeEdge(new CTreeNodeID("UsersAndGroups"),new CTreeNodeID("Users")));

			CTreeNodeID							TreeNodeID=new CTreeNodeID("UsersAndGroups");
			CTreeSourceData						TreeSourceData=new CTreeSourceData(TreeNodeID,NodeData.ToArray(),AllEdges.ToArray());
			CTree								Tree=new CTree(TreeSourceData);

			Action<CTreeNodeData,int,object>	Action=(TreeNode,Level,Param) =>
			{
				Console.WriteLine(string.Format("{0}TreeNode: [{1}] !","".PadRight(Level-1,'\t'),TreeNode));
			};

			Tree.TraverseTree(Action,null);

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------