using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace Styles
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			ButtonWithLocalStyle				Win=new ButtonWithLocalStyle();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			StyleWithMultipleButtons			Win=new StyleWithMultipleButtons();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			StyleWithMultipleElements			Win=new StyleWithMultipleElements();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			StylesWithSameKeys					Win=new StylesWithSameKeys();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			StyleWithPropertyElement			Win=new StyleWithPropertyElement();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			StyleWithResource					Win=new StyleWithResource();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			StylesWithTargetTypes				Win=new StylesWithTargetTypes();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			BasedOnStyle						Win=new BasedOnStyle();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			BasedOnTargetType					Win=new BasedOnTargetType();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			BasedOnDerivedTargetType			Win=new BasedOnDerivedTargetType();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			TargetTypeDerivatives				Win=new TargetTypeDerivatives();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			SetterWithBinding					Win=new SetterWithBinding();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			GraphicsStyles						Win=new GraphicsStyles();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			DrawGrid							Win=new DrawGrid();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			DocumentStyles						Win=new DocumentStyles();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			EventSetterDemo						Win=new EventSetterDemo();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			StyleWithTriggers					Win=new StyleWithTriggers();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			MultiTriggerDemo					Win=new MultiTriggerDemo();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			StyleWithDataTrigger				Win=new StyleWithDataTrigger();

			Win.InitializeComponent();

			Application							App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			MultiDataTriggerDemo				Win=new MultiDataTriggerDemo();

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
				//Test18();
				//Test19();
				Test20();
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