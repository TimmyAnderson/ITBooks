using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace Recursion
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test()
		{
			CTreeNode			NodeD1=new CTreeNode("D1",null,null);
			CTreeNode			NodeD2=new CTreeNode("D2",null,null);
			CTreeNode			NodeD3=new CTreeNode("D3",null,null);
			CTreeNode			NodeD4=new CTreeNode("D4",null,null);
			CTreeNode			NodeD5=new CTreeNode("D5",null,null);
			CTreeNode			NodeD6=new CTreeNode("D6",null,null);
			CTreeNode			NodeD7=new CTreeNode("D7",null,null);
			CTreeNode			NodeD8=new CTreeNode("D8",null,null);

			CTreeNode			NodeC1=new CTreeNode("C1",NodeD1,NodeD2);
			CTreeNode			NodeC2=new CTreeNode("C2",NodeD3,NodeD4);
			CTreeNode			NodeC3=new CTreeNode("C3",NodeD5,NodeD6);
			CTreeNode			NodeC4=new CTreeNode("C4",NodeD7,NodeD8);

			CTreeNode			NodeB1=new CTreeNode("B1",NodeC1,NodeC2);
			CTreeNode			NodeB2=new CTreeNode("B2",NodeC3,NodeC4);

			CTreeNode			NodeA=new CTreeNode("A",NodeB1,NodeB2);

			CParallelRecursion	PR=new CParallelRecursion(2);

			PR.PrintTree(NodeA);

			Console.WriteLine("".PadRight(79,'-'));

			PR.ParallelMirror(NodeA);

			PR.PrintTree(NodeA);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------