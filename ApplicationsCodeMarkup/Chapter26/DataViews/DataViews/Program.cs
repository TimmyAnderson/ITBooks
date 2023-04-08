using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
//-------------------------------------------------------------------------------------------------------
namespace DataViews
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			SingleRecordDataEntry				Win=new SingleRecordDataEntry();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			MultiRecordDataEntry				Win=new MultiRecordDataEntry();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			DataEntryWithNavigation				Win=new DataEntryWithNavigation();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			DataEntryWithListBox				Win=new DataEntryWithListBox();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			CollectionViewWithFilter			Win=new CollectionViewWithFilter();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			FilterWithText						Win=new FilterWithText();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			ListBoxWithGroups					Win=new ListBoxWithGroups();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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
				Test7();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadKey();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------