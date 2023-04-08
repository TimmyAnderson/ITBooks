using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace PathAndGeometries
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			LineGeometryDemo			Win=new LineGeometryDemo();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			RectangleGeometryDemo		Win=new RectangleGeometryDemo();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			EllipseGeometryDemo			Win=new EllipseGeometryDemo();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			OverlappingRectangles		Win=new OverlappingRectangles();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			FourOverlappingCircles		Win=new FourOverlappingCircles();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			CombinedGeometryModes		Win=new CombinedGeometryModes();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			Dumbbell					Win=new Dumbbell();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			TrivialPath					Win=new TrivialPath();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			MultipleLineSegments		Win=new MultipleLineSegments();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			PolyLineSegmentDemo			Win=new PolyLineSegmentDemo();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			OverlappingStars			Win=new OverlappingStars();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			ArcPossibilities			Win=new ArcPossibilities();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			ArcPossibilities2			Win=new ArcPossibilities2();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			FigureWithArcs				Win=new FigureWithArcs();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			SingleBezier				Win=new SingleBezier();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			BezierExperimenter			Win=new BezierExperimenter();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			SimulatedCircle				Win=new SimulatedCircle();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			Infinity					Win=new Infinity();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			BezierReproduce				Win=new BezierReproduce();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			PathMiniLanguage			Win=new PathMiniLanguage();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test21()
		{
			MiniLanguageInfinity		Win=new MiniLanguageInfinity();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test22()
		{
			ClippedButton				Win=new ClippedButton();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test23()
		{
			KeyholeOnTheMoon			Win=new KeyholeOnTheMoon();

			Win.InitializeComponent();

			Application					App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test24()
		{
			TextGeometryWindow			Win=new TextGeometryWindow();

			Win.InitializeComponent();

			Application					App=new Application();

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
				//Test20();
				//Test21();
				//Test22();
				//Test23();
				Test24();
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