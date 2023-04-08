using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace Transforms
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			TransformedButtons_XAML					Win=new TransformedButtons_XAML();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			TransformedButtons_CS					Win=new TransformedButtons_CS();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			InteractiveTranslateTransform_Render	Win=new InteractiveTranslateTransform_Render();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			InteractiveTranslateTransform_Layout	Win=new InteractiveTranslateTransform_Layout();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			InteractiveScaleTransform_Render		Win=new InteractiveScaleTransform_Render();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			InteractiveScaleTransform_Layout		Win=new InteractiveScaleTransform_Layout();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			InteractiveSkewTransform_Render			Win=new InteractiveSkewTransform_Render();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			InteractiveSkewTransform_Layout			Win=new InteractiveSkewTransform_Layout();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			InteractiveRotateTransform_Render		Win=new InteractiveRotateTransform_Render();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			InteractiveRotateTransform_Layout		Win=new InteractiveRotateTransform_Layout();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			RenderTransformAndLayoutTransform		Win=new RenderTransformAndLayoutTransform();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			RotatedButtons							Win=new RotatedButtons();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			WheelAndSpokes							Win=new WheelAndSpokes();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test14()
		{
			GeometryTransformDemo					Win=new GeometryTransformDemo();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test15()
		{
			CanvasModes								Win=new CanvasModes();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test16()
		{
			Flower									Win=new Flower();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test17()
		{
			TiltedTextShadow						Win=new TiltedTextShadow();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test18()
		{
			TiltedTextShadow2						Win=new TiltedTextShadow2();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test19()
		{
			EmbossAndEngrave						Win=new EmbossAndEngrave();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test20()
		{
			EmpiricalTiltedTextShadow				Win=new EmpiricalTiltedTextShadow();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test21()
		{
			TextDropShadow							Win=new TextDropShadow();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test22()
		{
			RotatedText								Win=new RotatedText();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test23()
		{
			RotateAndReflect						Win=new RotateAndReflect();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test24()
		{
			ReflectedText							Win=new ReflectedText();

			Win.InitializeComponent();

			Application								App=new Application();

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