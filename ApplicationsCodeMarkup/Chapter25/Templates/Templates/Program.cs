using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace Templates
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			ButtonWithTemplate					Win=new ButtonWithTemplate();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			ResourceTemplate					Win=new ResourceTemplate();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CircledRadioButtons					Win=new CircledRadioButtons();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			ToggleSwitch						Win=new ToggleSwitch();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			AutoTemplateSelection				Win=new AutoTemplateSelection();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			SelectDataTemplate					Win=new SelectDataTemplate();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			TriggerDataTemplate					Win=new TriggerDataTemplate();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			ListBoxWithItemsPanel				Win=new ListBoxWithItemsPanel();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			ColorListBoxTemplateWindow			Win=new ColorListBoxTemplateWindow();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			EmployeeWheelWindow					Win=new EmployeeWheelWindow();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			HierarchicalTemplates				Win=new HierarchicalTemplates();

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
				//Test7();
				//Test8();
				//Test9();
				//Test10();
				Test11();
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