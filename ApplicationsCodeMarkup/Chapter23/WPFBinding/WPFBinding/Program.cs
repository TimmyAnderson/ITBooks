using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace WPFBinding
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			BindingWithElementSyntax			Win=new BindingWithElementSyntax();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			BindingWithMarkupExtensionSyntax	Win=new BindingWithMarkupExtensionSyntax();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			BindingWithCSharp					Win=new BindingWithCSharp();
			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			BindingOneWayToSource				Win=new BindingOneWayToSource();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			BindingWithDataContext				Win=new BindingWithDataContext();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			BindingWithDataContextTwoBindings	Win=new BindingWithDataContextTwoBindings();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			ErrorBindingWithNoDP				Win=new ErrorBindingWithNoDP();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			CustomElementBindingWindow			Win=new CustomElementBindingWindow();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			BindingWithComplexPath				Win=new BindingWithComplexPath();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			BindingWithDecimalConverter			Win=new BindingWithDecimalConverter();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			MultiBindingTest					Win=new MultiBindingTest();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			UpdateSourceTriggerTest				Win=new UpdateSourceTriggerTest();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			BindingWithSourceProperty			Win=new BindingWithSourceProperty();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			DPAsASource							Win=new DPAsASource();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			SourceChangeNotificationByEvent		Win=new SourceChangeNotificationByEvent();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			ChangeByINotifyPropertyChanged		Win=new ChangeByINotifyPropertyChanged();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			FormattedMultiBinding				Win=new FormattedMultiBinding();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			RelativeSourceDemo					Win=new RelativeSourceDemo();

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
				//Test11();
				//Test12();
				//Test13();
				//Test14();
				//Test15();
				//Test16();
				//Test17();
				Test18();
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