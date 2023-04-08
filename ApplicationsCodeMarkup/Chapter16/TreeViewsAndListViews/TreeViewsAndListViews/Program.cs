using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//------------------------------------------------------------------------------
namespace TreeViewsAndListViews
{
//------------------------------------------------------------------------------
	class Program
	{
//------------------------------------------------------------------------------
		private static void Test1()
		{
			CSimpleTreeView					Win=new CSimpleTreeView();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test2()
		{
			CSlowDirectoryTreeView			Win=new CSlowDirectoryTreeView();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test3()
		{
			CDiskTreeView					Win=new CDiskTreeView();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test4()
		{
			CTreeViewWithTemplate			Win=new CTreeViewWithTemplate();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test5()
		{
			CShowClassHierarchy				Win=new CShowClassHierarchy();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test6()
		{
			CSimpleListView					Win=new CSimpleListView(false);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test7()
		{
			CSimpleListView					Win=new CSimpleListView(true);
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test8()
		{
			CSimpleSortedListView			Win=new CSimpleSortedListView();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
		private static void Test9()
		{
			CExploreDependencyProperties	Win=new CExploreDependencyProperties();
			Application						App=new Application();

			App.Run(Win);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				//Test1();
				//Test2();
				//Test3();
				//Test4();
				//Test5();
				//Test6();
				//Test7();
				//Test8();
				Test9();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------