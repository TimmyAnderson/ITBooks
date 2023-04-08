using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
//-------------------------------------------------------------------------------------------------------
namespace BitmapsDrawingsAndBrushes
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			DrawButtonsOnBitmap						Win=new DrawButtonsOnBitmap();
			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			DrawGraphicsOnBitmap					Win=new DrawGraphicsOnBitmap();
			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test3()
		{
			CreateIndexedBitmap						Win=new CreateIndexedBitmap();
			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test4()
		{
			CreateFullColorBitmap					Win=new CreateFullColorBitmap();
			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test5()
		{
			ConvertedBitmapChain					Win=new ConvertedBitmapChain();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test6()
		{
			ImageDisplaysVectorGraphics				Win=new ImageDisplaysVectorGraphics();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test7()
		{
			PictureAndFrame							Win=new PictureAndFrame();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test8()
		{
			SimpleImageBrush						Win=new SimpleImageBrush();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test9()
		{
			SimpleVisualBrush						Win=new SimpleVisualBrush();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test10()
		{
			SimpleDrawingBrush						Win=new SimpleDrawingBrush();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test11()
		{
			FishBrush								Win=new FishBrush();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test12()
		{
			ReflectedControls						Win=new ReflectedControls();

			Win.InitializeComponent();

			Application								App=new Application();

			App.Run(Win);
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test13()
		{
			AnimatedDrawingBrush					Win=new AnimatedDrawingBrush();

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
				Test13();
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